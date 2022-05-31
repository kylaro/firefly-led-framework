#include "ExamplePattern.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"

void ExamplePattern::init(){
    printf("example pattern init\n");
    myTiming = new Timing();
    printf("new timing\n");
    Effect::engine->apply(new ExampleEffect(LEDs));
    printf("effect engine applied\n");
}

void ExamplePattern::run(){
    if(myTiming->everyMs(1000)){
        printf("TimingGenerator works!\n");
    }
}

void ExamplePattern::release(){
    free(myTiming);
}