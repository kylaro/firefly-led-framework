#include "NathanChase.h"
#include "stdio.h"

void NathanChase::init()
{
}

void NathanChase::run()
{
    if (timer == NULL)
    {
        timer = new Timing();
        dirTimer = new Timing();
    }
    hue += 0.0015;
    hsv_t color = {hue, 1, 1};
    if (timer->everyMs(500))
    {
        i += dir;
    }
    if (dirT imer->everyMs(5000))
    {
        dir = -dir;
    }
    LEDs->setHSV(i, color);
}

void NathanChase::release()
{
    done = 1;
}