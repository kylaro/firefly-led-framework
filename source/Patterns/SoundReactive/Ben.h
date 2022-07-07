#pragma once
#include "../Pattern.h"
#include "../../kylarLEDs/Utility/Timing.h"
#include "../../Effects/Basics/Firefly.h"
#include <vector>
class Ben : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();
    
    private:
        Timing *myTiming;        

};