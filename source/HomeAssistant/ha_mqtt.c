
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

#include "ha_mqtt.h"
#include "lwip/apps/mqtt.h"
#include "lwip/apps/mqtt_priv.h"

#include "lwip/pbuf.h"
#include "lwip/tcp.h"
#include "lwip/dns.h"

#include "lwip/altcp_tcp.h"
#include "lwip/altcp_tls.h"

typedef struct MQTT_CLIENT_T_ {
    ip_addr_t remote_addr;
    mqtt_client_t *mqtt_client;
    u32_t received;
    u32_t counter;
    u32_t reconnect;
} MQTT_CLIENT_T;

// MQTT global
static mqtt_client_t *g_client;
static MQTT_CLIENT_T *g_state;

static MQTT_CLIENT_T* mqtt_client_init(void) {
    g_state = calloc(1, sizeof(MQTT_CLIENT_T));
    if (!g_state) {
        printf("failed to allocate state\n");
        return NULL;
    }
    g_state->received = 0;
    return g_state;
}

static void dns_found(const char *name, const ip_addr_t *ipaddr, void *callback_arg) {
    MQTT_CLIENT_T *state = (MQTT_CLIENT_T*)callback_arg;
    printf("DNS query finished with resolved addr of %s.\n", ip4addr_ntoa(ipaddr));
    state->remote_addr = *ipaddr;
}

static void run_dns_lookup() {
    printf("Running DNS query for %s.\n", MQTT_BROKER);

    cyw43_arch_lwip_begin();
    err_t err = dns_gethostbyname(MQTT_BROKER, &(g_state->remote_addr), dns_found, g_state);
    cyw43_arch_lwip_end();

    if (err == ERR_ARG) {
        printf("failed to start DNS query\n");
        return;
    }

    if (err == ERR_OK) {
        printf("no lookup needed\n");
        return;
    }

    while (g_state->remote_addr.addr == 0) {
        cyw43_arch_poll();
        sleep_ms(1);
    }
}

static void mqtt_pub_request_cb(void *arg, err_t err) {
    printf("mqtt_pub_request_cb: err %d\n", err);
    g_state->received++;
}

static void mqtt_sub_request_cb(void *arg, err_t err) {
    printf("mqtt_sub_request_cb: err %d\n", err);
}

static err_t _mqtt_publish(const char *topic, const char *msg, uint8_t retain, uint8_t qos) {
    err_t err;
    cyw43_arch_lwip_begin();
    err = mqtt_publish(g_state->mqtt_client, topic, msg, strlen(msg), qos, retain, mqtt_pub_request_cb, g_state);
    cyw43_arch_lwip_end();
    if(err != ERR_OK) {
        printf("Publish err: %d\n", err);
    }

    return err; 
}

// Global data
u32_t data_in = 0;
u8_t buffer[1025];
u8_t data_len = 0;

static void mqtt_pub_start_cb(void *arg, const char *topic, u32_t tot_len) {
    printf("mqtt_pub_start_cb: topic %s\n", topic);

    if (tot_len > 1024) {
        printf("Message length exceeds buffer size, discarding");
    } else {
        data_in = tot_len;
        data_len = 0;
    }
}

static void mqtt_pub_data_cb(void *arg, const u8_t *data, u16_t len, u8_t flags) {
    if (data_in > 0) {
        data_in -= len;
        memcpy(&buffer[data_len], data, len);
        data_len += len;

        if (data_in == 0) {
            buffer[data_len] = 0;
            printf("Message received: %s\n", &buffer);
        }

        // Process received MQTT messages here.

        if (strncmp((const char *)data, "ON", len) == 0) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
            _mqtt_publish(MQTT_TOPIC_PUBLISH, "ON", 0, 0);
        } else if (strncmp((const char *)data, "OFF", len) == 0) {
            cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
            _mqtt_publish(MQTT_TOPIC_PUBLISH, "OFF", 0, 0);
        }
    }
}

static void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
    if (status != 0) {
        printf("Error during connection: err %d.\n", status);
    } else {
        printf("MQTT connected.\n");
    }
}

static err_t _mqtt_publish_discovery() {
    char msg[256];
    uint8_t mac[6];
    cyw43_wifi_get_mac(NULL, CYW43_ITF_STA, mac);
    char mac_str[12];
    snprintf(mac_str, sizeof(mac_str), "%02X%02X%02X%02X%02X%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    snprintf(msg, sizeof(msg),
        "{\"name\":\"Pico W LED\","
        "\"state_topic\":\"home/pico_w/led/state\","
        "\"command_topic\":\"home/pico_w/led/set\","
        "\"unique_id\":\"picow_%s\","
        "\"payload_on\":\"ON\","
        "\"payload_off\":\"OFF\","
        "\"qos\":1,"
        "\"retain\":false}", mac_str);
    _mqtt_publish(MQTT_TOPIC_DISCOVERY, msg, 1, 1);
}

static err_t _mqtt_publish_heartbeat() {
    char msg[256];
    sprintf(msg, "{\"message\":\"hello from picow %d / %d\"}", g_state->received, g_state->counter);
    _mqtt_publish(MQTT_TOPIC_PUBLISH, msg, 0, 0);
}

static err_t mqtt_test_connect() {
    struct mqtt_connect_client_info_t ci;
    err_t err;

    memset(&ci, 0, sizeof(ci));

    ci.client_id = "PicoW";
    ci.client_user = NULL;
    ci.client_pass = NULL;
    ci.keep_alive = 0;
    ci.will_topic = NULL;
    ci.will_msg = NULL;
    ci.will_retain = 0;
    ci.will_qos = 0;

    #if MQTT_TLS

    struct altcp_tls_config *tls_config;

    #if defined(CRYPTO_CA) && defined(CRYPTO_KEY) && defined(CRYPTO_CERT)
    printf("Setting up TLS with 2wayauth.\n");
    tls_config = altcp_tls_create_config_client_2wayauth(
        (const u8_t *)ca, 1 + strlen((const char *)ca),
        (const u8_t *)key, 1 + strlen((const char *)key),
        (const u8_t *)"", 0,
        (const u8_t *)cert, 1 + strlen((const char *)cert)
    );
    // set this here as its a niche case at the moment.
    // see mqtt-sni.patch for changes to support this.
    ci.server_name = MQTT_SERVER_HOST;
    #elif defined(CRYPTO_CERT)
    printf("Setting up TLS with cert.\n");
    tls_config = altcp_tls_create_config_client((const u8_t *) cert, 1 + strlen((const char *) cert));
    #endif

    if (tls_config == NULL) {
        printf("Failed to initialize config\n");
        return -1;
    }

    ci.tls_config = tls_config;
    #endif

    const struct mqtt_connect_client_info_t *client_info = &ci;

    err = mqtt_client_connect(g_state->mqtt_client, &(g_state->remote_addr), MQTT_PORT, mqtt_connection_cb, g_state, client_info);
    
    if (err != ERR_OK) {
        printf("mqtt_connect return %d\n", err);
    }

    return err;
}

static void mqtt_connect() {
    if (mqtt_test_connect() == ERR_OK) {
        mqtt_set_inpub_callback(g_state->mqtt_client, mqtt_pub_start_cb, mqtt_pub_data_cb, 0);
    }
}

static void mqtt_run() {
    g_client = mqtt_client_new();
    g_state->mqtt_client = g_client;

    if (g_state->mqtt_client == NULL) {
        printf("Failed to create new mqtt client\n");
        return;
    }

    g_state->counter = 0;

    mqtt_connect();
}

// Public interface
void ha_mqtt_loop() {
    absolute_time_t timeout = nil_time;
    bool subscribed = false;
    bool discovered = false;
    err_t status = ERR_RST;

    while (true) {
        cyw43_arch_poll();
        absolute_time_t now = get_absolute_time();
        if (is_nil_time(timeout) || absolute_time_diff_us(now, timeout) <= 0) {
            if (mqtt_client_is_connected(g_state->mqtt_client)) {
                cyw43_arch_lwip_begin();

                if (!subscribed) {
                    mqtt_sub_unsub(g_state->mqtt_client, MQTT_TOPIC_SUBSCRIBE, 0, mqtt_sub_request_cb, 0, 1);
                    subscribed = true;
                }
                if (!discovered) {
                    status = _mqtt_publish_discovery();
                    discovered = true;
                }
                else {
                    if( MQTT_HEARTBEAT ) {
                        status = _mqtt_publish_heartbeat();
                    }
                }

                if (ERR_OK == status) {
                    if (g_state->counter != 0) {
                        printf("published %d\n", g_state->counter);
                    }
                    timeout = make_timeout_time_ms(5000);
                    g_state->counter++;
                } // else ringbuffer is full and we need to wait for messages to flush.
                cyw43_arch_lwip_end();
            } else {
                mqtt_connect();
            }
        }
    }
}

void ha_mqtt_init() {
    // memory alloc for mqtt instance
    if( NULL == mqtt_client_init() ) {
        printf("Failed to create new mqtt instance\n");
        return;
    }

    run_dns_lookup();  // checks if mqtt broker is reachable
    mqtt_run();        // runs the mqtt
}