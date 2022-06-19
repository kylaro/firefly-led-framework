#pragma once
#include "stdint.h"
#include <time.h>
#include "../Controllers/Controller.h"
class Timing{

    public:
        Timing();
        ~Timing();
        int everyMs(uint32_t ms);
        uint64_t timerMs(); // First call returns 0 and starts timer, next calls return ms since first call
        uint64_t timerUs();
        double takeSeconds(); // gets seconds since last, resets timer
        uint32_t takeMs();
        uint32_t takeMsEvery(uint32_t every); // don't reset if below every
        void reset();
        static void giveControllerForTiming(Controller *theController);
    private:
        uint32_t everyMsLastTime = 0;
        uint64_t timerStart = 0; // MICROSECONDS
        static Controller *controller;
};