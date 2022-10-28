#include "CirclesPattern.h"
#include <stdio.h>
#include "../../Effects/SoundReactive/CircleEffect.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"


void CirclesPattern::init(){

    inner_circles = new std::vector<CircleEffect*>();
    outer_circles = new std::vector<CircleEffect*>();

    //OUTER CIRCLES
    CircleEffect * eff = new CircleEffect();
    eff->init();
    eff->led(0)->led(1)->led(6)->led(10)->led(7);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(3)->led(4)->led(11)->led(5)->led(2);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(13)->led(14)->led(24)->led(15)->led(12);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(25)->led(40)->led(41)->led(27)->led(26);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(76)->led(77)->led(75)->led(52)->led(51);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);
    
    eff = new CircleEffect();
    eff->init();
    eff->led(90)->led(99)->led(91)->led(88)->led(89);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(105)->led(101)->led(97)->led(98)->led(100);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(104)->led(103)->led(95)->led(96)->led(102);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(93)->led(81)->led(82)->led(83)->led(94);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(67)->led(62)->led(66)->led(68)->led(80);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(36)->led(35)->led(34)->led(60)->led(61);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(8)->led(9)->led(19)->led(21)->led(20);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    //Center Circle....
    // eff = new CircleEffect();
    // eff->init();
    // eff->led(58)->led(57)->led(56)->led(55)->led(54);
    // Effect::engine->apply(eff);
    // outer_circles->push_back(eff);

    // eff = new CircleEffect();
    // eff->init();
    // eff->led(44)->led(45)->led(46)->led(47)->led(48);
    // Effect::engine->apply(eff);
    // outer_circles->push_back(eff);

    //INNER CIRCLES
    eff = new CircleEffect();
    eff->init();
    eff->led(17)->led(23)->led(30)->led(31)->led(22);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(28)->led(42)->led(43)->led(39)->led(29);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(74)->led(78)->led(73)->led(49)->led(53);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(92)->led(85)->led(71)->led(72)->led(86);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(69)->led(65)->led(64)->led(70)->led(79);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(33)->led(32)->led(38)->led(59)->led(37);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    // last leds
    // 18, 16, 63, 87, 84, 50, 18, 16, 63, 87, 84, 50

    highLEDs = new CircleEffect();
    highLEDs->init();
    highLEDs->led(18)->led(16)->led(50)->led(87)->led(84)->led(63)->led(57)->led(55)->led(47)->led(45)->led(56)->led(46)->led(44)->led(58)->led(54)->led(48);//after 63 are imposters (63 is good), up to 45 is good tho lol
    Effect::engine->apply(highLEDs);

    secTimer = new Timing();
    avgTimer = new Timing();
    valTimer = new Timing();
}

void CirclesPattern::run(){
    double micVal = pow(Microphone::getLowNormal(),2) ;
    static double brightness = 0;
    static double highVal = 0;
    double seconds = secTimer->takeSeconds();
    int avgLoops = 0;
    // Color movement
    //printf("micTimer = %d ... %f\n", micTimer->timerMs(), micTimer->takeSeconds());
    double micAdd = micVal / 50; // trying to even out timing
    // printf("avgTimer = %d ... %d\n", avgTimer->timerMs());//, avgTimer->takeMsEvery(25));
    avgLoops = avgTimer->takeMsEvery(1);


    // Brightness
    double proposedBrightness = (micVal);
    //printf("valTimer = %d ... %d\n", valTimer->timerMs(), valTimer->takeMsEvery(100));
    avgLoops = valTimer->takeMsEvery(1);
    for(int i = 0; i < avgLoops; i++){
        //brightness = (brightness*120.0 + proposedBrightness)/121.0;
        if(proposedBrightness > brightness){
            //increasing
            brightness = (brightness*50.0 + proposedBrightness) / 51.0;
        }else{
            //decreasing
            brightness = (brightness*120.0 + proposedBrightness) / 121.0;
        }

        if(Microphone::getHighNormal() > highVal){
            highVal = (highVal*3.0 + Microphone::getHighNormal()) / 4.0;
        }else{
            highVal = (highVal*24.0 + Microphone::getHighNormal()) / 25.0;//25
        }
        
        
    }
    if(highVal > 1){
        highVal = 1;
    }
    
    if(proposedBrightness > brightness){
        brightness = proposedBrightness;
    }

    for(int i = 0; i < outer_circles->size(); i++){
        CircleEffect * eff = outer_circles->at(i);
        eff->volume = micVal;
        eff->calculate(brightness);
        
    }

    for(int i = 0; i < inner_circles->size(); i++){
        CircleEffect * eff = inner_circles->at(i);
        eff->volume = micVal;
        eff->calculate(brightness);
    }
    
    //printf("high val = %f\n", highVal);
    highLEDs->white(highVal);
    
}

void CirclesPattern::release(){
    delete(secTimer);
    delete(avgTimer);
    delete(valTimer);
    delete(outer_circles);
    delete(inner_circles);
}