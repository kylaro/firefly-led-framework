#include "ExamplePattern.h"
#include <stdio.h>
#include "../../Effects/Examples/ExampleEffect.h"

void ExamplePattern::init(){
    myGenerator = new Generator();
    effectEngine->apply(new ExampleEffect(LEDs));
}

void ExamplePattern::run(){
    if(myGenerator->everyMs(1000)){
        printf("Generator works!\n");
    }
}

void ExamplePattern::release(){
    
}