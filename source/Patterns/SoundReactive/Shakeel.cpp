#include "Shakeel.h"
#include <stdio.h>
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"



void Shakeel::init(){
    pixels = new std::vector<SoundPixel*>();
    int stripLen = LEDs::strip(0)->num();
    double symmetryPoint = stripLen/2 ;
    for(int i = 0; i < stripLen; i++){
        SoundPixel * eff = new SoundPixel();
        eff->i = i;
        if(i < symmetryPoint){
            eff->hue = i/symmetryPoint;
        }else{
            eff->hue = 1.0-((i-symmetryPoint)/symmetryPoint);
        }
        Effect::engine->apply(eff);
        pixels->push_back(eff);
    }

    secTimer = new Timing();
    avgTimer = new Timing();
    valTimer = new Timing();
}

void Shakeel::run(){
    double micVal = Microphone::getLowNormal();
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
    double proposedBrightness = 0.5+(micVal/2);
    //printf("valTimer = %d ... %d\n", valTimer->timerMs(), valTimer->takeMsEvery(100));
    avgLoops = valTimer->takeMsEvery(1);
    for(int i = 0; i < avgLoops; i++){
        brightness = (brightness*100.0 + proposedBrightness)/101.0;
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

void Shakeel::release(){

    free(secTimer);
    free(avgTimer);
    free(pixels);
}