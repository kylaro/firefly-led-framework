#include "FireFlyController.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"


FireFlyController::FireFlyController(){
    initCommunication();
    initBrightness();
    initHue();
    initPatternButton();
    initOutput();
}

void FireFlyController::initOutput(){
    

    uint offset = pio_add_program(PX_pio, &ws2812_program);

    gpio_init(PX_pin);
    gpio_set_dir(PX_pin, GPIO_OUT);
    gpio_put(PX_pin, 0);

    // 800kHz, 8 bit transfers
    ws2812_program_init(PX_pio, PX_sm, offset, PX_pin, 800000, 8);
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
    printf("Communication established\n");
}


uint32_t FireFlyController::getCurrentTimeMillis(){
    absolute_time_t new_time = get_absolute_time(); //Microseconds
    uint32_t millis = new_time /= 1000;
    return millis;
}

void FireFlyController::outputLEDs(uint8_t *leds, uint32_t N){
    uint32_t numBytes = N*3;
    uint8_t *pixels = leds;
    while(numBytes--){
        // Bits for transmission must be shifted to top 8 bits
        pio_sm_put_blocking(PX_pio, PX_sm, ((uint32_t)*pixels++)<< 24);
    }
    sleep_ms(50);
}

void FireFlyController::initHue(){

}

void FireFlyController::initBrightness(){
    
}

void FireFlyController::initPatternButton(){
    
}