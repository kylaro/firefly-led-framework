#include "Nathan.h"
#include <stdio.h>
#include "../../Effects/SoundReactive/NathanChase.h"
#include "../../Effects/Effect.h"
#include "../../kylarLEDs/Controllers/FireFly/Sensors/Microphone/Microphone.h"

void Nathan::init()
{
    myTiming = new Timing();

    for (int i = 0; i < LEDs->num(); i++)
    {

        if (i % 4 == 0)
        {
            NathanChase *eff = new NathanChase(LEDs);
            eff->i = i;
            eff->hue = i / LEDs->num();
            Effect::engine->apply(eff);
        }
    }
}

void Nathan::run()
{
}

void Nathan::release()
{
    free(myTiming);
}