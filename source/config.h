#pragma once
// Welcome to the beautiful config file. Here lies everything you could ever want to configure.


////////////////////////////////////////////////////////////
/////////                 LEDS                  ////////////
////////////////////////////////////////////////////////////
/**
 * NUM_STRIPS is the number of pins to output on.
 * NUM_LEDS is the number of LEDs per strip.
 * BRIGHTNESS_OFFSET is an added brightness. Useful for when no potentiometer.
 * LEDS_OFFSET shift the start and end of the LED strip
 * TODO: Make the strips able to turn on / off output pins.
 * 
 */
#define NUM_STRIPS 2
#define NUM_LEDS 120
#define LEDS_OFFSET 0
#define HARDCODE_BRIGHTNESS 0.5 // Comment this out if you don't want to hardcode the brightness. This overrides the Potentiometer.

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
#define MQTT_ENABLE 0 // picow only.
#define WIFI_ENABLE 0 // picow only.

/**
 * Only set one to 1. Select the type of microphone to compile with.
 */
#define HW_ADC_MIC 0
#define HW_PDM_MIC 1

/**
 * Pin config.
 * For FireFlyV1.2, [20,21] is the linkmems mic, and [12,13] is the ST mic.
 */
#define ADC_MIC_PIN 26
#define PDM_MIC_PIN_DATA 20
#define PDM_MIC_PIN_CLK  21



////////////////////////////////////////////////////////////
/////////                MICROPHONE             ////////////
////////////////////////////////////////////////////////////
/**
 * Signal Processing Options
 */
#define LOW_BINS 20
#define SKIP_BINS 0
#define HIGH_BINS 100


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
#define WIFI_SSID "Starlink"
#define WIFI_PASSWORD "spacelasers42069"
#define AP_WIFI_SSID "picow"
#define AP_WIFI_PASSWORD "12345678"


////////////////////////////////////////////////////////////
/////////                DEBUG                   ////////////
////////////////////////////////////////////////////////////
#define DEBUG_DELAY_MAIN 0 // Used to give time to start Serial Monitoring
#define DEBUG_PRINT_MAIN 0
#define DEBUG_PRINT_MIC 0
#define DEBUG_PRINT_MIC_TIMING 0
#define DEBUG_PRINT_FLASH 0
#define DEBUG_PRINT_OTHER 0

////////////////////////////////////////////////////////////
/////////                MISC                   ////////////
////////////////////////////////////////////////////////////
/**
 * OVERCLOCK: 0 - Clock default of 133MHz
 *            1 - Clock set to 250MHz
 */
#define OVERCLOCK 1