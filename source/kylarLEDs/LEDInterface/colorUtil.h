#pragma once
#include <stdint.h>

// #define HUE_LUT_RES 0.01f
// #define HUE_LUT_SIZE (int)(1.0f/LUT_RES)

#define REMAP_LUT_RES 0.003f
#define REMAP_LUT_SIZE (int)(1.0f/REMAP_LUT_RES)

#define HSV_HUE_SEXTANT		256
#define HSV_HUE_STEPS		(6 * HSV_HUE_SEXTANT)

#define HSV_HUE_MIN		0
#define HSV_HUE_MAX		(HSV_HUE_STEPS - 1)
#define HSV_SAT_MIN		0
#define HSV_SAT_MAX		255
#define HSV_VAL_MIN		0
#define HSV_VAL_MAX		255

/*
 * Macros that are common to all implementations
 */
#define HSV_MONOCHROMATIC_TEST(s,v,r,g,b) \
	do { \
		if(!(s)) { \
			 *(r) = *(g) = *(b) = (v); \
			return; \
		} \
	} while(0)


/*
 * Pointer swapping:
 * 	sext.	r g b	r<>b	g<>b	r <> g	result
 *	0 0 0	v u c			!u v c	u v c
 *	0 0 1	d v c				d v c
 *	0 1 0	c v u	u v c			u v c
 *	0 1 1	c d v	v d c		d v c	d v c
 *	1 0 0	u c v		u v c		u v c
 *	1 0 1	v c d		v d c	d v c	d v c
 *
 * if(sextant & 2)
 * 	r <-> b
 *
 * if(sextant & 4)
 * 	g <-> b
 *
 * if(!(sextant & 6) {
 * 	if(!(sextant & 1))
 * 		r <-> g
 * } else {
 * 	if(sextant & 1)
 * 		r <-> g
 * }
 */
#define HSV_SWAPPTR(a,b)	do { uint8_t *tmp = (a); (a) = (b); (b) = tmp; } while(0)
#define HSV_POINTER_SWAP(sextant,r,g,b) \
	do { \
		if((sextant) & 2) { \
			HSV_SWAPPTR((r), (b)); \
		} \
		if((sextant) & 4) { \
			HSV_SWAPPTR((g), (b)); \
		} \
		if(!((sextant) & 6)) { \
			if(!((sextant) & 1)) { \
				HSV_SWAPPTR((r), (g)); \
			} \
		} else { \
			if((sextant) & 1) { \
				HSV_SWAPPTR((r), (g)); \
			} \
		} \
	} while(0)

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
    uint16_t h;
    uint8_t s;
    uint8_t v;
} hsv16_t;

typedef struct{
    int i;
    rgb_t rgb;
} irgb_t;

typedef struct{
    int i;
    rgb8_t rgb;
} irgb8_t;

class ColorUtil{
    public:
        static float sanitizeH(float x);
        static float sanitizeSV(float x);
        static rgb_t hsv2rgb(hsv_t hsv);
        static float remap(float from, float fromMin, float fromMax, float toMin,  float toMax);
        static float remapHue(float hue);
        static void fast_hsv2rgb_32bit(uint16_t h, uint8_t s, uint8_t v, uint8_t *r, uint8_t *g , uint8_t *b);
        static float remapHueLUT[REMAP_LUT_SIZE];
        static void generateRemapLUT();
        //static float hsv2rgbLUT[HUE_LUT_SIZE];
};


