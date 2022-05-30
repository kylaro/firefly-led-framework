#include "Button.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

uint8_t Button::pin;
uint32_t* Button::patternIndex;

void Button::interrupt(uint gpio, uint32_t event){
    (*Button::patternIndex)++; // Increment pattern index
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
    gpio_irq_callback_t callback = &Button::interrupt;
    gpio_set_irq_enabled_with_callback(A, GPIO_IRQ_EDGE_FALL, true, callback);
}