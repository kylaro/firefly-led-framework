#pragma once
#include "../Effect.h"
#include "../../kylarLEDs/Utility/Timing.h"

class Heart : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        void clamp(float *x, float min, float max);
        ~Heart();
        void setBrightness(float b);
        float hue = 0;
        float speed = 1;
    private:
        float brightness = 0;

        void shiftFifo();
        Timing *hueTimer;
        Timing *fifoTimer;
};