#include "Potentiometer.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "stdio.h"
Potentiometer::Potentiometer(int pin, int adc){
    this->pin = pin;
    this->adc = adc;
    adc_init();
    adc_gpio_init(pin);
    adc_select_input(adc);
}

double Potentiometer::getValue(){
    adc_select_input(adc);
    uint32_t result = adc_read();
    double value = ( (double) result)/ (4096.0);
    printf("pot val = %f\n", value);
    return value;
}