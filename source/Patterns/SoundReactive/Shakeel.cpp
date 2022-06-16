#include "Shakeel.h"
#include <stdio.h>
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void Shakeel::init()
{
    myTiming = new Timing();
    pixels = new std::vector<SoundPixel *>();
    double symmetryPoint = LEDs->num() / 2;
    for (int i = 0; i < LEDs->num(); i++)
    {
        SoundPixel *eff = new SoundPixel(LEDs);
        eff->i = i;
        if (i < symmetryPoint)
        {
            eff->hue = i / symmetryPoint;
        }
        else
        {
            eff->hue = 1.0 - ((i - symmetryPoint) / symmetryPoint);
        }
        Effect::engine->apply(eff);
        pixels->push_back(eff);
    }
}

void Shakeel::run()
{
    double micVal = Microphone::getLowNormal();
    static double hueAdd = 0;

    // Color movement
    double micAdd = micVal / 50.0;
    hueAdd = (hueAdd * 4.0 + micAdd) / 5.0;
    if (micAdd > hueAdd)
    {
        hueAdd = micAdd;
    }

    // SoundPixel one; // value of type SoundPixel
    // one.micVal;
    // SoundPixel *two = new SoundPixel(); // memory address of type SoundPixel
    // two->micVal = 0;
    // SoundPixel three = *two; // dereference pointer
    // SoundPixel *four = &one; // get memory address / reference to SoundPixel one
    // four->micVal = 0;        // sets one's micVal to 0

        for (SoundPixel *pixel : *pixels)
    {

        pixel->micVal = micVal;
        pixel->hueAdd = hueAdd;
    }
}

void Shakeel::release()
{
    free(myTiming);
    free(pixels);
}