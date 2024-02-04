#pragma once
#include "../Effect.h"

class SpaceXLogo : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        ~SpaceXLogo();
        void setBrightness(float b);
    private:
        hsv_t color_fifo[3];
        float brightness = 0;
};