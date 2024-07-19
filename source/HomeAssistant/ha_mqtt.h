#ifndef HA_MQTT_H
#define HA_MQTT_H

#include <stdint.h>

#define MQTT_LOGIN "ha"
#define MQTT_PASSWORD "ha"

#define MQTT_BROKER "192.168.1.18"
#define MQTT_TOPIC "home/pico_w/led"

#ifdef __cplusplus
extern "C" {
#endif

void ha_mqtt_init();

#ifdef __cplusplus
}
#endif


#endif // HA_MQTT_H