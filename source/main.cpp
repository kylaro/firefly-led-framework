
#include "stdio.h"
#include <vector>
#include <string>
#include "Effects/Effect.h"
#include "kylarLEDs/LEDInterface/LEDs.h"
#include "kylarLEDs/EffectEngine/EffectEngine.h"
#include "kylarLEDs/Controllers/FireFly/FireFlyController.h"
#include "Patterns/Examples/ExamplePattern.h"
#include "Patterns/Examples/FireFlies.h"
#include "Patterns/Examples/FireFliesSame.h"
#include "Patterns/SoundReactive/Shakeel.h"
#include "Patterns/SoundReactive/Ben.h"
#include "kylarLEDs/Utility/ExecTimer.h"
#include <malloc.h>
#include "pico/time.h"
#include "config.h"

using namespace std;
int main(){

    // Initialize framework infrastructure
    Controller *ledController = new FireFlyController();
    EffectEngine *effectEngine = new EffectEngine();
    LEDs::init(NUM_STRIPS); // Initializing # of outputs
    LEDs::setNum(NUM_LEDS); // Setting all strips to 120 LEDs
    
    Effect::giveEngine(effectEngine);
    
    vector<Pattern*> *patterns = new vector<Pattern*>();
    //Push back all the patterns you want!
    //ADD YOUR PATTERNS HERE!
    //ex. patterns->push_back(new ExamplePattern());
    //patterns->push_back(new Ben());
    patterns->push_back(new Shakeel());
    patterns->push_back(new FireFlies());
    //patterns->push_back(new FireFliesSame());
    

    //Initialize main loop variables
    uint32_t numPatterns = patterns->size();
    uint32_t currentPatternIndex = 0;
    uint32_t nextPatternIndex = 0;
    Pattern *currentPattern = patterns->at(currentPatternIndex);
    Pattern *nextPattern = patterns->at(nextPatternIndex);
    
    //Give the ledController access to the nextPatternIndex
    //Thus it can write to it when its button is pressed and change the pattern
    ledController->givePatternIndex(&nextPatternIndex);

    //Give the LEDInterfaces the controller
    //This way the LEDInterface can call the output function to the controller
    //The LEDInterface can also ask the controller for hue/brightness info
    //Which is based on the sensors the controller accesses
    LEDs::giveController(ledController);
    Timing::giveControllerForTiming(ledController);

    //Initialize first pattern
    currentPattern->init();

    ExecTimer *timer = new ExecTimer();
    //Main loop
    while(1){
        // mem usage:
        struct mallinfo mi = mallinfo();
        printf("Total allocated space (bytes):      %d\n", mi.uordblks); // max is about 238516 bytes ( unless there is ghost memory )
        if(currentPatternIndex == nextPatternIndex){
            //We are remaining on the same pattern
            timer->start("mainloop");
            currentPattern->run();  // Allow pattern to create effects
            timer->add("currentPattern->run()");
            effectEngine->run();    // Run each effect to generate LED Changes
            timer->add("effectEngine->run()");
            LEDs::clear();          // Clear LEDs between runs
            timer->add("LEDs::clear()");
            LEDs::apply();          // Apply changes by collapsing LED Changes
            timer->add("LEDs::apply()");
            LEDs::output();         // Output to strip via controller
            timer->add("LEDs::output()");
            timer->print();
        }else{
            //We are changing pattern
            currentPattern->release();                      //Finish the current pattern
            effectEngine->clear();                          //Clear the effects
            LEDs::clear();                                  //Clear the LEDs
            LEDs::output();                                 //Output the off LEDs
            nextPatternIndex %= numPatterns;                //Protect from out of bounds
            nextPattern = patterns->at(nextPatternIndex);   //Get the next pattern
            currentPattern = nextPattern;                   //Set the current pattern to be the next
            currentPatternIndex = nextPatternIndex;         //Set current pattern index to the new one
            currentPattern->init();                         //Init the new current pattern
        }
    }
    

    return 0;
}