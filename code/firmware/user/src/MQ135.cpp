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
 
#include "MQ135.h"
#include <math.h>

 /**************** mq135_getro ****************
 Input:         resvalue - raw value from MQ135
                ppm - Defualt world Co2 PPM levels.
 Output:        Ro - current Ro of sensor

 Description:   This function assumes that the sensor is in clean air.
                #SHOULD NOT BE CALLED AFTER IMPLEMENTATION
 /*********************************************************/
long mq135_getro(long resvalue, double ppm) {
    return (long)(resvalue * exp( log(MQ135_SCALINGFACTOR/ppm) / MQ135_EXPONENT ));
}

 /******************* mq135_getppm ******************
 Input:         resvalue - raw value from MQ135
                ro

 Output:        PPM of CO2

 Description:   This function uses the curve diagram from specfication,
                and current global CO2 levels to, calculate the ppm 
                (parts per million) of CO2.
 /*********************************************************/
double mq135_getppm(long resvalue, long ro) {
    double ret = 0;
    double validinterval = 0;
    validinterval = resvalue/(double)ro;
    if(validinterval<MQ135_MAXRSRO && validinterval>MQ135_MINRSRO) {
    ret = (double)MQ135_SCALINGFACTOR * pow( ((double)resvalue/ro), MQ135_EXPONENT);
    }
    return ret;
}