#include "Microphone.h"

int Microphone::initialized = 0;
Microphone::Microphone(){
    // Constructor does nothing, this will be static class
    // No need for objects
}

// static
void Microphone::start(){
    start_pdm_mic();
    initialized = 1;
}

double Microphone::getFreqCenter(){
    if(initialized){
        return get_freq_data()->freq_center;
    } else {
        return 0;
    }
    
}
double Microphone::getHighFreqCenter(){
    if(initialized){
        return get_freq_data()->high_freq_center;
    } else {
        return 0;
    }
}
double Microphone::getLowFreqCenter(){
    if(initialized){
        return get_freq_data()->low_freq_center;
    } else {
        return 0;
    }
    
}
double Microphone::getEnergy(){
    if(initialized){
        return get_freq_data()->freq_energy;
    } else {
        return 0;
    }
    
}
double Microphone::getLowEnergy(){
    if(initialized){
        return get_freq_data()->low_freq_energy;
    } else {
        return 0;
    }
    
}
double Microphone::getHighEnergy(){
    if(initialized){
        return get_freq_data()->high_freq_energy;
    } else {
        return 0;
    }
    
}

double Microphone::getLowNormal(){
    if(initialized){
        return get_sound_profile()->low_normal_normal;
    } else {
        return 0;
    }
    
}
