#pragma once
#include "../Pattern.h"
#include "../../kylarLEDs/Utility/Timing.h"
//include circle effect
#include "../../Effects/SoundReactive/CircleEffect.h"

class CirclesPattern : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();
    
    private:
        int initted = 0;
        // vector of CircleEffect
        std::vector<CircleEffect*> *inner_circles;
        std::vector<CircleEffect*> *outer_circles;
        Timing *avgTimer;
        Timing *secTimer;
        Timing *valTimer;

        

};