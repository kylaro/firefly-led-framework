#include "audio_spectrogram.h"
#include "pico/time.h"

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

freq_data_t freq_data;
freq_data_t temp_freq_data;
sound_profile_t sound_profile;

const int print = 0;
const int exec_timing = 0;
absolute_time_t new_time; //Microseconds
absolute_time_t cur_time;
absolute_time_t start_time;
void pdm_core1_entry(){
    //Init:
    // initialize the hanning window and RFFT instance
    sleep_ms(10); //delay here so that the dma channel doesn't get claimed..
    hanning_window_init_q15(window_q15, FFT_SIZE);
    arm_rfft_init_q15(&S_q15, FFT_SIZE, 0, 1);

    multicore_lockout_victim_init();// NEEDED FOR MULTICORE LOCKOUT

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

    int starting_bin = 2;
    float low_bins = 14;
    float high_bins = 6; // 240
    float total_bins = low_bins + high_bins;
    
    
    while(1) {
        if(exec_timing){
            new_time = get_absolute_time(); //Microseconds
            start_time = new_time;
        }
        
        // Waiting for new samples
        while (new_samples_captured == 0) {
            tight_loop_contents();
        }
        if(exec_timing){
            cur_time = get_absolute_time();
            printf("wait = %.1f us\n", (double)(cur_time-start_time));
            start_time = get_absolute_time();
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

        if(exec_timing){
            cur_time = get_absolute_time();
            printf("arm stuff = %.1f us\n", (double)(cur_time-start_time));
            start_time = get_absolute_time();
        }
        

        // Audio processing:
        if(print){
            printf("|");
        }
        temp_freq_data.freq_energy = 0;
        temp_freq_data.low_freq_energy = 0;
        temp_freq_data.high_freq_energy = 0;

        // map the FFT magnitude values to pixel values
        for (int i = starting_bin; i < FFT_MAG_SIZE/3; i++) {
            // get the current FFT magnitude value
            q15_t magnitude = fft_mag_q15[i];
            int bin = i-starting_bin;

            
            if(bin <= low_bins){
                //LOWS
                temp_freq_data.freq_energy += magnitude / total_bins;
                temp_freq_data.low_freq_energy += magnitude / low_bins;
            }else if(bin - low_bins <= high_bins){
                //HIGHS
                //(skip)
            }else{
                // Out of range
                //(high after skip)
                temp_freq_data.freq_energy += magnitude / total_bins;
                temp_freq_data.high_freq_energy += magnitude / 10.0; //high_bins;
            }
                
            
            // scale it between 0 to 255 to map, so we can map it to a color based on the color map
            if(print){
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
            
        }
        if(print){
            printf("|\n");
        }

        if(exec_timing){
            //cur_time = get_absolute_time();
            printf("sum bins = %.1f us\n", (double)(get_absolute_time()-start_time));
            start_time = get_absolute_time();
        }

        freq_data.freq_energy = temp_freq_data.freq_energy;
        freq_data.low_freq_energy = temp_freq_data.low_freq_energy;
        freq_data.high_freq_energy = temp_freq_data.high_freq_energy;
        //printf("CORE1 %.0f %.0f %.0f\n", freq_data.low_freq_energy, freq_data.high_freq_energy, freq_data.freq_energy);
        updateSoundProfileLow();
        updateSoundProfileHigh();
        if(exec_timing){
            //cur_time = get_absolute_time();
            printf("profile = %.1f us\n", (double)(get_absolute_time()-start_time));
            start_time = get_absolute_time();
        }

        if(exec_timing){
            printf("sound FPS = %.1f / sec\n\n", 1000000.0/(double)(get_absolute_time() - new_time));
        }
    }
}

//What would be cool is to have it arranged in a normal distribution kinda way...
void updateSoundProfileLow() {
    //Only doing LOWS for now...
    //Update min
    double coef = 10.0;
    
    if(freq_data.low_freq_energy < sound_profile.low_min){
        //The frequency is lower!
        sound_profile.low_min = freq_data.low_freq_energy;//(sound_profile.low_min*coef + freq_data.low_freq_energy)/(coef+1);
    }else{
        sound_profile.low_min = (sound_profile.low_min*1000.0 + freq_data.low_freq_energy)/(1001.0);
    }

    //Update max
    if(freq_data.low_freq_energy > sound_profile.low_max){
        //The frequency is higher!
        sound_profile.low_max = freq_data.low_freq_energy;//(sound_profile.low_max*coef + freq_data.low_freq_energy)/(coef+1);
    }else{
        sound_profile.low_max *= 0.999;
    }

    //Update avg
    sound_profile.low_avg = (sound_profile.low_avg*coef + freq_data.low_freq_energy)/(coef+1);

    //Calculate normalized value
    sound_profile.low_normal = (freq_data.low_freq_energy - sound_profile.low_min)/(sound_profile.low_min+sound_profile.low_max);
    if(sound_profile.low_normal < 0){
        sound_profile.low_normal = 0;
    }
    // printf("%1.3f: \t%4.2f\t<-\t%4.2f\t->\t%4.2f\t", sound_profile.low_normal, sound_profile.low_min, sound_profile.low_avg, sound_profile.low_max);
    // for(int i = 0; i < sound_profile.low_normal/0.1; i++){
    //     printf("+");
    // }
    // printf("\n");

    // Calculated normal's min
    coef = 10.0;
    if(sound_profile.low_normal < sound_profile.low_normal_min){
        //The frequency is lower!
        sound_profile.low_normal_min = sound_profile.low_normal;//(sound_profile.low_min*coef + freq_data.low_freq_energy)/(coef+1);
    }else{
        sound_profile.low_normal_min = (sound_profile.low_normal_min*400.0 + sound_profile.low_normal)/(401.0);
    }

    //Calculate normal's max
    if(sound_profile.low_normal > sound_profile.low_normal_max){
        //The frequency is higher!
        sound_profile.low_normal_max = sound_profile.low_normal;//(sound_profile.low_max*coef + freq_data.low_freq_energy)/(coef+1);
    }else{
        sound_profile.low_normal_max *= 0.999;
    }

    // Calculate normal's place in that -> normal_normal
    sound_profile.low_normal_normal = (sound_profile.low_normal - sound_profile.low_normal_min)/(sound_profile.low_normal_min+sound_profile.low_normal_max);
    if(sound_profile.low_normal_normal < 0){
        sound_profile.low_normal_normal = 0;
    }

    //Print it

    // printf("%1.3f:\t%4.2f\t<-\t%4.2f\t->\t%4.2f\t", sound_profile.low_normal_normal, sound_profile.low_normal_min, sound_profile.low_normal, sound_profile.low_normal_max);
    // printf("|");
    // int count = 10;
    // for(int i = 0; i < sound_profile.low_normal_normal/0.1; i++){
    //     printf("+");
    //     count--;
    // }
    // for(int i = 0; i < count; i++){
    //     printf(" ");
    // }
    // printf("|");
    // printf("\n");


}

void updateSoundProfileHigh() {
    //HIGHS HIGHS HIGHS

    // print high energy
    //printf("--------\n");
    //printf("high energy: %f\n", freq_data.high_freq_energy);

    //Update min
    double coef = 10.0;
    if(freq_data.high_freq_energy < sound_profile.high_min){
        //The frequency is lower!
        sound_profile.high_min = freq_data.high_freq_energy;//(sound_profile.low_min*coef + freq_data.low_freq_energy)/(coef+1);
    }else{
        sound_profile.high_min = (sound_profile.high_min*1000.0 + freq_data.high_freq_energy)/(1001.0);
    }

    //printf("high min: %f\n", sound_profile.high_min);

    //Update max
    if(freq_data.high_freq_energy > sound_profile.high_max){
        //The frequency is higher!
        sound_profile.high_max = freq_data.high_freq_energy;//(sound_profile.low_max*coef + freq_data.low_freq_energy)/(coef+1);
    }else{
        sound_profile.high_max *= 0.999;
    }

    //printf("high max: %f\n", sound_profile.high_max);

    //Update avg
    sound_profile.high_avg = (sound_profile.high_avg*coef + freq_data.high_freq_energy)/(coef+1);
    //printf("high avg: %f\n", sound_profile.high_avg);
    //Calculate normalized value
    sound_profile.high_normal = (freq_data.high_freq_energy - sound_profile.high_min)/(sound_profile.high_min+sound_profile.high_max);
    if(sound_profile.high_normal < 0){
        sound_profile.high_normal = 0;
    }

    //printf("high normal: %f\n", sound_profile.high_normal);

    // Calculated normal's min
    coef = 10.0;
    if(sound_profile.high_normal < sound_profile.high_normal_min){
        //The frequency is lower!
        sound_profile.high_normal_min = sound_profile.high_normal;//(sound_profile.low_min*coef + freq_data.low_freq_energy)/(coef+1);
    }else{
        sound_profile.high_normal_min = (sound_profile.high_normal_min*400.0 + sound_profile.high_normal)/(401.0);
    }

    //printf("high normal min: %f\n", sound_profile.high_normal_min);

    //Calculate normal's max
    if(sound_profile.high_normal > sound_profile.high_normal_max){
        //The frequency is higher!
        sound_profile.high_normal_max = sound_profile.high_normal;//(sound_profile.low_max*coef + freq_data.low_freq_energy)/(coef+1);
    }else{
        sound_profile.high_normal_max *= 0.999;
    }
    if(sound_profile.high_normal_max > 9999999){
        sound_profile.high_normal_max = sound_profile.high_normal;
    }

    //printf("high normal max: %f\n", sound_profile.high_normal_max);

    // Calculate normal's place in that -> normal_normal
    sound_profile.high_normal_normal = (sound_profile.high_normal - sound_profile.high_normal_min)/(sound_profile.high_normal_min+sound_profile.high_normal_max);
    if(sound_profile.high_normal_normal < 0){
        sound_profile.high_normal_normal = 0;
    }

    //printf("high normal normal: %f\n", sound_profile.high_normal_normal);


    // printf("%1.3f:\t%4.2f\t<-\t%4.2f\t->\t%4.2f\t", sound_profile.high_normal_normal, sound_profile.high_normal_min, sound_profile.high_normal, sound_profile.high_normal_max);
    // printf("|");
    // int count = 10;
    // for(int i = 0; i < sound_profile.high_normal_normal/0.1; i++){
    //     printf("+");
    //     count--;
    // }
    // for(int i = 0; i < count; i++){
    //     printf(" ");
    // }
    // printf("|");
    // printf("\n");


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

void pause_pdm_mic(){
    multicore_lockout_start_blocking();
}

void resume_pdm_mic(){
    multicore_lockout_end_blocking();
}


int freq_to_bin(float freq){
    int bin = (int)roundf((freq*0.064 - 0.0154));
    if(bin < 0){
        return 1; // This is the lowest valid freq bin
    }
    if(bin >= FFT_MAG_SIZE){
        return FFT_MAG_SIZE - 1; // This is the maximum valid freq bin
    }

    return bin;
}


float bin_to_freq(int bin){
    float freq = 15.628*bin + 0.286;
    if(freq < 0){
        return 0; 
    }
    if(freq >= 32000){
        return 32000; 
    }

    return freq;
}


freq_data_t *get_freq_data(){
    return &freq_data;
}

sound_profile_t *get_sound_profile(){
    return &sound_profile;
}
