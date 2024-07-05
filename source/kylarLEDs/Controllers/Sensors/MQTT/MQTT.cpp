#include "MQTT.h"

int MQTT::initialized = 0;
MQTT::MQTT(){
    // Constructor does nothing, this will be static class
    // No need for objects
}

// static
void MQTT::start(){
    initialized = 1;
}