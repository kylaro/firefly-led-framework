#pragma once
#include "../Effect.h"
#include "SingleTime.h"
#include "../../kylarLEDs/Utility/Timing.h"
class FireFly : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        void release();
    private:
        double hue = 0;
        double speed = 1;
        double position = 0;
        int lastPosition = -1;
        int nextPosition = -1;
        single_time_t blueprint;
        Timing *timer;
};