#include "ShakeelFlash.h"
#include <stdio.h>
#include <math.h>
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"



void ShakeelFlash::init(){
    pixels = new std::vector<SoundPixel*>();
    int stripLen = LEDs::strip(0)->num();
    for(int i = 0; i < stripLen; i++){
        SoundPixel * eff = new SoundPixel();
        //printf("sound pixel size = %d\n", sizeof(SoundPixel));
        eff->i = i;
        eff->hue = 0.0;
        eff->strip = 0;
        Effect::engine->apply(eff);
        pixels->push_back(eff);
    }

    for(int i = 0; i < stripLen; i++){
        SoundPixel * eff = new SoundPixel();
        //printf("sound pixel size = %d\n", sizeof(SoundPixel));
        eff->i = i;
        eff->hue = 0.5;
        eff->strip = 1;
        Effect::engine->apply(eff);
        pixels->push_back(eff);
    }

    secTimer = new Timing();
    avgTimer = new Timing();
    valTimer = new Timing();
}

void ShakeelFlash::run(){
    double micVal = pow(Microphone::getLowNormal(),2) ;
    static double hueAdd = 0;
    static double brightness = 0;
    double seconds = secTimer->takeSeconds();
    int avgLoops = 0;
    // Color movement
    //printf("micTimer = %d ... %f\n", micTimer->timerMs(), micTimer->takeSeconds());
    double micAdd = micVal / 50; // trying to even out timing
    // printf("avgTimer = %d ... %d\n", avgTimer->timerMs());//, avgTimer->takeMsEvery(25));
    avgLoops = avgTimer->takeMsEvery(1);
    for(int i = 0; i < avgLoops; i++){
        hueAdd = (hueAdd*100.0 + micAdd )/101.0;
    }
    
    if(micAdd > hueAdd){
        hueAdd = micAdd;
    }


    // Brightness
    double proposedBrightness = 0.1+(0.9*micVal);
    //printf("valTimer = %d ... %d\n", valTimer->timerMs(), valTimer->takeMsEvery(100));
    avgLoops = valTimer->takeMsEvery(1);
    for(int i = 0; i < avgLoops; i++){
        brightness = (brightness*200.0 + proposedBrightness)/201.0;
    }
    
    if(proposedBrightness > brightness){
        brightness = proposedBrightness;
    }
    



    for(SoundPixel *pixel : *pixels){
        pixel->brightness = brightness;
        pixel->micVal = micVal;
        pixel->hueAdd = hueAdd * seconds*100.0;
    }
}

void ShakeelFlash::release(){

    delete(secTimer);
    delete(avgTimer);
    delete(pixels);
}