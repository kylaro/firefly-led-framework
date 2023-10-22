#include "ExampleEffect.h"
#include "stdio.h"

void ExampleEffect::init(){
    
}

void ExampleEffect::run(){
    hue += 0.0005;
    hsv_t color = {hue, 1, 0.07};
    LEDs::setHSV(i, color);
}

ExampleEffect::~ExampleEffect(){
    
}