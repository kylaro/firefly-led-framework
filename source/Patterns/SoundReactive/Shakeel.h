#pragma once
#include "../Pattern.h"
#include "../../kylarLEDs/Utility/Timing.h"
#include "../../Effects/SoundReactive/SoundPixel.h"
#include <vector>
class Shakeel : public Pattern{

    public:
        using Pattern::Pattern;
        void run();
        void init();
        void release();
    
    private:
        Timing *myTiming;
        int initted = 0;

        std::vector<SoundPixel*> *pixels;
        

};