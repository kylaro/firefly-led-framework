#include "ExamplePattern.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void ExamplePattern::init() {
    myTiming = new Timing();

    for(int i = 0; i < LEDs->num(); i++){
        ExampleEffect * eff = new ExampleEffect(LEDs);
        eff->i = i;
        eff->hue = i/LEDs->num();
        Effect::engine->apply(eff);
    }

}

void ExamplePattern::run(){
    
}

void ExamplePattern::release(){
    free(myTiming);
}