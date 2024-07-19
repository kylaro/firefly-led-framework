
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "ha_mqtt.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"
#include "lwip/netif.h"
#include "lwip/api.h"
#include "pico/cyw43_arch.h"
#include "lwip/priv/tcpip_priv.h"


static mqtt_client_t mqtt_client;

static void ha_connect_to_mqtt();
static void ha_mqtt_connect_cb( mqtt_client_t *client, void *arg, mqtt_connection_status_t status );
static void ha_message_received_cb( void *arg, const char *topic, u32_t tot_len );
static void ha_mqtt_sub_request_cb( void *arg, err_t result );

static void ha_message_received_cb( void *arg, const char *topic, u32_t tot_len ) {
    struct pbuf *p = (struct pbuf *)arg;
    char payload[10];
    int offset = 0;

    while(p != NULL) {
        memcpy( &payload[offset], p->payload, p->len );
        offset += p->len;
        p = p->next;
    }
    payload[tot_len] = '\0';

    if( strcmp(payload, "ON") == 0 ) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    } else if( strcmp(payload, "OFF" ) == 0) {
        cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    }
}

static void ha_mqtt_sub_request_cb( void *arg, err_t result ) {
    if (result != ERR_OK) {
        printf( "Subscribe failed\n" );
    }
}

static void ha_mqtt_connect_cb( mqtt_client_t *client, void *arg, mqtt_connection_status_t status ) {
    if (status == MQTT_CONNECT_ACCEPTED) {
        printf( "MQTT Connected\n" );
        for(int i = 0; i < 30; i++){
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            sleep_ms(20);
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            sleep_ms(20);
        }
        mqtt_subscribe( client, MQTT_TOPIC, 0, ha_mqtt_sub_request_cb, ha_message_received_cb );
    } else {
        printf( "MQTT Connection failed\n" );
    }
}

static void ha_connect_to_mqtt() {
    ip4_addr_t mqtt_server_ip;
    ip4addr_aton( MQTT_BROKER, &mqtt_server_ip );

    struct mqtt_connect_client_info_t ci;
    memset( &ci, 0, sizeof(ci) );
    ci.client_id = "pico_w";
    ci.client_user = NULL;
    ci.client_pass = NULL;
    ci.keep_alive = 100;

    printf("[MQTT] Attempting to connect...\n");

    mqtt_client_connect( &mqtt_client, &mqtt_server_ip, MQTT_PORT, ha_mqtt_connect_cb, NULL, &ci );
}

void ha_mqtt_init() {
    tcpip_init( NULL, NULL );
    ha_connect_to_mqtt();
}