#ifndef HA_MQTT_H
#define HA_MQTT_H

#include <stdint.h>
#include "../../../../config.h" // Get MQTT Broker / User / Pass


/* Topic definitions are replaced with char array so it
 * could be dynamically tied with the Unique ID (WiFi MAC)
 */
// #define MQTT_TOPIC_SUBSCRIBE "home/pico_w/led/set"
// #define MQTT_TOPIC_PUBLISH "home/pico_w/led/state"
// #define MQTT_TOPIC_DISCOVERY "homeassistant/switch/pico_w/config"


#define SW_VERSION "0.01" /* Placeholder */

#ifdef __cplusplus
extern "C" {
#endif

void ha_mqtt_init();
void ha_mqtt_loop();

typedef struct{
    bool enabled;
    float brightness;
    float hue;
    float saturation;
    float value;
    float r, g, b;
    int pattern_index; 
} ha_data_t; // Different struct for sending  / receiving from HomeAssistant?



ha_data_t *get_ha_data();

bool set_ha_temperature(double celsius); // Please redo this in a better way, just doing Proof of concept.

#ifdef __cplusplus
}
#endif


#endif // HA_MQTT_H