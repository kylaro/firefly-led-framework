#include "Ben.h"
#include <stdio.h>
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"



void Ben::init(){
    int stripLen = LEDs::strip(0)->num();
    float symmetryPoint = stripLen/2;
}

void Ben::run(){
    double micVal = Microphone::getLowNormal();
    printf("Mic val: %f\n",micVal);
    if(micVal > 0.95) {
        printf("Mic val > 0.95\n");
        FireFly *leftFly = new FireFly();
        leftFly->init();
        leftFly->blueprint.hue = 0;
        leftFly->direction = 1;
        leftFly->blueprint.index = 0;

        FireFly *rightFly = new FireFly();
        rightFly->init();
        rightFly->blueprint.hue = 0.5;
        rightFly->direction = -1;
        rightFly->blueprint.index = 0;

        Effect::engine->apply(leftFly);
        Effect::engine->apply(rightFly);
    }
}

void Ben::release(){

}