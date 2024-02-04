#pragma once
#include "../Effect.h"

class SpaceXLogo : public Effect{

    public:
        using Effect::Effect;
        void run();
        void init();
        ~SpaceXLogo();
        int i = 0;
        double hue = 0;
        int x, y = 0;
    private:
        int unused = 0;
};