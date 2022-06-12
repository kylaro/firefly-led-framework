#include "Microphone.h"

Microphone::Microphone(){
    // Constructor does nothing, this will be  class
    // No need for objects
}

// static
void Microphone::start(){
    start_pdm_mic();
}

 float Microphone::getFreqCenter(){
    return get_freq_data()->freq_center;
}
 float Microphone::getHighFreqCenter(){
    return get_freq_data()->high_freq_center;
}
 float Microphone::getLowFreqCenter(){
    return get_freq_data()->low_freq_center;
}
 float Microphone::getEnergy(){
    return get_freq_data()->freq_energy;
}
 float Microphone::getLowEnergy(){
    return get_freq_data()->low_freq_energy;
}
 float Microphone::getHighEnergy(){
    return get_freq_data()->high_freq_energy;
}