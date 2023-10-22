#include "CO2.h"
#include <stdio.h>
int CO2::initialized = 0;
Timing * CO2::timing = new Timing();
CO2::CO2(){
    // Constructor does nothing, this will be static class
    // No need for objects
    
}

// static
void CO2::start(){
    scd41_init();
    initialized = 1;
}

double CO2::getCO2(){
    static uint16_t co2, temp, humidity;
    if(initialized){
        if(CO2::timing->takeMsEvery(1000)){
            scd41_read_data(&co2, &temp, &humidity);
            if (co2 != 32768) {
                printf("CO2: %d ppm, Temp: %d, Humidity: %d\n", co2, temp, humidity);
            }else{
                //printf("ERROR READING SCD41\n");
            }
        }
        
    } else {
        return 0;
    }
    return 0.1234;
}
