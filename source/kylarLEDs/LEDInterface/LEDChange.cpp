#include "LEDChange.h"
#include <stdio.h>


void LEDChange::setRGB(rgb8_t rgb) {
	this->rgb.r = rgb.r;
	this->rgb.g = rgb.g;
	this->rgb.b = rgb.b;
}

LEDChange::LEDChange(){
    setRGB({0,0,0});
}

void LEDChange::combine(rgb8_t newrgb){
    if (count == 0) {
		setRGB(newrgb);
		count++;
        return;
	} else {
		rgb.r = (uint8_t)((uint32_t)rgb.r * (uint32_t)count + (uint32_t)newrgb.r) / ((uint32_t)count + 1);
		rgb.g = (uint8_t)((uint32_t)rgb.g * (uint32_t)count + (uint32_t)newrgb.g) / ((uint32_t)count + 1);
		rgb.b = (uint8_t)((uint32_t)rgb.b * (uint32_t)count + (uint32_t)newrgb.b) / ((uint32_t)count + 1);
		// rgb.r = (uint8_t)(((uint32_t)rgb.r * (uint32_t)count + newrgb.r*255.0f) / (float)(count + 1));
		// rgb.g = (uint8_t)(((uint32_t)rgb.g * (uint32_t)count + newrgb.g*255.0f) / (float)(count + 1));
		// rgb.b = (uint8_t)(((uint32_t)rgb.b * (uint32_t)count + newrgb.b*255.0f) / (float)(count + 1));
        count++;
	}
}


rgb8_t LEDChange::getRGB(){
	//rgb8_t ret_rgb = {rgb.r/255.0f, rgb.g/255.0f, rgb.b/255.0f};
    return rgb;
}