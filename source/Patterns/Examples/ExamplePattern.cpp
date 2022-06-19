#include "ExamplePattern.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void ExamplePattern::init(){
    myTiming = new Timing();
    int stripLen = LEDs::strip(0)->num();
    for(int i = 0; i < stripLen; i++){
        ExampleEffect * eff = new ExampleEffect();
        eff->i = i;
        eff->hue = i/stripLen;
        Effect::engine->apply(eff);
    }

}

void ExamplePattern::run(){
    
}

void ExamplePattern::release(){
    delete(myTiming);
}