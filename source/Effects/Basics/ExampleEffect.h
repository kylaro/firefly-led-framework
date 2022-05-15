#pragma once
#include "../Effect.h"

class ExampleEffect : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        void release();
    private:
        double hue = 0;
};