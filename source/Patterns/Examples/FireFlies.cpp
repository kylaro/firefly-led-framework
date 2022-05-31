#include "FireFlies.h"
#include <stdio.h>
#include "../../Effects/Basics/FireFly.h"

void FireFlies::init(){
    myTiming = new Timing();
    Effect::engine->apply(new FireFly(LEDs));
    FireFly *greenFireFly = new FireFly(LEDs);
    greenFireFly->hue = 0.33;
    greenFireFly->direction = -1;
    Effect::engine->apply(greenFireFly);
    initialized = 1;
}

void FireFlies::run(){
    if(initialized == 0){
        init();
    }
}

void FireFlies::release(){
    free(myTiming);
}