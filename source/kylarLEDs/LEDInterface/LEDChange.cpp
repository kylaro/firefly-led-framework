#include "LEDChange.h"
#include <stdio.h>

LEDChange::LEDChange(int i, rgb_t rgb)
{
	this->rgb = rgb;
	index = i;
}

void LEDChange::combine(rgb_t newrgb)
{
	if (count == 0)
	{
		rgb = newrgb;
		count++;
		return;
	}
	else
	{
		// color mix
		rgb.r = (rgb.r * count + newrgb.r) / (double)(count + 1);
		rgb.g = (rgb.g * count + newrgb.g) / (double)(count + 1);
		rgb.b = (rgb.b * count + newrgb.b) / (double)(count + 1);
		count++;
	}
}

rgb_t LEDChange::getRGB()
{
	return this->rgb;
}