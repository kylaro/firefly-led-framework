#include "ExamplePattern.h"
#include <stdio.h>
#include "../../Effects/Examples/ExampleEffect.h"

void ExamplePattern::init(){
    myTiming = new Timing();
    effectEngine->apply(new ExampleEffect(LEDs));
}

void ExamplePattern::run(){
    if(myTiming->everyMs(1000)){
        printf("TimingGenerator works!\n");
    }
}

void ExamplePattern::release(){
    
}