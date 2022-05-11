#include "ExamplePattern.h"
#include <stdio.h>

void ExamplePattern::init(){
    myGenerator = new Generator();
}

void ExamplePattern::run(){
    if(myGenerator->everyMs(1000)){
        printf("Generator works!\n");
    }
}

void ExamplePattern::release(){
    
}