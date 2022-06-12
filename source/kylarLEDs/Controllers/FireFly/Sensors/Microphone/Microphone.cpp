#include "Microphone.h"


//extern void start_pdm_mic();

Microphone::Microphone(){
    
}

//static
void Microphone::start(){
    start_pdm_mic();
}