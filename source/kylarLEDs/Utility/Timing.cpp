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

// gets seconds since last call, resets timer
double Timing::takeSeconds(){ 
    double seconds = ((double)timerMs())/1000.0;
    reset();
    return seconds;
}

uint32_t Timing::takeMs(){ 
    // gets seconds since last, resets timer
    // not sure if this is working...
    uint32_t ms = timerMs();
    reset();
    return ms;
}

// Neat function, basically can count how many times you've passed the every
uint32_t Timing::takeMsEvery(uint32_t every){ 
    // returns the number of times every has happened and resets
    // so like if you want to loop 1000 times per second, do takeMsEvery(1);
    uint32_t ms = timerMs();
    uint32_t count = ms/every;
    if(count > 0){
        timerStart += 1000*count*every; // shave off those seconds
        return count;
    }else{
        return 0;
    }
    
}

Timing::~Timing(){

}