#include "LEDInterface.h"
#include "../Utility/ExecTimer.h"
#include "stdio.h"
#include "stdlib.h"
LEDInterface::LEDInterface(uint8_t strip){
    rgb_t off = {0, 0, 0};
    this->strip = strip;
    for(int i = 0; i < MAX_NUM_LEDS; i++){
        changesArray[i] = new LEDChange();
        printf("size of ledchange = %d\n", sizeof(LEDChange));
        ledsArray[i*3] = 0;
        ledsArray[i*3+1] = 0;
        ledsArray[i*3+2] = 0;
        printf("size of ledsarray = %d\n", sizeof(ledsArray));
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

double LEDInterface::remapHue(double hue){
    //RED section 1
    const double pt[] = {0.05, 0.5, 0.95};// Points where the color changes
    if(hue < 0.166){
        //Red section 1
        return ColorUtil::remap(hue, 0, 0.166, 0, pt[0]);
    }else if(hue < 0.5){
        //Green section
        return ColorUtil::remap(hue, 0.166, 0.5, pt[0], pt[1]);
    }else if(hue < 0.833){
        // Blue section
        return ColorUtil::remap(hue, 0.5, 0.833, pt[1], pt[2]);
    }else{
        //Red section 2
        return ColorUtil::remap(hue, 0.833, 1, pt[2], 1);
    }
    return hue;
}

irgb_t LEDInterface::setHSV(int index, hsv_t hsv){
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
    //timer->add("::sanitizeH(hsv.h)");
    hsv.h = remapHue(hsv.h);
    //timer->add("remapHue(hsv.h);");
    hsv.s = ColorUtil::sanitizeSV(hsv.s);
    hsv.v = ColorUtil::sanitizeSV(hsv.v);
    //timer->add("::sanitizeSV(hsv.v)");
    rgb_t rgb = ColorUtil::hsv2rgb(hsv); 
    //timer->add("::hsv2rgb(hsv)");
    changesArray[index]->combine(rgb);
    //timer->add("changesArray[index]->combine(rgb)");
    //timer->print();
    //delete(timer);
    // Create the return value, for re-use
    irgb_t irgb;
    irgb.rgb = rgb;
    irgb.i = index;
    return irgb;
}

void LEDInterface::setRGBUnprotected(int index, rgb_t rgb){
    changesArray[index]->combine(rgb);
}

void LEDInterface::apply(){
    uint8_t r, g, b;
    rgb_t rgb;
    double brightness = 255.0*ledController->getBrightness();
    for (int i = 0; i < numLEDs; i++) {
        LEDChange* change = changesArray[i];
        if (change->count != 0) {
            rgb = change->getRGB();
            r = (uint8_t) (rgb.r*brightness);
            g = (uint8_t) (rgb.g*brightness);
            b = (uint8_t) (rgb.b*brightness);
            ledsArray[3*i] = g;
            ledsArray[3*i+1] = r;
            ledsArray[3*i+2] = b;
            change->count = 0;
        }
    }
}


void LEDInterface::output(){
    ledController->outputLEDs(strip, ledsArray, numLEDs);
}

void LEDInterface::clear(){
    for(int i = 0; i < numLEDs; i++){
        ledsArray[i*3] = 0;
        ledsArray[i*3+1] = 0;
        ledsArray[i*3+2] = 0;
    }
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