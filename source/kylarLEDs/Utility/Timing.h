#pragma once
#include "stdint.h"
#include <time.h>
#include "../Controllers/Controller.h"
class Timing{

    public:
        Timing();
        int everyMs(uint32_t ms);
        uint64_t timerMs(); // First call returns 0 and starts timer, next calls return ms since first call
        static void giveControllerForTiming(Controller *theController);
    private:
        uint32_t everyMsLastTime = 0;
        uint64_t timerStart = 0;
        static Controller *controller;
};