#include "Button.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include "stdio.h"
#include "../Encoder/Encoder.h"

uint8_t Button::pin;
uint32_t* Button::patternIndex;

void Button::interrupt(uint gpio, uint32_t event){
    if(gpio != pin){
        Encoder::interrupt(gpio, event);
        return;
    }
    static absolute_time_t last_time = {0};
    static int press_state = 0;// 0 Waiting for press, 1 waiting for release
    absolute_time_t new_time = get_absolute_time();
    

    if(absolute_time_diff_us(last_time, new_time) < 30000){ //30ms
        return;
    }


    if(press_state == 0){
        (*Button::patternIndex)++; // Increment pattern index
        press_state = 1;
    }else{
        press_state = 0;
    }

    last_time = new_time;
    
}

void Button::givePatternIndex(uint32_t *patternIndex){
    Button::patternIndex = patternIndex;
}


Button::Button(int A){
    //Inputs:
    Button::pin = A;
    gpio_init(A);
    gpio_set_dir(A, GPIO_IN);
    gpio_pull_up(A);//Set PULL UP
    //INTT//INTERRUPTS NOTE: "Currently GPIO parameter is ignored, callback will be called for any enabled GPIO IRQ on any pin"
    //This is spaghetti code, to fix this I am thinking to make a static "Interrupts" class that all interrupts can be handled by 1
    //The objects would be added to the Interrupts class static list so that all of their interrupt functions get called or basedon their gpio
    gpio_irq_callback_t callback = &Button::interrupt;
    gpio_set_irq_enabled_with_callback(A, GPIO_IRQ_EDGE_FALL, true, callback);
}