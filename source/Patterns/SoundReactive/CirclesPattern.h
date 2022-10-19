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
        CircleEffect* highLEDs;
        Timing *avgTimer;
        Timing *secTimer;
        Timing *valTimer;

        // int8_t x_points[] =  {-32, -13, 13, 31, 44, 15, -15, -45, -88, -69, -34, 35, 69, 89, 92, 62, 37, 0, -37, -61, -92, -73, -16, 16, 75, 121, 105, 90, 65, 44, 11, -11, -45, -65, -89, -106, -120, -61, -30, 29, 114, 95, 61, 41, 20, 20, 20, 20, 20, 41, 75, 114, 96, 62, -20, -20, -20, -20, -20, -41, -95, -114, -114, -76, -41, -62, -95, -121, -92, -65, -30, -10, 10, 29, 65, 92, 121, 107, 44, -45, -107, -92, -76, -61, -38, -15, 16, 38, 75, 92, 88, 60, 0, -88, -68, -33, -14, 14, 35, 68, 45, 14, -13, -45, -33, 33};
        // int8_t y_points[] =  {121, 114, 114, 123, 108, 95, 95, 106, 88, 91, 89, 90, 91, 88, 68, 74, 65, 76, 65, 76, 69, 61, 61, 61, 60, 32, 45, 34, 37, 45, 41, 40, 45, 37, 35, 45, 31, 16, 30, 30, 13, 14, 15, 10, 21, 10, 0, -10, -20, -11, 0, -14, -14, -16, -20, -10, 0, 10, 21, 11, 15, 13, -13, 0, -11, -17, -15, -30, -34, -37, -30, -41, -41, -30, -38, -33, -32, -45, -45, -45, -44, -69, -60, -74, -66, -62, -62, -65, -60, -69, -88, -75, -75, -89, -92, -90, -95, -96, -91, -93, -105, -115, -115, -105, -121, -121};

        uint8_t spiral[106];
        uint8_t horizontal[106];
        

};