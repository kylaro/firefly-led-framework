#ifndef HA_MQTT_H
#define HA_MQTT_H

#include <stdint.h>

#define MQTT_LOGIN "kylar"
#define MQTT_PASSWORD "SudoRoot42069"
#define MQTT_BROKER "192.168.1.227"

#define MQTT_TOPIC_SUBSCRIBE "home/pico_w/led/set"
#define MQTT_TOPIC_PUBLISH "home/pico_w/led/state"
#define MQTT_TOPIC_DISCOVERY "homeassistant/switch/pico_w_led/config"
#define MQTT_HEARTBEAT 0

#ifdef __cplusplus
extern "C" {
#endif

void ha_mqtt_init();
void ha_mqtt_loop();

typedef struct{
    // We know the centers, and can track their movement
    bool enabled;
    float brightness;
    float hue;
    float saturation;
    float value;
    float r, g, b;
    int pattern_index; 
} ha_data_t;


ha_data_t *get_ha_data();

#ifdef __cplusplus
}
#endif


#endif // HA_MQTT_H