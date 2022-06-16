#pragma once

typedef struct{
    double h;         // Color: 0 to 1.0 : 0 is RED, 0.33 is GREEN, 0.66 BLUE
    double s;  // Whiteness: 0 to 1.0 : 0 is WHITE, 1 is COLOR
    double v;       // Brightness: 0 to 1.0 : 0 is OFF, 1 is ON
} hsv_t;

typedef struct{
    double r;         // Red 0 to 1.0
    double g;       // Green 0 to 1.0
    double b;        // Blue 0 to 1.0
} rgb_t;

class ColorUtil{
    public:
        static double sanitizeH(double x);
        static double sanitizeSV(double x);
        static rgb_t hsv2rgb(hsv_t hsv);
        static double remap(double from, double fromMin, double fromMax, double toMin,  double toMax);
};
