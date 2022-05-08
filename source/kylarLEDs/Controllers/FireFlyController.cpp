#include "FireFlyController.h"
#include "pico/stdlib.h"
#include <stdio.h>

FireFlyController::FireFlyController(){
    initCommunication();
}

void FireFlyController::initCommunication(){
    int LED_PIN = 25; // Built-in LED pin
    stdio_init_all();
    //Initialize built-in LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, 0);
    sleep_ms(1000);
    gpio_put(LED_PIN, 1);
    sleep_ms(500);
    gpio_put(LED_PIN, 0);
    sleep_ms(500);
    gpio_put(LED_PIN, 1);




    sleep_ms(100);
    printf("my value = %d\n", this->value);
}