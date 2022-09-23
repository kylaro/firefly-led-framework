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
    eff->led(72)->led(73)->led(71)->led(58)->led(57);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);
    
    eff = new CircleEffect();
    eff->init();
    eff->led(86)->led(95)->led(87)->led(84)->led(85);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(101)->led(97)->led(93)->led(94)->led(96);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(100)->led(99)->led(91)->led(92)->led(98);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(89)->led(77)->led(78)->led(79)->led(90);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(63)->led(50)->led(62)->led(64)->led(76);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(36)->led(35)->led(34)->led(48)->led(49);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(8)->led(9)->led(19)->led(21)->led(20);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(45)->led(44)->led(54)->led(60)->led(53)->led(46);
    Effect::engine->apply(eff);
    outer_circles->push_back(eff);

    //INNER CIRCLES
    eff = new CircleEffect();
    eff->init();
    eff->led(16)->led(29)->led(39)->led(30)->led(23);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(56)->led(59)->led(55)->led(43)->led(42);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(83)->led(82)->led(68)->led(69)->led(74);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(80)->led(75)->led(66)->led(67)->led(81);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(51)->led(37)->led(47)->led(52)->led(61);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    eff = new CircleEffect();
    eff->init();
    eff->led(18)->led(22)->led(31)->led(38)->led(32);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    // last LEDs:
    // 17, 28, 33, 65, 70, 88,

    eff = new CircleEffect();
    eff->init();
    eff->led(17)->led(28)->led(33)->led(65)->led(70)->led(88);
    Effect::engine->apply(eff);
    inner_circles->push_back(eff);

    secTimer = new Timing();
    avgTimer = new Timing();
    valTimer = new Timing();
}

void CirclesPattern::run(){
    double micVal = pow(Microphone::getLowNormal(),2) ;
    static double brightness = 0;
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
        brightness = (brightness*120.0 + proposedBrightness)/121.0;
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
    
}

void CirclesPattern::release(){
    delete(secTimer);
    delete(avgTimer);
    delete(valTimer);
    delete(outer_circles);
    delete(inner_circles);
}