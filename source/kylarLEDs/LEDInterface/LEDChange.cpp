#include "LEDChange.h"
#include <stdio.h>


void LEDChange::setRGB(rgb_t rgb) {
	this->rgb.r = (uint8_t)(rgb.r*255.0);
	this->rgb.g = (uint8_t)(rgb.g*255.0);
	this->rgb.b = (uint8_t)(rgb.b*255.0);
}

LEDChange::LEDChange(){
    setRGB({0,0,0});
}

void LEDChange::combine(rgb_t newrgb){
    if (count == 0) {
		setRGB(newrgb);
		count++;
        return;
	} else {
		rgb.r = (uint8_t)(((uint32_t)rgb.r * (uint32_t)count + newrgb.r*255.0f) / (float)(count + 1));
		rgb.g = (uint8_t)(((uint32_t)rgb.g * (uint32_t)count + newrgb.g*255.0f) / (float)(count + 1));
		rgb.b = (uint8_t)(((uint32_t)rgb.b * (uint32_t)count + newrgb.b*255.0f) / (float)(count + 1));
        count++;
	}
}


rgb_t LEDChange::getRGB(){
	rgb_t ret_rgb = {rgb.r/255.0f, rgb.g/255.0f, rgb.b/255.0f};
    return ret_rgb;
}