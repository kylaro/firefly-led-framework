#include "SoundPixel.h"
#include "stdio.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void SoundPixel::init(){
    
}

void SoundPixel::run(){
    static double brightness = 1;
    
    hue += 0.001 + hueAdd; // 0.01- 0.001
    
    // Brightness
    double proposedBrightness = 0.5+(micVal/2);
    if(proposedBrightness > brightness){
        brightness = proposedBrightness;
    }else{
        brightness = (brightness*1000.0 + proposedBrightness)/1001.0;
    }

    // Output
    hsv_t color = {hue, 1, brightness};
    LEDs->setHSV(i, color);
}

void SoundPixel::release(){
    done = 1;
}

SoundPixel::~SoundPixel(){

}
