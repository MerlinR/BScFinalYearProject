/******************************************************************
  MQ135 CO2 monitoring library for Redbear Duo

  Features:
  - Calibrates Ro
  - Detects CO2
  - Small library

  Contribution:  Merlin Roe, merlin.roe@hotmail.co.uk
  Based on epierre  https://github.com/empierre/arduino/blob/master/AirQuality-MQ135.ino
                    https://github.com/empierre/arduino/blob/master/AirQuality-Multiple_Gas_Sensor1_4.ino

  Datasheets:
  - https://www.futurlec.com/Datasheet/Sensor/MQ-135.pdf
  - http://china-total.com/Product/meter/gas-sensor/MQ135.pdf

  Changelog:
   
 ******************************************************************/
#ifndef mq_h
#define mq_h

#define MQ135_DEFAULTPPM 409 //default ppm of CO2 for calibration
//#define MQ135_DEFAULTRO 78550 //default Ro for MQ135_DEFAULTPPM ppm of CO2
//#define MQ135_DEFAULTRO 102451 //First calibration
#define MQ135_DEFAULTRO 148594 //Solder calibration
#define MQ135_SCALINGFACTOR 116.6020682 //CO2 gas value
#define MQ135_EXPONENT -2.769034857 //CO2 gas value
#define MQ135_MAXRSRO 2.428 //for CO2
#define MQ135_MINRSRO 0.358 //for CO2
#define MQ135_READ_COUNT 5 //to get averge analog value
#define MQ135_READ_DELAY 2

long mq135_getro(long resvalue, double ppm);

double mq135_getppm(long resvalue, long ro);

#endif // mq_h