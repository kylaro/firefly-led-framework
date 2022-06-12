#include "audio_spectrogram.h"


// microphone configuration
const struct pdm_microphone_config pdm_config = {
    // GPIO pin for the PDM DAT signal
    .gpio_data = 20,
    // GPIO pin for the PDM CLK signal
    .gpio_clk = 21,
    // PIO instance to use
    .pio = pio1,
    // PIO State Machine instance to use
    .pio_sm = 0,
    // sample rate in Hz
    .sample_rate = SAMPLE_RATE,
    // number of samples to buffer
    .sample_buffer_size = INPUT_BUFFER_SIZE,
};

q15_t capture_buffer_q15[INPUT_BUFFER_SIZE];
volatile int new_samples_captured = 0;

q15_t input_q15[FFT_SIZE];
q15_t window_q15[FFT_SIZE];
q15_t windowed_input_q15[FFT_SIZE];

arm_rfft_instance_q15 S_q15;

q15_t fft_q15[FFT_SIZE * 2];
q15_t fft_mag_q15[FFT_MAG_SIZE];

void pdm_core1_entry(){
    //Init:
    // initialize the hanning window and RFFT instance
    hanning_window_init_q15(window_q15, FFT_SIZE);
    arm_rfft_init_q15(&S_q15, FFT_SIZE, 0, 1);

    //Loop:
    // initialize the PDM microphone
    if (pdm_microphone_init(&pdm_config) < 0) {
        printf("PDM microphone initialization failed!\n");
        while (pdm_microphone_init(&pdm_config) < 0) { tight_loop_contents(); }
    }

    // set callback that is called when all the samples in the library
    // internal sample buffer are ready for reading
    pdm_microphone_set_samples_ready_handler(on_pdm_samples_ready);

    // start capturing data from the PDM microphone
    if (pdm_microphone_start() < 0) {
        printf("PDM microphone start failed!\n");
        while (pdm_microphone_start() < 0) { tight_loop_contents(); }
    }

    while(1) {
        while (new_samples_captured == 0) {
            tight_loop_contents();
        }
        new_samples_captured = 0;

        // move input buffer values over by INPUT_BUFFER_SIZE samples
        arm_copy_q15(input_q15 + INPUT_BUFFER_SIZE, input_q15, (FFT_SIZE - INPUT_BUFFER_SIZE));

        // copy new samples to end of the input buffer with a bit shift of INPUT_SHIFT
        arm_shift_q15(capture_buffer_q15, INPUT_SHIFT, input_q15 + (FFT_SIZE - INPUT_BUFFER_SIZE), INPUT_BUFFER_SIZE);
    
        // apply the DSP pipeline: Hanning Window + FFT
        arm_mult_q15(window_q15, input_q15, windowed_input_q15, FFT_SIZE);
        arm_rfft_q15(&S_q15, windowed_input_q15, fft_q15);
        arm_cmplx_mag_q15(fft_q15, fft_mag_q15, FFT_MAG_SIZE);



        // Audio processing:
        printf("|");
        // map the FFT magnitude values to pixel values
        for (int i = 0; i < FFT_MAG_SIZE/3; i++) {
            // get the current FFT magnitude value
            q15_t magnitude = fft_mag_q15[i];

            // scale it between 0 to 255 to map, so we can map it to a color based on the color map
            int color_index = (magnitude / FFT_MAG_MAX) * 255;
            char symbol = ' ';
            if (color_index > 160) {
                color_index = 255;
                symbol = 'X';
            }else if(color_index > 80) {
                symbol= 'x';
            }else if(color_index > 40) {
                symbol = '.';
            }
            printf("%c", symbol);
        }
        printf("|\n");
    }
}



void hanning_window_init_q15(q15_t* window, size_t size) {
    for (size_t i = 0; i < size; i++) {
       float32_t f = 0.5 * (1.0 - arm_cos_f32(2 * PI * i / FFT_SIZE ));

       arm_float_to_q15(&f, &window_q15[i], 1);
    }
}

void on_pdm_samples_ready()
{
    // callback from library when all the samples in the library
    // internal sample buffer are ready for reading 
    new_samples_captured = pdm_microphone_read(capture_buffer_q15, FFT_MAG_SIZE);
}

void start_pdm_mic(){
    multicore_launch_core1(pdm_core1_entry);
}