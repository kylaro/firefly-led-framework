#include "Waveform.h"


Waveform::Waveform(){

}

Waveform::Waveform(uint32_t periodMs){
    period = periodMs;
}

Waveform::~Waveform(){
    delete(timer);
}

void Waveform::initTimer(){
    timer = new Timing();
}

void Waveform::setPeriodMs(uint32_t ms){
    period = ms;
}

double Waveform::value(){
    if(timer == NULL){
        initTimer();
        return sample(0);
    }
    uint64_t time = timer->timerMs();
    double index = (time % period)/((double)period);
    return sample(index);
}

int Waveform::complete(){
    if(timer == NULL){
        return 0;
    }
    uint64_t time = timer->timerMs();
    return time / period;
}