#include "CircleEffect.h"
#include "stdio.h"
#include <math.h>

void CircleEffect::init(){
    // initialize vector pixels
    pixels = new std::vector<uint8_t>();
    
}

// Adds LED to list of LEDs to be affected by this effect
CircleEffect* CircleEffect::led(uint8_t i){
    pixels->push_back(i);
    return this;
}

void CircleEffect::calculate(double phase){
    hsv_t color = {hue/10.0, 1, 0};
    hue += phase/12.0;
    for(int i = 0; i < pixels->size(); i++){
        // sample sin wave to get v
        color.v = ((sin(hue + (i*2*3.1415)/pixels->size())+1)/2)*.45 + phase*.55;
        color.v *= color.v;
        color.h = hue/15.0 + i/(double)pixels->size()*(0.15+phase*.45);
        LEDs::setHSV(pixels->at(i), color);
    }
}

void CircleEffect::white(double val){
    hsv_t color = {0, 0, val};
    for(int i = 0; i < pixels->size(); i++){
        LEDs::setHSV(pixels->at(i), color);
    }
}

void CircleEffect::run(){
    //hue += 0.0015;
    
    
    
    // for(int i = 0; i < pixels->size(); i++){
        
    //     //LEDs::setHSV(pixels->at(i), color);
    // }
}

CircleEffect::~CircleEffect(){
    // free vector pixels
    delete pixels;
    
}