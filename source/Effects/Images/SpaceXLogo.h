#pragma once
#include "../Effect.h"
#include "../../kylarLEDs/Utility/Timing.h"

class SpaceXLogo : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        void clamp(float *x, float min, float max);
        ~SpaceXLogo();
        void setBrightness(float b);
        float hue = 0;
    private:
        float brightness = 0;
        void shiftFifo();
        Timing *hueTimer;
        Timing *fifoTimer;
};