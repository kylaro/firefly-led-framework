#include "Encoder.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/time.h"

int Encoder::count = 0;
int Encoder::frequency = 0;
uint8_t Encoder::pinB;
uint8_t Encoder::pinA;
void Encoder::interrupt(uint gpio, uint32_t event){
    static absolute_time_t last_time = 0;
    absolute_time_t new_time = get_absolute_time();

    //printf("EN Interrupt gp%d\tevent=%d",gpio, event);

    if(absolute_time_diff_us(last_time, new_time) < 2000){ //2ms
        return;
    }
    last_time = new_time;
    //Encoder::frequency++;
    // EN_A rising edge:
    if(gpio_get(Encoder::pinB)){
        Encoder::count+= 1;//Encoder::frequency;
    }else{
        Encoder::count-= 1;//Encoder::frequency;
    }
}

bool Encoder::frequencyReduce(struct repeating_timer *t){
    if(Encoder::frequency > 1){
        Encoder::frequency--;
    }
    return true;
}

int Encoder::getCount(){
    return Encoder::count;
}

Encoder::Encoder(int A, int B){
    //Inputs:
    Encoder::pinA = A;
    Encoder::pinB = B;
    gpio_init(A);
    gpio_init(B);
    gpio_set_dir(A, GPIO_IN);
    gpio_set_dir(B, GPIO_IN);
    gpio_pull_up(A);//Set PULL UP
    gpio_pull_up(B);//Set PULL UP
    gpio_irq_callback_t callback = &Encoder::interrupt;
    gpio_set_irq_enabled_with_callback(A, GPIO_IRQ_EDGE_RISE, true, callback);
    
    // struct repeating_timer timer;
    // add_repeating_timer_ms(100, &Encoder::frequencyReduce, NULL, &timer);
}