#pragma once
#include "../Pattern.h"
#include "../../kylarLEDs/Utility/Timing.h"

class Nathan : public Pattern
{

public:
    using Pattern::Pattern;
    void run();
    void init();
    void release();

private:
    Timing *myTiming;
    int initted = 0;
};