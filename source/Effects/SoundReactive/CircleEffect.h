#pragma once
#include "../Effect.h"

class CircleEffect : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        ~CircleEffect();
        uint8_t t = 0;
        double hue = 0;
        double volume = 0;
        // a vector of uint8_t
        std::vector<uint8_t> * pixels;
        CircleEffect* led(uint8_t i);
        void calculate(double phase);
        void white(double val);
};