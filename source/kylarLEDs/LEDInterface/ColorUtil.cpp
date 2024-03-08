#include "ColorUtil.h"
#include <cmath>
#include <stdio.h>

float ColorUtil::remapHueLUT[REMAP_LUT_SIZE];

void ColorUtil::generateRemapLUT() {
    for (int i = 0; i < REMAP_LUT_SIZE; i++) {
        float hue = (float)i / (float)REMAP_LUT_SIZE;
        remapHueLUT[i] = remapHue(hue);
    }
}

//LOOP WHEEL
float ColorUtil::sanitizeH(float x) {
    //CONVERT THIS X VALUE TO BE BETWEEN 0 AND 1 PLEASE
    if (x < 0) {
        x = fabs(x);//ok now it is positive
        x = fmod(x, 1.0);
        x = 1.0 - x;
        return x;
    }
    if (x > 1) {
        x = fmod(x, 1.0);
        return x;
    }
    return x;
}

//MAX / MIN
float ColorUtil::sanitizeSV(float x) {
    //CONVERT THIS X VALUE TO BE BETWEEN 0 AND 1 PLEASE
    if (x < 0) {
        return 0;
    }
    if (x > 1) {
        return 1;
    }
    return x;
}
// Source: https://www.vagrearg.org/content/hsvrgb
void ColorUtil::fast_hsv2rgb_32bit(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b) {
	HSV_MONOCHROMATIC_TEST(s, v, r, g, b);	// Exit with grayscale if s == 0

	uint8_t sextant = h >> 8;

	HSV_POINTER_SWAP(sextant, r, g, b);	// Swap pointers depending which sextant we are in

	*g = v;		// Top level

	// Perform actual calculations

	/*
	 * Bottom level: v * (1.0 - s)
	 * --> (v * (255 - s) + error_corr + 1) / 256
	 */
	uint16_t ww;		// Intermediate result
	ww = v * (255 - s);	// We don't use ~s to prevent size-promotion side effects
	ww += 1;		// Error correction
	ww += ww >> 8;		// Error correction
	*b = ww >> 8;

	uint8_t h_fraction = h & 0xff;	// 0...255
	uint32_t d;			// Intermediate result

	if(!(sextant & 1)) {
		// *r = ...slope_up...;
		d = v * (uint32_t)((255 << 8) - (uint16_t)(s * (256 - h_fraction)));
		d += d >> 8;	// Error correction
		d += v;		// Error correction
		*r = d >> 16;
	} else {
		// *r = ...slope_down...;
		d = v * (uint32_t)((255 << 8) - (uint16_t)(s * h_fraction));
		d += d >> 8;	// Error correction
		d += v;		// Error correction
		*r = d >> 16;
	}
}

rgb_t ColorUtil::hsv2rgb(hsv_t hsv) {
    float H = hsv.h * 360.0f;
    float S = hsv.s * 100.0f;
    float V = hsv.v * 100.0f;

    float s = S / 100.0f;
    float v = V / 100.0f;
    float C = s * v;
    float X = C * (1.0f - fabs(fmod(H / 60.0f, 2.0f) - 1.0f));
    float m = v - C;

    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C, g = 0, b = X;
    }

    float R = (r + m);// *255;
    float G = (g + m);// * 255;
    float B = (b + m);// * 255;

    rgb_t rgb = { R,G,B };
    return rgb;
}

float ColorUtil::remapHue(float hue){
    //RED section 1
    const float pt[] = {0.05, 0.5, 0.95};// Points where the color changes
    if(hue < 0.166){
        //Red section 1
        return remap(hue, 0, 0.166, 0, pt[0]);
    }else if(hue < 0.5){
        //Green section
        return remap(hue, 0.166, 0.5, pt[0], pt[1]);
    }else if(hue < 0.833){
        // Blue section
        return remap(hue, 0.5, 0.833, pt[1], pt[2]);
    }else{
        //Red section 2
        return remap(hue, 0.833, 1, pt[2], 1);
    }
    return hue;
}

float ColorUtil::remap(float from, float fromMin, float fromMax, float toMin,  float toMax){
    float fromAbs  =  from - fromMin;
    float fromMaxAbs = fromMax - fromMin;      
    
    float normal = fromAbs / fromMaxAbs;

    float toMaxAbs = toMax - toMin;
    float toAbs = toMaxAbs * normal;

    float to = toAbs + toMin;
    
    return to;
}