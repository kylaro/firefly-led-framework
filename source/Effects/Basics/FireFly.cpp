#include "FireFly.h"
#include <stdio.h>

void FireFly::init(){
    speed = 1.0;
    position = 0;
    blueprint.brightness = 1;
    blueprint.hue = hue;
    blueprint.index = 0;
    blueprint.Toffset = 0;
    blueprint.Trise = 500;
    blueprint.Thold = 400;
    blueprint.Tfall = 1500;
    timer = new Timing();
    initialized = 1;
}

void FireFly::run(){
    if(initialized == 0){
        init();
    }
    
    if(timer->everyMs(200)){
        // "We have moved!"
        blueprint.index += direction;
        Effect::engine->queueApply((new SingleTime(LEDs))->init(blueprint));
    }
    if(speed < 0.1){
        done = 1;
    }
    
    
}

void FireFly::release(){
    done = 1;
    free(timer);
}