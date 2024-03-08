#pragma once

#include <stdio.h>
#include <math.h>
#include "pico/stdlib.h"
#include "pdm_microphone.h"
#include "arm_math.h"
#include "pico/multicore.h"


// constants
#define SAMPLE_RATE       32000
#define FFT_SIZE          2048
#define FFT_MAG_SIZE      FFT_SIZE/2
#define INPUT_BUFFER_SIZE 512
#define INPUT_SHIFT       2 // 2
#define FFT_BINS_SKIP     0
#define FFT_MAG_MAX       2000.0

typedef struct{
    // We know the centers, and can track their movement
    float high_freq_center;
    float low_freq_center;
    float freq_center;

    // We know the energies, this is how loud it is;
    float high_freq_energy;
    float low_freq_energy;
    float freq_energy;
} freq_data_t;

typedef struct{
    double low_min;
    double low_max;
    double low_avg;
    double low_normal;  //Current value of low - normalized 0 - 1 with min and max
    double low_normal_min;
    double low_normal_max;
    double low_normal_normal;   // This is the best to use 0 - 1

    double high_min;
    double high_max;
    double high_avg;
    double high_normal; //Current value of low - normalized 0 - 1 with min and max
    double high_normal_min;
    double high_normal_max;
    double high_normal_normal;   // This is the best to use 0 - 1
} sound_profile_t;

void input_init_q15();
void hanning_window_init_q15(q15_t* window, size_t size);
void on_pdm_samples_ready();
void pdm_core1_entry();
void start_pdm_mic();
void pause_pdm_mic();
void resume_pdm_mic();
void updateSoundProfileLow();
void updateSoundProfileHigh();



int freq_to_bin(float freq);
float bin_to_freq(int bin);

freq_data_t *get_freq_data();
sound_profile_t *get_sound_profile();

