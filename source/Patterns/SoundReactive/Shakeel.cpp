#include "Shakeel.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void Shakeel::init(){
    myTiming = new Timing();

    for(int i = 0; i < 150; i++){
        ExampleEffect * eff = new ExampleEffect(LEDs);
        eff->i = i;
        Effect::engine->apply(eff);
    }
    //Effect::engine->apply(new ExampleEffect(LEDs));
}

void Shakeel::run(){
    //printf("CORE0 %f %f %f\n", freq_data.low_freq_energy, freq_data.high_freq_energy, freq_data.freq_energy);
}

void Shakeel::release(){
    free(myTiming);
}