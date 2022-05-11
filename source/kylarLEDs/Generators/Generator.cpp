#include "Generator.h"
#include <stdio.h>

Controller *Generator::controller;
Generator::Generator(){


}

void Generator::giveControllerForTiming(Controller *theController){
    controller = theController;
}

int Generator::everyMs(int ms){
    //Return 1 if ms has passed since the last time it this was called
    //Return 0 if not
    uint32_t current_time = controller->getCurrentTimeMillis();
    uint32_t delta = current_time - everyMsLastTime;

    //printf("EveryMS delta=%d, cur%d, last%d\n", delta,current_time, everyMsLastTime);
    if(delta >= ms){
        //Enough time has elapsed
        everyMsLastTime = current_time;
        return 1;
    }else{
        //Not enough time has elapsed
        return 0;
    }

}