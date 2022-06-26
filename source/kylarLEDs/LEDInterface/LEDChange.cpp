#include "LEDChange.h"
#include <stdio.h>


void LEDChange::setColor(rgb8_t rgb) {
	this->color.r = rgb.r;
	this->color.g = rgb.g;
	this->color.b = rgb.b;
}

void LEDChange::setColor(rgbw8_t rgbw) {
	this->color.r = rgbw.r;
	this->color.g = rgbw.g;
	this->color.b = rgbw.b;
#if RGBW
	this->color.w = rgbw.w;
#endif
}

LEDChange::LEDChange(){
    
}

void LEDChange::combine(rgb8_t newrgb){
    if (count == 0) {
		setColor(newrgb);
		count++;
        return;
	} else {
		color.r = (uint8_t)((uint32_t)color.r * (uint32_t)count + (uint32_t)color.r) / ((uint32_t)count + 1);
		color.g = (uint8_t)((uint32_t)color.g * (uint32_t)count + (uint32_t)color.g) / ((uint32_t)count + 1);
		color.b = (uint8_t)((uint32_t)color.b * (uint32_t)count + (uint32_t)color.b) / ((uint32_t)count + 1);
        count++;
	}
}

void LEDChange::combine(rgbw8_t newrgb){

    if (count == 0) {
		setColor(newrgb);
		count++;
        return;
	} else {
		color.r = (uint8_t)((uint32_t)color.r * (uint32_t)count + (uint32_t)newrgb.r) / ((uint32_t)count + 1);
		color.g = (uint8_t)((uint32_t)color.g * (uint32_t)count + (uint32_t)newrgb.g) / ((uint32_t)count + 1);
		color.b = (uint8_t)((uint32_t)color.b * (uint32_t)count + (uint32_t)newrgb.b) / ((uint32_t)count + 1);
#if RGBW
		color.w = (uint8_t)((uint32_t)color.w * (uint32_t)count + (uint32_t)newrgb.w) / ((uint32_t)count + 1);
#endif
		count++;
	}

}