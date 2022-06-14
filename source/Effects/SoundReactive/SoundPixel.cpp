#include "SoundPixel.h"
#include "stdio.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void SoundPixel::init(){
    
}

void SoundPixel::run(){
    static double brightness = 1;
    //hue += 0.0015 + Microphone::getLowEnergy()/50000.0;
    hue += 0.001 + Microphone::getLowNormal()/100.0; // 0.01- 0.001
    //SHAKEEL'S REQUEST:
    // fast rise, slow decay
    //make smooth brightness decrease
    //hsv_t color = {hue, 1, (fmax(Microphone::getLowEnergy()-100, 0))/500.0+0.75};
    double proposedBrightness = 0.5+(Microphone::getLowNormal()/2);
    if(proposedBrightness > brightness){
        brightness = proposedBrightness;
    }else{
        brightness = (brightness*1000.0 + proposedBrightness)/1001.0;
    }
    hsv_t color = {hue, 1, brightness};
    LEDs->setHSV(i, color);
}

void SoundPixel::release(){
    done = 1;
}
