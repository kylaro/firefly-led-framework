#include "FireFliesSame.h"
#include <stdio.h>
#include "../../Effects/Basics/FireFly.h"

void FireFliesSame::init(){
    myTiming = new Timing();
    Effect::engine->apply(new FireFly());
    FireFly *greenFireFly = new FireFly();
    greenFireFly->init();
    greenFireFly->blueprint.hue = 0;
    greenFireFly->direction = 1;
    greenFireFly->blueprint.index = 44;
    Effect::engine->apply(greenFireFly);
    initialized = 1;
}

void FireFliesSame::run(){
    if(initialized == 0){
        init();
    }
}

void FireFliesSame::release(){
    free(myTiming);
}