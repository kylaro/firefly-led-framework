#include "SpaceX.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"



SpaceX::~SpaceX() {}

void SpaceX::init(){
    // myTiming = new Timing();
    // int stripLen = LEDs::strip(0)->num();
    // for(int i = 0; i < stripLen; i++){
    //ExampleEffect * eff = new ExampleEffect();
    //     eff->i = i;
    //     eff->hue = i/(double)stripLen;
    //Effect::engine->apply(eff);
    // }
    SpaceXLogo *logo = new SpaceXLogo();
    Effect::engine->apply(logo);
}

void SpaceX::run(){
    
}

void SpaceX::release(){
    delete(myTiming);
}