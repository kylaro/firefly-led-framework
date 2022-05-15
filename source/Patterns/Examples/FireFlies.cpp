#include "FireFlies.h"
#include <stdio.h>
#include "../../Effects/Basics/FireFly.h"

void FireFlies::init(){
    myTiming = new Timing();
    Effect::engine->apply(new FireFly(LEDs));
    initialized = 1;
}

void FireFlies::run(){
    if(initialized == 0){
        init();
    }
}

void FireFlies::release(){
    
}