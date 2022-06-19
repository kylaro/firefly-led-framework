#include "FireFly.h"
#include <stdio.h>
#include "WaveformLED.h"
#include "../../kylarLEDs/Utility/Waveforms/Triangle.h"

void FireFly::init(){
    speed = 1.0;
    position = 0;
    blueprint.brightness = 1;
    blueprint.hue = hue;
    blueprint.index = 0;
    blueprint.Toffset = 0;
    blueprint.Trise = 150;
    blueprint.Thold = 0;
    blueprint.Tfall = 2000;
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
        //Effect::engine->queueApply((new SingleTime())->init(blueprint));
        Effect::engine->queueApply(((new WaveformLED(new Triangle(4000)))->setI(blueprint.index)->setHue(blueprint.hue)->setCount(1)));
    }
    if(speed < 0.1){
        done = 1;
    }
    
    
}

void FireFly::release(){
    done = 1;
    free(timer);
}