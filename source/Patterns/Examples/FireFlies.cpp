#include "FireFlies.h"
#include <stdio.h>
#include "../../Effects/Basics/FireFly.h"

void FireFlies::init(){
    myTiming = new Timing();
    
    FireFly *cyanFly = new FireFly(LEDs);
    cyanFly->init();
    cyanFly->blueprint.hue = 0;
    cyanFly->direction = 1;
    cyanFly->blueprint.index = 0;

    FireFly *yellowFly = new FireFly(LEDs);
    yellowFly->init();
    yellowFly->blueprint.hue = 0.25;
    yellowFly->direction = 1;
    yellowFly->blueprint.index = (int)LEDs->num()/2;

    FireFly *magentaFly = new FireFly(LEDs);
    magentaFly->init();
    magentaFly->blueprint.hue = 0.5;
    magentaFly->direction = -1;
    magentaFly->blueprint.index = (int)LEDs->num()/2;

    FireFly *lastFly = new FireFly(LEDs);
    lastFly->init();
    lastFly->blueprint.hue = 0.75;
    lastFly->direction = -1;
    lastFly->blueprint.index = 0;

    Effect::engine->apply(cyanFly);
    Effect::engine->apply(yellowFly);
    Effect::engine->apply(magentaFly);
    Effect::engine->apply(lastFly);
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