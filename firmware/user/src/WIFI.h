/******************************************************************
  Small network managment for Redbear Duo

  Features:
  - Auto connects to known networks
  - Scans local networks
  
  Author:  Merlin Roe, merlin.roe@hotmail.co.uk
  Heavily relies on Sparkfun API

 ******************************************************************/

#ifndef WiFi_h
#define WiFi_h

#define WIFI_COUNT 5 //Number of stored networks

void setup_known_wifi();

int check_network();
void scan_networks();
void connect_to_network(int index);

#endif // WiFi_h