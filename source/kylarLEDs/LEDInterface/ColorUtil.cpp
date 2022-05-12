#include "ColorUtil.h"
#include <cmath>


//LOOP WHEEL
double ColorUtil::sanitizeH(double x) {
    //CONVERT THIS X VALUE TO BE BETWEEN 0 AND 1 PLEASE
    if (x < 0) {
        x = fabs(x);//ok now it is positive
    }
    if (x > 1) {
        x = fmod(x, 1.0);
    }
    return x;
}

//MAX / MIN
double ColorUtil::sanitizeSV(double x) {
    //CONVERT THIS X VALUE TO BE BETWEEN 0 AND 1 PLEASE
    if (x < 0) {
        return 0;
    }
    if (x > 1) {
        return 1;
    }
    return x;
}

rgb_t ColorUtil::hsv2rgb(hsv_t hsv) {
    double H = hsv.h * 360.0;
    double S = hsv.s * 100.0;
    double V = hsv.v * 100.0;

    double s = S / 100;
    double v = V / 100;
    double C = s * v;
    double X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    double m = v - C;
    double r, g, b;
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
    
    double R = (r + m);// *255;
    double G = (g + m);// * 255;
    double B = (b + m);// * 255;
    rgb_t rgb = { R,G,B };
    return rgb;
}
