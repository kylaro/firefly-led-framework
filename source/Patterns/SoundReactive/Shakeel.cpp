#include "Shakeel.h"
#include <stdio.h>
#include "../../Effects/SoundReactive/SoundPixel.h"


void Shakeel::init(){
    myTiming = new Timing();
    double symmetryPoint = LEDs->num()/2;
    for(int i = 0; i < LEDs->num(); i++){
        SoundPixel * eff = new SoundPixel(LEDs);
        eff->i = i;
        if(i < symmetryPoint){
            eff->hue = i/symmetryPoint;
        }else{
            eff->hue = 1.0-((i-symmetryPoint)/symmetryPoint);
        }
        Effect::engine->apply(eff);
    }
}

void Shakeel::run(){

}

void Shakeel::release(){
    free(myTiming);
}