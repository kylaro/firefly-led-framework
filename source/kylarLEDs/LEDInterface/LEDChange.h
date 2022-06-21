#pragma once
#include "ColorUtil.h"

class LEDChange {

    public:
        LEDChange();
        void combine(rgb8_t other);
        uint8_t count = 0;
        rgb8_t getRGB();
    private:
        rgb8_t rgb;
        void setRGB(rgb8_t rgb);
        
};