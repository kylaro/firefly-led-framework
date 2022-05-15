#include "ExamplePattern.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"

void ExamplePattern::init(){
    myTiming = new Timing();
    Effect::engine->apply(new ExampleEffect(LEDs));
}

void ExamplePattern::run(){
    if(myTiming->everyMs(1000)){
        printf("TimingGenerator works!\n");
    }
}

void ExamplePattern::release(){
    
}