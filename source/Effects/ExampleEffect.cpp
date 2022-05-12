#include "ExampleEffect.h"


void ExampleEffect::init(){
    
}

void ExampleEffect::run(){
    hue += 0.1;
    hsv_t color = {hue, 1, 1};
    LEDs->setHSV(1, color);
}

void ExampleEffect::release(){

}