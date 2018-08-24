/*-------------------------------------------------------------------
    Title: FYP
    Description: Embedded system that logs temperature, humidity, particles, CO, CO2 and GPs
              sending this information to a database using particle cloud.
    Author: Merlin Roe
    Date:   5/09/2016
*/
    float __version = 2.54;

/* ----------------------------INCLUDES-------------------------------------- */

/* Libraries */
#include "application.h"
#include <math.h>
#include "HttpClient.h"
#include "DHT.h"
#include "WIFI.h"
#include "MQ135.h"

#define DEBUG_LOG 2 /*  0 = no debug.	 1 = outputdebug and upload.	 2 - debug and dont upload. */
#define MAX_RESULT_COUNT 50	/* Maximum results that can be stored */
#define MEASURE_INTERMQ135_value 28000 /* Time between new readings (1 minute) */
char DEVICE_ID = 1;

SYSTEM_MODE(SEMI_AUTOMATIC);    /* Semi-Automatic, does not automatically connect */

/*----------------------------GLOBALS---------------------------------------*/

/*  Pins
    Digital Pin 0    - Temp/Humid sensor
    Digital Pin 5    - Air quality sensor
    Analog  Pin 4    - MQ135
*/

unsigned long sampletime_ms = 30000;    /* Time bewteen results. 30000 = 30 seconds */
unsigned long starttime;
unsigned long reading_interMQ135_value;

DHT dht;	/* initialising DHT library */

/*-------- PPD42NJ particl sensors --------*/
int AIR_Q_PIN = D5;
unsigned long duration;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;

/*-------- MQ135 --------*/
int MQ135_PIN = A4;
int MQ135_value = 0;

/* -------- HTTPS -------- */
#define UPLOAD_ATTEMPT_LIMIT 11
HttpClient http;

http_header_t headers[] = {
    { "Accept" , "*/*"},
    { NULL, NULL } /* NOTE: Always terminate headers will NULL */
};

http_request_t request;
http_response_t response;

/* -------- Data structure -------- */

char res_index = 0;

struct current_readings {
    int humid = 0;
    float temp = 0;

	int particle_LPO = 0;
    float particle_ratio = 0;
    float particle_concentration = 0;
 
	unsigned short int mq135_CO2 = 0;

	String GPS;
	char GPS_status = 'V'; /* Defualt "Void" GPS status */
} struct_datagroup[MAX_RESULT_COUNT];

/* --------------------------FUNCTIONS----------------------------------------- */

 /**************** print_data ****************
 Input:         void
 Output:       	void
 Description:   Outputs all variables stored within struct
*********************************************************/
void print_data(){
    Serial1.print("Version: ");
	Serial1.println(__version);
    
    Serial1.print("Data index: ");
	Serial1.println(int(res_index));
    
    Serial1.print("Humdity: ");
    Serial1.println(struct_datagroup[res_index].humid);
    Serial1.print("Temperature: ");
    Serial1.println(struct_datagroup[res_index].temp);

	Serial1.print("LPO: ");
    Serial1.println(struct_datagroup[res_index].particle_LPO);
    Serial1.print("Particle ratio: ");
    Serial1.println(struct_datagroup[res_index].particle_ratio);
    Serial1.print("Particles per 0.01 cubic feet: ");
    Serial1.println(struct_datagroup[res_index].particle_concentration);

	Serial1.print("MQ135 CO2: ");
    Serial1.print(struct_datagroup[res_index].mq135_CO2);
	Serial1.println(" PPM");
	
	Serial1.print("GPS Status: ");
    Serial1.println(struct_datagroup[res_index].GPS_status);
	
	Serial1.print("GPS: ");
    Serial1.println(struct_datagroup[res_index].GPS);

    Serial1.println("-----------------------");
}

 /**************** read_GPS ****************
 Input:         
 Output:        data - String with entire RMC data

 Description:   Consistantly reads the serial connection of the GPS,
 				Record each line.
				Exit loop when entire line is read and starts with RMC.
 *********************************************************/
String read_GPS(){
    String inWord;
    char inByte;
    while(1){
        while (Serial1.available() > 0){
            inByte = Serial1.read();

        	if (inByte == '\n') {
        		if (inWord.startsWith("$GPRMC")) {
        			return inWord;
        			inWord = "";
        		}
        		else{
        			/* reset string */
        			inWord = "";
            	}
        	}
        	else{
        		inWord += inByte; /*building string */
        	}
        }
    }
}

 /**************** upload_results ****************
 Input:         void
 Output:        void

 Description:   loops through from current to oldest data set,
                creating the GET string and uploading to the server.
 *********************************************************/
void upload_results(){

	for(int i = res_index; i >= 0; i--){
        if(struct_datagroup[i].GPS_status == 'V'){
            Serial1.print("Ignoring data set for inMQ135_valueid GPS: ");
            Serial1.println(i);
		    continue;
        }
            	
		Serial1.println("Uploading results...");

        /* Creating string for uploading Via GET */
		String path = String::format("/insertdata.php?sensor_ID=%d&temp=%.2f&humid=%d&CO2=%d&parti=%f&gps=", 
                                    DEVICE_ID, struct_datagroup[i].temp, struct_datagroup[i].humid, struct_datagroup[i].mq135_CO2, 
                                    struct_datagroup[i].particle_concentration);

		path = String(path + struct_datagroup[i].GPS);
		Serial1.println(path);

        /* reuqest details */
		request.hostname = "www.merlinroe.com";
		request.port = 80;
		request.path = path;
		
        http.get(request, response, headers);
        Serial1.print("Application>\tResponse status: ");
		Serial1.println(response.status);
        delay(10);
	}
	
    Serial1.println("-----------------------");
	res_index = 0;
}

 /**************** setup ****************
 Input:         void
 Output:        void

 Description:   
 *********************************************************/
void setup()
{
	Serial1.begin(9600);	/* RX/TX serial IC2, using external USB adapter */

	pinMode(AIR_Q_PIN,INPUT);
	/* pinMode(MQ135_PIN, INPUT); Can be omitted since analog */
	
	Serial1.print("Application started, Version: ");
	Serial1.println(__version);
	
	dht.setup(D0);
	
	setup_known_wifi();
	WiFi.on();
	check_network();

	reading_interMQ135_value = millis();
}

void loop()
{
    if ((millis()-reading_interMQ135_value) > MEASURE_INTERMQ135_value){
        
        starttime = millis();	/* starting time for particle sensor */
		lowpulseoccupancy = 0;
        
        while((millis()-starttime) < sampletime_ms){
            /* counting low pulse */
	        duration = pulseIn(AIR_Q_PIN, LOW);
	        lowpulseoccupancy = lowpulseoccupancy+duration;
        }
        
        float ratio = 0;
		
		/*-------- Particle Sensor --------*/

		ratio = lowpulseoccupancy / (sampletime_ms * 10.0);  /* Integer percentage 0=>100 */

        /* using spec sheet curve */
		struct_datagroup[res_index].particle_concentration = 1.1 * pow(ratio,3) - 3.8 * pow(ratio,2) + 520*ratio + 0.62; 
		struct_datagroup[res_index].particle_LPO = lowpulseoccupancy;
		struct_datagroup[res_index].particle_ratio = ratio;

		/*-------- MQ gas sensor --------*/

		int MQ135_valuer = 0;
		
		/* find average of 5 values */
		for(int i = 0; i < MQ135_READ_COUNT; i++){
		    MQ135_valuer += analogRead(MQ135_PIN);
		    delay(MQ135_READ_DELAY);
		}
		MQ135_valuer = MQ135_valuer / MQ135_READ_COUNT;
		
		MQ135_value = ((float)22000*(1023-MQ135_valuer)/MQ135_valuer);
        
        /* convert to ppm (using default ro) */
        struct_datagroup[res_index].mq135_CO2 = mq135_getppm(MQ135_value, MQ135_DEFAULTRO);

		/*-------- DHT22 Temp + Humidity sensor --------*/
		
	    struct_datagroup[res_index].temp = dht.getTemperature();
	    struct_datagroup[res_index].humid = dht.getHumidity();
	    
	    /*------- GPS --------*/

		struct_datagroup[res_index].GPS = read_GPS();
		
        /* Searching string for V (void) or A (active) from the status */
		for(int i = 0; i < struct_datagroup[res_index].GPS.length(); i++){
		    if(struct_datagroup[res_index].GPS.charAt(i) == 'V'){
		        struct_datagroup[res_index].GPS_status = 'V';
		        break;
		    }
		    else if(struct_datagroup[res_index].GPS.charAt(i) == 'A'){
		        struct_datagroup[res_index].GPS_status = 'A';
		        break;
		    } 
		}
		
		/*-------- Print Debug --------*/
		
		if(DEBUG_LOG > 0){
			print_data();
		}
		
		/* debug 2 means no uploading / Which in turns means no saving results */
		if(DEBUG_LOG != 2){
			if(check_network()){
				Serial1.println("Attempting to upload results");
				upload_results();
			}
			else{
				/* Save */
				if(res_index < MAX_RESULT_COUNT){
				    if(struct_datagroup[res_index].GPS_status == 'A'){
				        Serial1.println("No WiFi, storing results");
				        res_index++;
            	    }
            	    else{
            	        Serial1.println("No WiFi or GPS");
            	    }
				}
			}
		}

        /* reseting counter for loop */
	    reading_interMQ135_value = millis();
    }
}