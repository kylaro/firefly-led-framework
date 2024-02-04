#include "LEDs.h"
#include <stdio.h>

std::vector<LEDInterface*> *LEDs::strips;
LEDs::LEDs(){


}



LEDInterface *LEDs::strip(uint8_t strip){
    return strips->at(strip);
}

void LEDs::init(uint8_t numInterfaces){
    ColorUtil::generateRemapLUT();
    strips = new std::vector<LEDInterface*>();
    printf("size of ledinterface = %d\n", sizeof(LEDInterface));
    for(int i = 0; i < numInterfaces; i++){
        LEDInterface *leds = new LEDInterface(i);
        leds->setNum(1); // Setting a default number of LEDs...
        LEDs::strips->push_back(leds);
    }
}

// Sets hsv for all strips
void LEDs::setHSV(int i, hsv_t color){
    irgb8_t irgb;
    int first = 1;
    // The reason the stuff going on here is weird, is to make it faster
    // Using the result of the first setHSV to make the next faster
    for(LEDInterface *strip : *strips){
        if(first){
            irgb = strip->setHSV(i, color);
            first = 0;
        }else{
            //irgb = strip->setHSV(i, color);
            strip->setRGBUnprotected(irgb.i, irgb.rgb);  // This skips the HSV conversion, which saves time
        }
        
    }
}

// Sets rgb for all strips
void LEDs::setRGB(int i, rgb8_t color){
    for(LEDInterface *strip : *strips){
        strip->setRGBUnprotected(i, color);  // This skips the HSV conversion, which saves time
    }
}

void LEDs::setNum(uint16_t num){
    for(LEDInterface *strip : *strips){
        strip->setNum(num);
    }
}

void LEDs::output(){
    for(LEDInterface *strip : *strips){
        strip->output();
    }
}

void LEDs::clear(){
    for(LEDInterface *strip : *strips){
        strip->clear();
    }

}

void LEDs::apply(){
    for(LEDInterface *strip : *strips){
        strip->apply();
    }
}

void LEDs::giveController(Controller * controller){
    for(LEDInterface *strip : *strips){
        strip->giveController(controller);
    }
}