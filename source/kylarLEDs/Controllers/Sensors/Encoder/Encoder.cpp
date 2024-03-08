#include "Encoder.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"
#include <stdio.h>
int Encoder::count = 0;
int Encoder::frequency = 0;

uint8_t Encoder::pinA;
uint8_t Encoder::pinB;

void Encoder::interrupt(uint gpio, uint32_t event)
{
    static absolute_time_t last_time = 0;
    static double velocity = 0; // measure how many times the encoder has been turned in the last second
    absolute_time_t new_time = get_absolute_time();

    if (absolute_time_diff_us(last_time, new_time) < 2000)
    { // 2ms
        return;
    }

    uint64_t time_delta = absolute_time_diff_us(last_time, new_time);

    velocity = (1000000.0 / (double)time_delta );
    //0 - 10 : intentional
    //10-20 : normal
    // 20+ : fast
    int add = 1 + (int)velocity / 10; // scale 


    last_time = new_time;
   
    //  EN_A rising edge:
    if (gpio_get(Encoder::pinB))
    {
        Encoder::count += add; 
    }
    else
    {
        Encoder::count -= add; 
    }
}


int Encoder::getCount()
{
    return Encoder::count;
}

Encoder::Encoder(int A, int B)
{
    // Inputs:
    Encoder::pinA = A;
    Encoder::pinB = B;
    gpio_init(A);
    gpio_init(B);
    gpio_set_dir(A, GPIO_IN);
    gpio_set_dir(B, GPIO_IN);
    gpio_pull_up(A); // Set PULL UP
    gpio_pull_up(B); // Set PULL UP
    // INTERRUPTS NOTE: "Currently GPIO parameter is ignored, callback will be called for any enabled GPIO IRQ on any pin"
    gpio_irq_callback_t callback = &Encoder::interrupt; // warning, spaghetti code, this function is not called by the interrupt...
    // The callback function being called is actually Button::interrupt.... but this is left here to enable this interrupt
    gpio_set_irq_enabled_with_callback(A, GPIO_IRQ_EDGE_RISE, true, callback);

    
}