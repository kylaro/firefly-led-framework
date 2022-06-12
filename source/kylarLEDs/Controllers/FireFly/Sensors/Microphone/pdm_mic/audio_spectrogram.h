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



void input_init_q15();
void hanning_window_init_q15(q15_t* window, size_t size);
void on_pdm_samples_ready();
void pdm_core1_entry();
void start_pdm_mic();