#pragma once
#include "../Pattern.h"
#include "../../kylarLEDs/Utility/Timing.h"

class SpaceX : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();
        virtual ~SpaceX();
    
    private:
        Timing *myTiming;
        int initted = 0;
        

};