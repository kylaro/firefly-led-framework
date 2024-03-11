#ifndef WIFI_H
#define WIFI_H

#include "lwip/apps/httpd.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

// External declarations for CGI and SSI handler functionalities
// These are defined in wifi.c but can be used elsewhere if needed

// WIFI Credentials - It's good practice to keep these secure and not hard-coded in your source files
extern const char WIFI_SSID[];
extern const char WIFI_PASSWORD[];

// Initializes the Wi-Fi module and connects to the network
int wifi_init();

// CGI handler declaration
// Handles incoming CGI requests, for example turning an LED on or off via a web interface
const char *cgi_led_handler(int iIndex, int iNumParams, char *pcParam[], char *pcValue[]);

// Initializes CGI handlers for handling specific web requests
void cgi_init(void);

// Tags for Server-Side Includes (SSI) - these tags are placeholders in your web pages that get replaced with actual values
extern const char *ssi_tags[];

// Handler for SSI requests, which replaces SSI tags with actual data
u16_t ssi_handler(int iIndex, char *pcInsert, int iInsertLen);

// Initializes the SSI handler with the tags and the actual function that handles the replacements
void ssi_init();

#endif // WIFI_H
