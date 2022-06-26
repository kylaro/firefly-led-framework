#pragma once
#include "ColorUtil.h"

class LEDChange {

    public:
        LEDChange();
        void combine(rgb8_t other);
        void combine(rgbw8_t other);
        uint8_t count = 0;
        void setColor(rgbw8_t rgbw);
        void setColor(rgb8_t rgb);
#if RGBW
        rgbw8_t color;
#else
        rgb8_t color;
#endif

        
        
        
};