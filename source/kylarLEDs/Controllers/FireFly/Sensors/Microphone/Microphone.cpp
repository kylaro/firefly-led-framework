#include "Microphone.h"

Microphone::Microphone(){
    // Constructor does nothing, this will be  class
    // No need for objects
}

// static
void Microphone::start(){
    start_pdm_mic();
}

double Microphone::getFreqCenter(){
    return get_freq_data()->freq_center;
}
double Microphone::getHighFreqCenter(){
    return get_freq_data()->high_freq_center;
}
double Microphone::getLowFreqCenter(){
    return get_freq_data()->low_freq_center;
}
double Microphone::getEnergy(){
    return get_freq_data()->freq_energy;
}
double Microphone::getLowEnergy(){
    return get_freq_data()->low_freq_energy;
}
double Microphone::getHighEnergy(){
    return get_freq_data()->high_freq_energy;
}

double Microphone::getLowNormal(){
    return get_sound_profile()->low_normal_normal;
}
