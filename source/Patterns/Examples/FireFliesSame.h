#pragma once
#include "../Pattern.h"
#include "../../kylarLEDs/Utility/Timing.h"

class FireFliesSame : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();
    
    private:
        Timing *myTiming;
        

};