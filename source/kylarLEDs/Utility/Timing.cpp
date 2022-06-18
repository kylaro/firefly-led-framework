#include "Timing.h"
#include <stdio.h>

Controller *Timing::controller;
Timing::Timing(){


}

// Static
void Timing::giveControllerForTiming(Controller *theController){
    controller = theController;
}

int Timing::everyMs(uint32_t ms){
    //Return 1 if ms has passed since the last time it this was called
    //Return 0 if not
    uint64_t current_time = controller->getCurrentTimeMillis();
    uint64_t delta = current_time - everyMsLastTime;

    if(delta >= ms){
        //Enough time has elapsed
        everyMsLastTime = current_time;
        return 1;
    }else{
        //Not enough time has elapsed
        return 0;
    }

}

uint64_t Timing::timerMs(){
    if(timerStart == 0){
        //First call, initialize timer:
        timerStart = controller->getCurrentTimeMicros();
        return 0;
    }else{
        return (controller->getCurrentTimeMicros() - timerStart)/1000;
    }

}

uint64_t Timing::timerUs(){
    if(timerStart == 0){
        //First call, initialize timer:
        timerStart = controller->getCurrentTimeMicros();
        return 0;
    }else{
        return controller->getCurrentTimeMicros() - timerStart;
    }
}


void Timing::reset(){
    timerStart = controller->getCurrentTimeMicros();
}

