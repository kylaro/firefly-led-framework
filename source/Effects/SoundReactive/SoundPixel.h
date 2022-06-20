#pragma once
#include "../Effect.h"

class SoundPixel : public Effect{

    public:
        using Effect::Effect;
        ~SoundPixel();
        void run();
        void init();
        void release();
        uint16_t i = 0;
        float hue = 0;
        float micVal = 0;
        float hueAdd = 0;
        float brightness = 0;
    private:
        
};