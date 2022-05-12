#include "LEDInterface.h"

LEDInterface::LEDInterface(){
    rgb_t off = {0, 0, 0};
    for(int i = 0; i < NUM_CHANGES; i++){
        changesArray[i] = new LEDChange(i, off);
    }
}


void LEDInterface::setRGB(){

}

void LEDInterface::setHSV(int index, hsv_t hsv){
    hsv.h = ColorUtil::sanitizeH(hsv.h);
    hsv.s = ColorUtil::sanitizeSV(hsv.s);
    hsv.v = ColorUtil::sanitizeSV(hsv.v);
    rgb_t rgb = ColorUtil::hsv2rgb(hsv); 
    changesArray[index]->combine(rgb);
}

void LEDInterface::apply(){
    for (int i = 0; i < NUM_CHANGES; i++) {
        LEDChange* change = changesArray[i];
        if (change->count != 0) {
            //setLED(change->index, (change->rgb.r * 255.0 * scale), (change->rgb.g * 255.0 * scale), (change->rgb.b * 255.0 * scale), real);
            change->count = 0;
        }
        
    }
}

void LEDInterface::output(){

}

void LEDInterface::giveController(Controller * ledController){
    this->ledController = ledController;
}