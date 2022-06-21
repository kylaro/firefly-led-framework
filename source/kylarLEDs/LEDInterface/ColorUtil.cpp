#include "ColorUtil.h"
#include <cmath>
#include <stdio.h>

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

// rgb_t ColorUtil::fastHSV2RGB(){

// }

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


float ColorUtil::remap(float from, float fromMin, float fromMax, float toMin,  float toMax){
    float fromAbs  =  from - fromMin;
    float fromMaxAbs = fromMax - fromMin;      
    
    float normal = fromAbs / fromMaxAbs;

    float toMaxAbs = toMax - toMin;
    float toAbs = toMaxAbs * normal;

    float to = toAbs + toMin;
    
    return to;
}