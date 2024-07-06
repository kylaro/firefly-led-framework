#include "stdio.h"
#include "WiFi/WiFi.h"
#include "Network.h"
#include "Credentials.h"
#include "pico/time.h"
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"

int status;

void Network::connect() {

  cyw43_arch_init();

  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

  cyw43_arch_enable_sta_mode();

  // Connect to the WiFI network - loop until connected
  while(cyw43_arch_wifi_connect_timeout_ms(WIFI_SSID, WIFI_PASSWORD, CYW43_AUTH_WPA2_AES_PSK, 10000) != 0){
    printf("Attempting to connect...\n");
    sleep_ms(50);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(350);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
  }
  // Print a success message once connected
  printf("Connected! \n");
  for(int i = 0; i < 10; i++){
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);
    sleep_ms(50);
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    sleep_ms(50);
  }

  cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 1);

  // Kylar's note: The below code was the original here.
  // It will compile, however, it will on this line:
  //    async_context_add_when_pending_worker(_context, &always_pending_update_timeout_worker);
  //
  // So, instead, I'm proceeding using the more pico style of wifi connecting.
  // Leaving the below Arduino style for reference, and all the code in the WiFi folder is for this.
  // WiFi folder code is mostly from framework-arduinopico/ArduinoCore-API/
  //   while (status != WL_CONNECTED) {

  //   printf("Attempting to connect to WPA SSID: %s\n", WIFI_SSID);

  //   // Connect to WPA/WPA2 network:

  //   status = WiFi.begin(WIFI_SSID, WIFI_PASSWORD); //Set these credentials

  //   // wait to connect:

  //   sleep_ms(5000);

  // }

  // if (status == WL_CONNECTED) {
  //   printf("Connected to %s\n", WIFI_SSID);
  // }else{
  //   printf("Connection error status = %d\n", status);
  // }
}