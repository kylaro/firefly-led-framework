#include "SoundPixel.h"
#include "stdio.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void SoundPixel::init(){
    
}

void SoundPixel::run(){
    //hue += added in shakeel pattern...
    
    // Output
    hsv_t color = {hue, 1, brightness};
    LEDs::setHSV(i, color);
}

void SoundPixel::release(){
    done = 1;
}

SoundPixel::~SoundPixel(){

}
