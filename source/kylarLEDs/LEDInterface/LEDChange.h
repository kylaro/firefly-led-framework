#pragma once
#include "ColorUtil.h"

class LEDChange {

    public:
        LEDChange(int i, rgb_t rgb);
        void combine(rgb_t other);
        int count = 0;
    private:
        int index;
        rgb_t rgb;
        
};