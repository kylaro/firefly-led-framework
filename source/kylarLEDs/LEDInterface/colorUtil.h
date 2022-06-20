#pragma once
#include <stdint.h>
typedef struct{
    float h;         // Color: 0 to 1.0 : 0 is RED, 0.33 is GREEN, 0.66 BLUE
    float s;        // Whiteness: 0 to 1.0 : 0 is WHITE, 1 is COLOR
    float v;       // Brightness: 0 to 1.0 : 0 is OFF, 1 is ON
} hsv_t;

typedef struct{
    float r;         // Red 0 to 1.0
    float g;       // Green 0 to 1.0
    float b;        // Blue 0 to 1.0
} rgb_t;

typedef struct{
    uint8_t r;  // Red 0 to 255
    uint8_t g;  // Green 0 to 255
    uint8_t b;  // Blue 0 to 255
} rgb8_t;

typedef struct{
    int i;
    rgb_t rgb;
} irgb_t;

class ColorUtil{
    public:
        static double sanitizeH(double x);
        static double sanitizeSV(double x);
        static rgb_t hsv2rgb(hsv_t hsv);
        static double remap(double from, double fromMin, double fromMax, double toMin,  double toMax);
};
