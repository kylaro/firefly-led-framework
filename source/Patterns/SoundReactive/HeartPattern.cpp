#include "HeartPattern.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"



HeartPattern::~HeartPattern() {}

void HeartPattern::init(){
    Heart *heart = new Heart();
    heart->init();
    Effect::engine->apply(heart);

    secTimer = new Timing();
    avgTimer = new Timing();
    valTimer = new Timing();
}

void HeartPattern::run(){
    double micVal = pow(Microphone::getLowNormal(),2) ;
    static double brightness = 0;
    static double highVal = 0;
    double result = 0;
    double seconds = secTimer->takeSeconds();
    int avgLoops = 0;
    // Color movement
    //printf("micTimer = %d ... %f\n", micTimer->timerMs(), micTimer->takeSeconds());

    // printf("avgTimer = %d ... %d\n", avgTimer->timerMs());//, avgTimer->takeMsEvery(25));
    avgLoops = avgTimer->takeMsEvery(1);


    // Brightness
    double proposedBrightness = (micVal);
    //printf("valTimer = %d ... %d\n", valTimer->timerMs(), valTimer->takeMsEvery(100));
    avgLoops = valTimer->takeMsEvery(1);
    for(int i = 0; i < avgLoops; i++){
        //brightness = (brightness*120.0 + proposedBrightness)/121.0;
        if(proposedBrightness > brightness){
            //increasing
            brightness = (brightness*120.0 + proposedBrightness) / 121.0;
        }else{
            //decreasing
            brightness = (brightness*120.0 + proposedBrightness) / 121.0; // 120
        }

        if(Microphone::getHighNormal() > highVal){
            highVal = (highVal*50.0 + Microphone::getHighNormal()) / 51.0;
        }else{
            highVal = (highVal*50.0 + Microphone::getHighNormal()) / 51.0;//25
        }
        
        
    }
    if(highVal > 1){
        highVal = 1;
    }
    
    if(proposedBrightness > brightness){
        brightness = proposedBrightness;
    }

    if(brightness > highVal){
        result = brightness + highVal * 0.1;
    }else{
        result = highVal + brightness * 0.1;
    }
    
    heart->setBrightness((float)result);
}

void HeartPattern::release(){
    delete(secTimer);
    delete(avgTimer);
    delete(valTimer);
    delete(heart);
}