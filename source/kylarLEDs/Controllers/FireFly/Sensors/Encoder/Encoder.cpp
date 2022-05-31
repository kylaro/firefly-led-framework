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
    // Explain: This was intended to subtract from the "frequency" every x seconds (timer based)
    // "frequency" was a count of how fast the encoder was being turned, the idea was to change the color
    // faster if the user is spinning it faster...
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
    //INTERRUPTS NOTE: "Currently GPIO parameter is ignored, callback will be called for any enabled GPIO IRQ on any pin"
    gpio_irq_callback_t callback = &Encoder::interrupt; // warning, spaghetti code, this function is not called by the interrupt...
    // The callback function being called is actually Button::interrupt.... but this is left here to enable this interrupt
    gpio_set_irq_enabled_with_callback(A, GPIO_IRQ_EDGE_RISE, true, callback);
    
    // struct repeating_timer timer;
    // add_repeating_timer_ms(100, &Encoder::frequencyReduce, NULL, &timer);
}