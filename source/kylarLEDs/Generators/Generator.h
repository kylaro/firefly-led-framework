#pragma once
#include "stdint.h"
#include <time.h>
#include "../Controllers/Controller.h"
class Generator{

    public:
        Generator();
        int everyMs(int ms);
        static void giveControllerForTiming(Controller *theController);
    
        uint32_t everyMsLastTime = 0;
        static Controller *controller;
};