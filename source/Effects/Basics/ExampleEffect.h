#pragma once
#include "../Effect.h"

class ExampleEffect : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        void release();
        int i = 0;
    private:
        double hue = 0;
};