#include "ExampleEffect.h"
#include "stdio.h"

void ExampleEffect::init(){
    
}

void ExampleEffect::run(){
    hue += 0.0015;
    hsv_t color = {hue, 1, 1};
    LEDs::setHSV(i, color);
}

ExampleEffect::~ExampleEffect(){
    
}