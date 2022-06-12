#pragma once
#include "../Effect.h"

class SoundPixel : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        void release();
        int i = 0;
        double hue = 0;
    private:
        int unused = 0;
};