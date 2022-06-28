#include "SoundPixel.h"
#include "stdio.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void SoundPixel::init(){
    
}

void SoundPixel::run(){
    hue += hueAdd; // 0.01- 0.001
    
    // Output
    hsv_t color = {hue, 1, brightness};
    LEDs::setHSV(i, color);
}

SoundPixel::~SoundPixel(){
    done = 1;
}
