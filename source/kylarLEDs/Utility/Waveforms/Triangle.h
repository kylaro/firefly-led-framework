#pragma once
#include "Waveform.h"

class Triangle : public Waveform{

    public:
        using Waveform::Waveform;
        // ~Triangle();
        double sample(double index);

};