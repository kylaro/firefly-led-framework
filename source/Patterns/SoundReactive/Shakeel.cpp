#include "Shakeel.h"
#include <stdio.h>
#include "../../Effects/SoundReactive/SoundPixel.h"


void Shakeel::init(){
    myTiming = new Timing();

    for(int i = 0; i < LEDs->num(); i++){
        SoundPixel * eff = new SoundPixel(LEDs);
        eff->i = i;
        eff->hue = i/LEDs->num();
        Effect::engine->apply(eff);
    }
}

void Shakeel::run(){
    
}

void Shakeel::release(){
    free(myTiming);
}