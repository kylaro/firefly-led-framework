#include "FireFlyController.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"

FireFlyController::FireFlyController(){
    initCommunication();
    initBrightness();
    initHue();
    initPatternButton();
    
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
    sleep_ms(5000);
    printf("Communication established");
}


uint32_t FireFlyController::getCurrentTimeMillis(){
    absolute_time_t new_time = get_absolute_time(); //Microseconds
    uint32_t millis = new_time /= 1000;
    return millis;
}

void FireFlyController::outputLEDs(uint32_t *leds, uint32_t N){

}

void FireFlyController::initHue(){

}

void FireFlyController::initBrightness(){
    
}

void FireFlyController::initPatternButton(){
    
}