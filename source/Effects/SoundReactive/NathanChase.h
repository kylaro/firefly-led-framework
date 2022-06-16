#pragma once
#include "../Effect.h"
#include "../../kylarLEDs/Utility/Timing.h"
class NathanChase : public Effect
{

public:
    using Effect::Effect;
    void run();
    void init();
    void release();
    int i = 0;
    int dir = 1;
    double hue = 0;

private:
    int unused = 0;
    Timing *timer = NULL;
    Timing *dirTimer = NULL;
};