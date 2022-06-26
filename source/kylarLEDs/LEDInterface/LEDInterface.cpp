#include "LEDInterface.h"
#include "../Utility/ExecTimer.h"
#include "stdio.h"
#include "stdlib.h"
LEDInterface::LEDInterface(uint8_t strip){
    rgb_t off = {0, 0, 0};
    this->strip = strip;
    for(int i = 0; i < NUM_LEDS; i++){
        changesArray[i] = new LEDChange();
        ledsArray[i*3] = 0;
        ledsArray[i*3+1] = 0;
        ledsArray[i*3+2] = 0;
    }
}


void LEDInterface::setRGB(int index, rgb_t rgb){
    // set RGB is discontinued, HSV is superior
    // if(index >= NUM_LEDS){
    //     return;
    // }
    // rgb.r = ColorUtil::sanitizeH(rgb.r);
    // rgb.g = ColorUtil::sanitizeH(rgb.g);
    // rgb.b = ColorUtil::sanitizeH(rgb.b);
    // changesArray[index]->combine(rgb);
}



irgb8_t LEDInterface::setHSV(int index, hsv_t hsv){
    if(index >= numLEDs){
        index %= numLEDs;
    }
    if(index < 0){
        index = abs(index);
        index %= numLEDs;
        index = numLEDs - 1 - index;
    }
    //ExecTimer *timer = new ExecTimer();
    //timer->start("setHSV");

    hsv.h += ledController->getHue();
    //timer->add("ledController->getHue()");

    hsv.h = ColorUtil::sanitizeH(hsv.h);
    hsv.s = ColorUtil::sanitizeSV(hsv.s);
    hsv.v = ColorUtil::sanitizeSV(hsv.v);

    //timer->add("::sanitizeHSV()");

    hsv.h = ColorUtil::remapHueLUT[(int)(hsv.h/REMAP_LUT_RES)];//ColorUtil::remapHue(hsv.h);
    //timer->add("remapHue(hsv.h);");
    irgb8_t irgb8;
#if RGBW
    hsv.v = hsv.v*hsv.s;
    hsv16_t hsv16 = {hsv.h * HSV_HUE_MAX, hsv.s * HSV_SAT_MAX, hsv.v * HSV_VAL_MAX};
    rgbw8_t rgbw;
    ColorUtil::fast_hsv2rgb_32bit(hsv16.h, hsv16.s, hsv16.v, &rgbw.r, &rgbw.g, &rgbw.b);
    rgbw.w = (uint8_t)((1.0f-hsv.s)*64.0f);
    
    changesArray[index]->combine(rgbw);
    return irgb8; // for rgbw, this is ignored, but still needs to be returned
    // something could be added later.
#else
    rgb8_t rgb8;
    hsv16_t hsv16 = {hsv.h * HSV_HUE_MAX, hsv.s * HSV_SAT_MAX, hsv.v * HSV_VAL_MAX};
    
    ColorUtil::fast_hsv2rgb_32bit(hsv16.h, hsv16.s, hsv16.v, &rgb8.r, &rgb8.g, &rgb8.b);
    
    changesArray[index]->combine(rgb8);

    // Create the return value, for re-use
    irgb8_t irgb;
    irgb.rgb = rgb8;
    irgb.i = index;
    return irgb;
#endif
    
}

void LEDInterface::setRGBUnprotected(int index, rgb8_t rgb8){
    changesArray[index]->combine(rgb8);
}

void LEDInterface::apply(){
    uint8_t r, g, b, w;
    rgb8_t rgb;
    rgbw8_t rgbw;
    float brightness = ledController->getBrightness();
    uint8_t brightnessLUT[256];
    for(int i = 0; i < 256; i++){
        brightnessLUT[i] = i * brightness;
    }
    for (int i = 0; i < numLEDs; i++) {
        LEDChange* change = changesArray[i];
        if (change->count != 0) {
#if RGBW
            rgbw = change->color;
            r = brightnessLUT[rgbw.r];
            g = brightnessLUT[rgbw.g];
            b = brightnessLUT[rgbw.b];
            w = brightnessLUT[rgbw.w];
            ledsArray[4*i] = g;
            ledsArray[4*i+1] = r;
            ledsArray[4*i+2] = b;
            ledsArray[4*i+3] = w;
#else
            rgb = change->color;
            r = brightnessLUT[rgb.r];
            g = brightnessLUT[rgb.g];
            b = brightnessLUT[rgb.b];
            ledsArray[3*i] = g;
            ledsArray[3*i+1] = r;
            ledsArray[3*i+2] = b;
            
#endif
            change->count = 0;
        }
    }
}


void LEDInterface::output(){
    ledController->outputLEDs(strip, ledsArray, numLEDs);
}

void LEDInterface::clear(){
#if RGBW
    for(int i = 0; i < numLEDs; i++){
        ledsArray[i*4] = 0;
        ledsArray[i*4+1] = 0;
        ledsArray[i*4+2] = 0;
        ledsArray[i*4+3] = 0;
    }
#else
    for(int i = 0; i < numLEDs; i++){
        ledsArray[i*3] = 0;
        ledsArray[i*3+1] = 0;
        ledsArray[i*3+2] = 0;
    }
#endif
}

void LEDInterface::giveController(Controller * ledController){
    this->ledController = ledController;
}

double LEDInterface::num(){ //Get num LEDs
    return (double)numLEDs;
} 
void LEDInterface::setNum(uint16_t num){ //set number of LEDs
    numLEDs = num;
    clear();
} 