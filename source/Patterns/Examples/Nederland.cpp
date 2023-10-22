#include "Nederland.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/CO2/CO2.h"


void Nederland::init(){
    myTiming = new Timing();
    int stripLen = LEDs::strip(0)->num();
    for(int i = 0; i < stripLen; i++){
        ExampleEffect * eff = new ExampleEffect();
        eff->i = i;
        eff->hue = i/(double)stripLen;
        Effect::engine->apply(eff);
    }

}

void Nederland::run(){
    // Read the CO2
    double co2 = CO2::getCO2();
}

void Nederland::release(){
    delete(myTiming);
}