#include "SingleTime.h"
#include "stdio.h"


void SingleTime::init(){
    profile.brightness = 1;
    profile.hue = 0;
    profile.Toffset = 0;
    profile.Trise = 200;
    profile.Thold = 600;
    profile.Tfall = 200;
    initialized = 1;
}

SingleTime* SingleTime::init(single_time_t blueprint){
    profile.index = blueprint.index;
    profile.brightness = blueprint.brightness;
    profile.hue = blueprint.hue;
    profile.Toffset = blueprint.Toffset;
    profile.Trise = blueprint.Trise;
    profile.Thold = blueprint.Thold;
    profile.Tfall = blueprint.Tfall;
    initialized = 1;
    ID = profile.index;
    return this;
}

void SingleTime::run(){
    if(initialized == 0){
        init();
    }
    if(timer == NULL){
        timer = new Timing();
    }
    uint32_t time = timer->timerMs();

    hsv_t color = {profile.hue, 1, profile.brightness};
    if(time < profile.Toffset){
        //We are within offset phase
        return; // Do not write to LEDs
    }else if(time-profile.Toffset < profile.Trise){
        //We are in rise phase
        double brightness = (time - profile.Toffset)/(double)profile.Trise;
        color.v *= brightness;
    }else if(time-profile.Toffset-profile.Trise < profile.Thold){
        // We are in hold phase
        // Color is initialized to the correct value;
    }else if(time-profile.Toffset-profile.Trise-profile.Thold < profile.Tfall){
        // We are in falling phase
        double brightness = 1.0 - (time - profile.Toffset-profile.Trise - profile.Thold)/(double)profile.Tfall;
        color.v *= brightness;
    }else{
        done = 1;
        color.v = 0;
    }
    
    LEDs->setHSV(profile.index, color);
}

void SingleTime::release(){
    done = 1;
    free(timer);
}