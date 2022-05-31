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
    this->timing = new Timing();
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

    for(int i = 0; i < 10; i++){
        gpio_put(LED_PIN, 1);
        sleep_ms(30);
        gpio_put(LED_PIN, 0);
        sleep_ms(30);
    }
    gpio_put(LED_PIN, 1);

    printf("Communication established\n");

    // How to overclock (or underclock!)
    // if (!set_sys_clock_khz(250000, false)){
    //   printf("system clock 250MHz failed\n");
    // }else{
    //   printf("system clock now 250MHz\n");
    // }
}


uint64_t FireFlyController::getCurrentTimeMillis(){
    absolute_time_t new_time = get_absolute_time(); //Microseconds
    uint64_t millis = new_time / 1000;
    return millis;
}

void FireFlyController::outputLEDs(uint8_t *leds, uint32_t N){
    uint32_t numBytes = N*3;
    uint8_t *pixels = leds;
    while(numBytes--){
        // Bits for transmission must be shifted to top 8 bits
        pio_sm_put_blocking(PX_pio, PX_sm, ((uint32_t)*pixels++)<< 24);
    }
    sleep_ms(1);
}

double FireFlyController::getBrightness(){
    static double brightness = 0;
    
    if(timing->everyMs(10)){
        brightness = analogPot->getValue();
    }else{
        return brightness;
    }
    double threshold = 0.03;
    if(brightness < threshold){
        brightness = 0;
    }else{
        brightness -= threshold;
    }
    return brightness;
}

double FireFlyController::getHue(){
    int count = encoder->getCount();
    //count *= 2;
    double hue = (count)/360.0;
    //printf("hue set to %f\n", hue);
    return hue;
}

void FireFlyController::initHue(){
    encoder = new Encoder(26, 22);

}

void FireFlyController::initBrightness(){
    this->analogPot = new Potentiometer(27, 1);
}

void FireFlyController::initPatternButton(){
    this->button = new Button(28);
}

void FireFlyController::givePatternIndex(uint32_t *patternIndex){
    this->patternIndex = patternIndex;
    Button::givePatternIndex(this->patternIndex);
}