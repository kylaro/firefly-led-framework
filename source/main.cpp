
#include "stdio.h"
#include <vector>
#include "Effects/Effect.h"
#include "kylarLEDs/LEDInterface/LEDInterface.h"
#include "kylarLEDs/EffectEngine/EffectEngine.h"
#include "kylarLEDs/Controllers/FireFly/FireFlyController.h"
#include "Patterns/Examples/ExamplePattern.h"
#include "Patterns/Examples/FireFlies.h"


using namespace std;
int main(){
    // Initialize framework infrastructure
    Controller *ledController = new FireFlyController();
    EffectEngine *effectEngine = new EffectEngine();
    LEDInterface *LEDs = new LEDInterface();
    Timing::giveControllerForTiming(ledController);
    Effect::giveEngine(effectEngine);
    
    vector<Pattern*> *patterns = new vector<Pattern*>();
    //Push back all the patterns you want!
    //ADD YOUR PATTERNS HERE!
    //ex. patterns->push_back(new ExamplePattern(LEDs));
    patterns->push_back(new FireFlies(LEDs));
    patterns->push_back(new ExamplePattern(LEDs));

    //Initialize main loop variables
    uint32_t numPatterns = patterns->size();
    uint32_t currentPatternIndex = 0;
    uint32_t nextPatternIndex = 0;
    Pattern *currentPattern = patterns->at(currentPatternIndex);
    Pattern *nextPattern = patterns->at(nextPatternIndex);
    
    //Give the ledController access to the nextPatternIndex
    //Thus it can write to it when its button is pressed and change the pattern
    ledController->givePatternIndex(&nextPatternIndex);

    //Give the LEDInterface the controller
    //This way the LEDInterface can call the output function to the controller
    //The LEDInterface can also ask the controller for hue/brightness info
    //Which is based on the sensors the controller accesses
    LEDs->giveController(ledController);

    //Initialize first pattern
    currentPattern->init();

    //Main loop
    while(1){
        if(currentPatternIndex == nextPatternIndex){
            //We are remaining on the same pattern
            printf("Current pattern run:\n");
            currentPattern->run();  //Allow pattern to create effects
            printf("Effect Engine Run:\n");
            effectEngine->run();    //Run each effect to generate LED Changes
            printf("LEDS APPLY:\n");
            LEDs->apply();          //Apply changes by collapsing LED Changes
            printf("LEDS OUTPUT\n");
            LEDs->output();         //Output to strip via controller
        }else{
            //We are changing pattern
            currentPattern->release();                      //Finish the current pattern
            printf("---BUTTON PRESSED----\n");
            effectEngine->clear();                          //Clear the effects
            LEDs->clear();
            LEDs->output();
            printf("DONE with clear\n");
            nextPatternIndex %= numPatterns;                //Protect from out of bounds
            printf("next pattern index = %d\n", nextPatternIndex);
            nextPattern = patterns->at(nextPatternIndex);   //Get the next pattern
            printf("next pattern set\n");
            currentPattern = nextPattern;                   //Set the current pattern to be the next
            printf("cur pat set\n");
            currentPatternIndex = nextPatternIndex;         //Set current pattern index to the new one
            printf("unified index\n");
            currentPattern->init();                         //Init the new current pattern
            printf("finished init\n");
            printf("NEXT LOOP\n");
        }
        //printf("next = %d\n", nextPatternIndex);
    }
    

    return 0;
}