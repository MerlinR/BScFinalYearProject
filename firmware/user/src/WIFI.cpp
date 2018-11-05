/******************************************************************
  Small network managment for Redbear Duo

  Features:
  - Auto connects to known networks
  - Scans local networks
  
  Author:  Merlin Roe, merlin.roe@hotmail.co.uk
  Heavily relies on Sparkfun API

 ******************************************************************/

#include "WIFI.h"
#include <application.h>

#define WIFI_CHECK_TIME 50 //Times to wait connecting to network and to receive IP.

struct wifi_struct {
  String ssid;
  String password;
};

struct wifi_struct known_wifi[WIFI_COUNT];

 void setup_known_wifi(){
    known_wifi[0].ssid = "SSID";
    known_wifi[0].password = "PASSWORD";
 }

int check_network(){
    //Check if connected, if not scan for known networks.
    if(WiFi.ready()){
        return 1;
    }
    else{
        scan_networks();
    }

    //Check connection again
    if(WiFi.ready()){
        return 1;
    }
    else {
        WiFi.disconnect(); //redudant to ensure disconnected
        return 0;
    }

}

 void scan_networks() {
  // scan for nearby networks:

  WiFiAccessPoint aps[20];
  int found = WiFi.scan(aps, 20);

  if (found <= 0) {
    Serial1.println("No wifi connections");
    return;
  }

  // print the list of networks seen:
  for (int i = 0; i < found; i++) {
    WiFiAccessPoint& ap = aps[i];

    for(int i = 0; i < WIFI_COUNT; i++){
        if(known_wifi[i].ssid == ap.ssid){
            connect_to_network(i);
            return;
        }
    }
  }
}

void connect_to_network(int index){

    WiFi.setCredentials(known_wifi[index].ssid,known_wifi[index].password);
    WiFi.connect();

    Serial1.print("connecting to SSID: ");
    Serial1.println(known_wifi[index].ssid);

    char wifi_count = 0;

    while ( WiFi.connecting()) {
        
        if(wifi_count > WIFI_CHECK_TIME)
            return;
        
        // print dots while we wait to connect
        Serial1.print(".");
        delay(300);
        
        wifi_count++;
    }

    wifi_count = 0;

    IPAddress localIP = WiFi.localIP();
    
    while (localIP[0] == 0) {
        localIP = WiFi.localIP();
        
        if(wifi_count > WIFI_CHECK_TIME)
            return;
        
        Serial1.println("waiting for an IP address");
        delay(1000);
        
        wifi_count++;
    }

    Particle.connect();
}