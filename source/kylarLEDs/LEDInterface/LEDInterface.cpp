#include "LEDInterface.h"
#include "stdio.h"
#include "stdlib.h"
LEDInterface::LEDInterface(){
    rgb_t off = {0, 0, 0};
    for(int i = 0; i < MAX_NUM_LEDS; i++){
        changesArray[i] = new LEDChange(i, off);
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

void LEDInterface::setHSV(int index, hsv_t hsv){
    if(index >= numLEDs){
        index %= numLEDs;
    }
    if(index < 0){
        index = abs(index);
        index %= numLEDs;
        index = numLEDs - 1 - index;
    }
    hsv.h += ledController->getHue();
    hsv.h = ColorUtil::sanitizeH(hsv.h);
    hsv.h = remapHue(hsv.h);
    hsv.s = ColorUtil::sanitizeSV(hsv.s);
    hsv.v = ColorUtil::sanitizeSV(hsv.v);
    rgb_t rgb = ColorUtil::hsv2rgb(hsv); 
    changesArray[index]->combine(rgb);
}

void LEDInterface::apply(){
    uint8_t r, g, b;
    rgb_t rgb;
    for (int i = 0; i < numLEDs; i++) {
        LEDChange* change = changesArray[i];
        if (change->count != 0) {
            rgb = change->getRGB();
            r = (uint8_t) (rgb.r*255.0*ledController->getBrightness());
            g = (uint8_t) (rgb.g*255.0*ledController->getBrightness());
            b = (uint8_t) (rgb.b*255.0*ledController->getBrightness());
            ledsArray[3*i] = g;
            ledsArray[3*i+1] = r;
            ledsArray[3*i+2] = b;
            change->count = 0;
        }
    }
}


void LEDInterface::output(){
    ledController->outputLEDs(ledsArray, numLEDs);
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