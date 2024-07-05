#include "stdio.h"
//#include <WiFi/WiFi.h>
#include "Network.h"
#include "Credentials.h"

int status;

void Network::connect() {
    while (status != 0) {

    printf("Attempting to connect to WPA SSID: %s\n", WIFI_SSID);

    // Connect to WPA/WPA2 network:

    //status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //Set these credentials

    // wait to connect:

    //delay(5000);

  }

  if (status == 0) {
    printf("Connected to %s\n", WIFI_SSID);
  }else{
    printf("Connection error status = %d\n", status);
  }
}