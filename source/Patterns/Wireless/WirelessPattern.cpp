#include "WirelessPattern.h"
#include <stdio.h>
#include "../../Effects/Basics/ExampleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/Sensors/Microphone/Microphone.h"

void WirelessPattern::init(){
    

}

void WirelessPattern::run(){

    // TODO CHATGPT
    // I need to retrieve data about what wireless things have happened in cgi_led_handler
    
    
}

void WirelessPattern::release(){
    delete(myTiming);
}