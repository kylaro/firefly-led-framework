#include "WaveformLED.h"
#include "stdio.h"

WaveformLED::WaveformLED(Waveform * waveform){
    wave = waveform;
}

void WaveformLED::init(){

}

void WaveformLED::run(){
    hsv_t color = {hue, 1, wave->value()};
    if(  (count > 0) &&  wave->complete() >= count){
        // The finish condition
        done = 1;
        LEDs::setHSV(i, {0,0,0});
    }else{
        LEDs::setHSV(i, color);
    }
}

void WaveformLED::release(){
    //delete(wave);
}

WaveformLED::~WaveformLED(){
    delete(wave);
}


WaveformLED* WaveformLED::setI(int i){
    this->i = i;
    return this;
}
WaveformLED* WaveformLED::setCount(int count){
    this->count = count;
    return this;
}
WaveformLED* WaveformLED::setHue(double hue){
    this->hue = hue;
    return this;

}