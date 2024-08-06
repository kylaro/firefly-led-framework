#pragma once
// Welcome to the beautiful config file. Here lies everything you could ever want to configure.


////////////////////////////////////////////////////////////
/////////                 LEDS                  ////////////
////////////////////////////////////////////////////////////
/**
 * NUM_STRIPS is the number of pins to output on.
 * NUM_LEDS is the number of LEDs per strip.
 * TODO: Make the strips able to turn on / off output pins.
 * 
 */
#define NUM_STRIPS 2
#define NUM_LEDS 64


////////////////////////////////////////////////////////////
/////////                 HARDWARE              ////////////
////////////////////////////////////////////////////////////
/**
 * Enable only one. Set to 1 for enable, 0 for disable.
 * 
 * Microphone Enable: Use Core1 for signal processing.
 *                    PIO1 for reading the microphone.
 * MQTT Enable: Turn on Wifi in Core1, but for MQTT + Home Assistant in Station mode
 * WiFi Enable: Turn on Wifi in Core1, but host a network + website in Access Point mode
 */
#define MICROPHONE_ENABLE 0
#define MQTT_ENABLE 1 // picow only.
#define WIFI_ENABLE 0 // picow only.



////////////////////////////////////////////////////////////
/////////                MICROPHONE             ////////////
////////////////////////////////////////////////////////////
/**
 * Signal Processing Options
 */
#define LOW_BINS 20
#define SKIP_BINS 0


////////////////////////////////////////////////////////////
/////////                MQTT                   ////////////
////////////////////////////////////////////////////////////
#define MQTT_LOGIN "kylar"
#define MQTT_PASSWORD "SudoRoot42069"
#define MQTT_BROKER "192.168.1.227"
#define MQTT_HEARTBEAT 0


////////////////////////////////////////////////////////////
/////////                WIFI                   ////////////
////////////////////////////////////////////////////////////
/**
 * WIFI_SSID and WIFI_PASSWORD are used when joining a wifi network (mqtt)
 * AP_WIFI_SSID and AP_WIFI_PASSWORD are used when creating the wifi network (wifi access point)
 * The AP stuff is not implemented yet.
 */
#define WIFI_SSID "trojan-virus" // "Starlink";
#define WIFI_PASSWORD "dmesg1-W-clear!" // "spacelasers42069";
#define AP_WIFI_SSID "picow"
#define AP_WIFI_PASSWORD "12345678"


////////////////////////////////////////////////////////////
/////////                DEBUG                   ////////////
////////////////////////////////////////////////////////////
#define DEBUG_PRINT_MAIN 0
#define DEBUG_PRINT_MIC 1
#define DEBUG_PRINT_MIC_TIMING 1
#define DEBUG_PRINT_OTHER 1

////////////////////////////////////////////////////////////
/////////                MISC                   ////////////
////////////////////////////////////////////////////////////
/**
 * OVERCLOCK: 0 - Clock default of 133MHz
 *            1 - Clock set to 250MHz
 */
#define OVERCLOCK 0