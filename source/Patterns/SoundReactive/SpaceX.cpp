#include "SpaceX.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"



SpaceX::~SpaceX() {}

void SpaceX::init(){
    SpaceXLogo *spacex_logo = new SpaceXLogo();
    Effect::engine->apply(spacex_logo);

    secTimer = new Timing();
    avgTimer = new Timing();
    valTimer = new Timing();
}

void SpaceX::run(){

    double micVal = pow(Microphone::getLowNormal(),2) ;
    static double brightness = 0;
    double seconds = secTimer->takeSeconds();
    int avgLoops = 0;
    // Color movement
    //printf("micTimer = %d ... %f\n", micTimer->timerMs(), micTimer->takeSeconds());
    double micAdd = micVal / 50; // trying to even out timing
    // printf("avgTimer = %d ... %d\n", avgTimer->timerMs());//, avgTimer->takeMsEvery(25));
    avgLoops = avgTimer->takeMsEvery(1);


    // Brightness
    double proposedBrightness = (micVal);
    //printf("valTimer = %d ... %d\n", valTimer->timerMs(), valTimer->takeMsEvery(100));
    avgLoops = valTimer->takeMsEvery(1);
    for(int i = 0; i < avgLoops; i++){
        brightness = (brightness*120.0 + proposedBrightness)/121.0;
    }
    
    if(proposedBrightness > brightness){
        brightness = proposedBrightness;
    }
    
    spacex_logo->setBrightness((float)brightness);
}

void SpaceX::release(){
    delete(secTimer);
    delete(avgTimer);
    delete(valTimer);
    delete(spacex_logo);
}