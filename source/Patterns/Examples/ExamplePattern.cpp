#include "ExamplePattern.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"

void ExamplePattern::init(){
    printf("example pattern init\n");
    myTiming = new Timing();
    printf("new timing\n");
    for(int i = 0; i < 150; i++){
        ExampleEffect * eff = new ExampleEffect(LEDs);
        eff->i = i;
        Effect::engine->apply(eff);
    }
    //Effect::engine->apply(new ExampleEffect(LEDs));
    printf("effect engine applied\n");
}

void ExamplePattern::run(){
    
}

void ExamplePattern::release(){
    free(myTiming);
}