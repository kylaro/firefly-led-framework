#pragma once
#include "../Effect.h"

class SoundPixel : public Effect{

    public:
        using Effect::Effect;
        ~SoundPixel();
        void run();
        void init();
        void release();
        int i = 0;
        double hue = 0;
        double micVal = 0;
        double hueAdd = 0;
        double brightness = 0;
    private:
        int unused = 0;
};