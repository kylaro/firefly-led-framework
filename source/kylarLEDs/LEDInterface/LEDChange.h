#pragma once
#include "ColorUtil.h"

class LEDChange {

    public:
        LEDChange();
        void combine(rgb_t other);
        uint8_t count = 0;
        rgb_t getRGB();
    private:
        rgb8_t rgb;
        void setRGB(rgb_t rgb);
        
};