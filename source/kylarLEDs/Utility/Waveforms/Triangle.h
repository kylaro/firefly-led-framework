#pragma once
#include "Waveform.h"

class Triangle : public Waveform{

    public:
        using Waveform::Waveform;
        
        double sample(double index);

};