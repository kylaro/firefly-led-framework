#include "ExampleEffect.h"


void ExampleEffect::init(){
    
}

void ExampleEffect::run(){
    hue += 0.01;
    hsv_t color = {hue, 1, 1};
    LEDs->setHSV(1, color);
}

void ExampleEffect::release(){
    done = 1;
}