#ifndef HA_MQTT_H
#define HA_MQTT_H

#include <stdint.h>

#define MQTT_LOGIN "ha"
#define MQTT_PASSWORD "ha"
#define MQTT_BROKER "192.168.1.18"

#define MQTT_TOPIC_SUBSCRIBE "home/pico_w/led/set"
#define MQTT_TOPIC_PUBLISH "home/pico_w/led/state"
#define MQTT_TOPIC_DISCOVERY "homeassistant/switch/pico_w_led/config"
#define MQTT_HEARTBEAT 0

#ifdef __cplusplus
extern "C" {
#endif

void ha_mqtt_init();
void ha_mqtt_loop();

#ifdef __cplusplus
}
#endif


#endif // HA_MQTT_H