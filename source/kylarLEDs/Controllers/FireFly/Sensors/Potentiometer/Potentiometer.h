#pragma once

class Potentiometer {
    public:
        Potentiometer(int pin, int adc);
        double getValue(); // 0.0 to 1.0
    private:
        int pin;
        int adc;

};