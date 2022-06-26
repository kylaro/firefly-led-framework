#include "SoundPixel.h"
#include "stdio.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void SoundPixel::init(){
    
}

void SoundPixel::run(){
    //hue += added in shakeel pattern...
    sat = ((float)i/(float)NUM_LEDS);
    // Output
    hsv_t color = {hue, sat, brightness};
    //hsv_t color = {0, 1, 1};
    LEDs::setHSV(i, color);
}

void SoundPixel::release(){
    done = 1;
}

SoundPixel::~SoundPixel(){

}
