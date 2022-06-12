#include "SoundPixel.h"
#include "stdio.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void SoundPixel::init(){
    
}

void SoundPixel::run(){
    hue += 0.0015 + Microphone::getLowEnergy()/50000.0;
    hsv_t color = {hue, 1, (fmax(Microphone::getLowEnergy()-100, 0))/500.0+0.75};
    LEDs->setHSV(i, color);
}

void SoundPixel::release(){
    done = 1;
}