#include "LEDChange.h"


LEDChange::LEDChange(int i, rgb_t rgb){
    this->rgb = rgb;
    index = i;
}

void LEDChange::combine(rgb_t newrgb){
    if (count == 0) {
		rgb = newrgb;
		count++;
		return;
	} else {
        count++;
		rgb.r = (rgb.r * count + newrgb.r) / (double)(count);
		rgb.g = (rgb.g * count + newrgb.g) / (double)(count);
		rgb.b = (rgb.b * count + newrgb.b) / (double)(count);
	}
}