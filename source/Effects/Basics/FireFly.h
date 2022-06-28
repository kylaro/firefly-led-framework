#pragma once
#include "../Effect.h"
#include "SingleTime.h"
#include "../../kylarLEDs/Utility/Timing.h"
class FireFly : public Effect{

    public:
        using Effect::Effect;
        ~FireFly();
        void run();
        void init();
        int direction = 1;
        double hue = 0;
        single_time_t blueprint;
    private:
        double speed = 1;
        double position = 0;
        int lastPosition = -1;
        int nextPosition = -1;
        
        Timing *timer;
};