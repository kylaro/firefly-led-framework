#include "ExamplePattern.h"
#include <stdio.h>
#include "../Effects/ExampleEffect.h"

void ExamplePattern::init(){
    myGenerator = new Generator();
}

void ExamplePattern::run(){
    if(myGenerator->everyMs(1000)){
        printf("Generator works!\n");
        effectEngine->apply(new ExampleEffect());
    }
}

void ExamplePattern::release(){
    
}