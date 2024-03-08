#include "Heart.h"
#include "stdio.h"
// uint8_t image_0_hsv_efficient_heart[104] = 
// { 67, 92, 99, 163, 188, 195, 59, 68, 91, 100, 123, 155, 164, 187, 196, 219, 37, 58, 69, 90, 101, 122, 133, 154, 165, 186, 197, 218, 229, 38, 57, 70, 89, 102, 121, 134, 153, 166, 185, 198, 217, 230, 39, 56, 71, 88, 103, 120, 135, 152, 167, 184, 199, 216, 231, 40, 55, 72, 87, 104, 119, 136, 151, 168, 183, 200, 215, 232, 54, 73, 86, 105, 118, 137, 150, 169, 182, 201, 214, 74, 85, 106, 117, 138, 149, 170, 181, 202, 84, 107, 116, 139, 148, 171, 180, 108, 115, 140, 147, 172, 114, 141, 146, 142,};
// uint8_t image_1_hsv_efficient_heart[41] = 
// { 32, 96, 160, 255, 62, 97, 161, 225, 2, 66, 125, 157, 221, 28, 131, 252, 36, 132, 228, 7, 24, 248, 22, 233, 10, 245, 52, 212, 44, 236, 18, 82, 178, 242, 14, 78, 206, 48, 112, 144, 208,};
// uint8_t image_2_hsv_efficient_heart[42] = 
// { 63, 127, 191, 1, 65, 126, 190, 254, 29, 93, 130, 162, 226, 35, 156, 220, 251, 6, 25, 23, 247, 9, 53, 234, 43, 203, 244, 19, 83, 211, 13, 77, 173, 237, 49, 113, 177, 241, 47, 111, 143, 207,};
// uint8_t image_3_hsv_efficient_heart[38] = 
// { 0, 64, 128, 192, 30, 94, 129, 193, 34, 98, 189, 253, 60, 124, 227, 5, 26, 250, 8, 246, 42, 213, 20, 235, 12, 76, 204, 243, 50, 210, 46, 110, 174, 238, 16, 80, 176, 240,};
// uint8_t image_4_hsv_efficient_heart[29] = 
// { 31, 95, 159, 223, 33, 158, 222, 61, 194, 4, 27, 249, 41, 21, 11, 75, 51, 179, 45, 109, 205, 17, 81, 145, 209, 15, 79, 175, 239,};
// uint8_t image_outline_heart[30] = 
// { 67, 92, 99, 163, 188, 195, 59, 123, 155, 219, 37, 133, 229, 38, 230, 39, 231, 40, 232, 54, 214, 74, 202, 84, 180, 108, 172, 114, 146, 142,};
 
// const int num_layers_heart = 5;
// uint8_t* image_pointers_heart[] = { image_0_hsv_efficient_heart, image_1_hsv_efficient_heart, image_2_hsv_efficient_heart, image_3_hsv_efficient_heart, image_4_hsv_efficient_heart };
// uint8_t image_lengths_heart[] = { 104, 41, 42, 38, 29, 30 };
uint8_t image_0_hsv_efficient_heart[104] = 
{ 67, 92, 99, 163, 188, 195, 59, 68, 91, 100, 123, 155, 164, 187, 196, 219, 37, 58, 69, 90, 101, 122, 133, 154, 165, 186, 197, 218, 229, 38, 57, 70, 89, 102, 121, 134, 153, 166, 185, 198, 217, 230, 39, 56, 71, 88, 103, 120, 135, 152, 167, 184, 199, 216, 231, 40, 55, 72, 87, 104, 119, 136, 151, 168, 183, 200, 215, 232, 54, 73, 86, 105, 118, 137, 150, 169, 182, 201, 214, 74, 85, 106, 117, 138, 149, 170, 181, 202, 84, 107, 116, 139, 148, 171, 180, 108, 115, 140, 147, 172, 114, 141, 146, 142,};
uint8_t image_1_hsv_efficient_heart[14] = 
{ 160, 158, 130, 131, 132, 75, 203, 51, 211, 45, 237, 17, 241, 15,};
uint8_t image_2_hsv_efficient_heart[12] = 
{ 191, 161, 157, 156, 52, 44, 204, 18, 210, 14, 238, 240,};
uint8_t image_3_hsv_efficient_heart[11] = 
{ 192, 190, 162, 53, 43, 19, 179, 13, 205, 209, 239,};
uint8_t image_4_hsv_efficient_heart[9] = 
{ 223, 193, 189, 42, 20, 12, 178, 206, 208,};
uint8_t image_5_hsv_efficient_heart[9] = 
{ 224, 222, 194, 41, 21, 11, 173, 177, 207,};
uint8_t image_6_hsv_efficient_heart[7] = 
{ 255, 225, 221, 22, 10, 174, 176,};
uint8_t image_7_hsv_efficient_heart[7] = 
{ 254, 226, 220, 23, 9, 145, 175,};
uint8_t image_8_hsv_efficient_heart[4] = 
{ 253, 227, 8, 144,};
uint8_t image_9_hsv_efficient_heart[10] = 
{ 252, 228, 251, 6, 25, 7, 24, 113, 112, 143,};
uint8_t image_10_hsv_efficient_heart[10] = 
{ 4, 5, 26, 250, 249, 248, 109, 110, 80, 111,};
uint8_t image_11_hsv_efficient_heart[11] = 
{ 2, 3, 27, 36, 247, 233, 246, 83, 82, 81, 79,};
uint8_t image_12_hsv_efficient_heart[11] = 
{ 0, 1, 29, 35, 60, 213, 234, 244, 77, 78, 48,};
uint8_t image_13_hsv_efficient_heart[13] = 
{ 31, 32, 30, 33, 34, 61, 212, 235, 76, 243, 50, 49, 47,};
uint8_t image_14_hsv_efficient_heart[9] = 
{ 63, 62, 65, 66, 93, 236, 242, 46, 16,};
uint8_t image_15_hsv_efficient_heart[5] = 
{ 64, 95, 94, 97, 98,};
uint8_t image_16_hsv_efficient_heart[7] = 
{ 96, 127, 128, 126, 129, 125, 124,};
uint8_t image_outline_heart[30] = 
{ 67, 92, 99, 163, 188, 195, 59, 123, 155, 219, 37, 133, 229, 38, 230, 39, 231, 40, 232, 54, 214, 74, 202, 84, 180, 108, 172, 114, 146, 142,};
 
const int num_layers_heart = 17;
uint8_t* image_pointers_heart[] = { image_0_hsv_efficient_heart, image_1_hsv_efficient_heart, image_2_hsv_efficient_heart, image_3_hsv_efficient_heart, image_4_hsv_efficient_heart, image_5_hsv_efficient_heart, image_6_hsv_efficient_heart, image_7_hsv_efficient_heart, image_8_hsv_efficient_heart, image_9_hsv_efficient_heart, image_10_hsv_efficient_heart, image_11_hsv_efficient_heart, image_12_hsv_efficient_heart, image_13_hsv_efficient_heart, image_14_hsv_efficient_heart, image_15_hsv_efficient_heart, image_16_hsv_efficient_heart,  };
uint8_t image_lengths_heart[] = { 104, 14, 12, 11, 9, 9, 7, 7, 4, 10, 10, 11, 11, 13, 9, 5, 7, 30 };





float color_fifo_heart[num_layers_heart-1]; // This is the number of images in the animation



void Heart::init(){
    hueTimer = new Timing();
    fifoTimer = new Timing();
    
    
}

void Heart::clamp(float *x, float min, float max){
    if( *x < min){
        *x = min;
    }else if(*x > max){
        *x = max;
    }
}

void Heart::shiftFifo(){
    
    float exchange_rate = speed*0.2*fifoTimer->takeMsEvery(1); // 0.9
    // At the end the color falls into the void
    //printf("color fifo 0 = %f\n", color_fifo[0]);
    color_fifo_heart[num_layers_heart-1] = (color_fifo_heart[num_layers_heart-1] * 10.0 - exchange_rate*color_fifo_heart[num_layers_heart-1])/11.0;
    
    
    for(int i = num_layers_heart - 1; i >= 1; i--){
        
        float receiver = color_fifo_heart[i];
        float donor = color_fifo_heart[i-1];
        float exchange = donor * exchange_rate;
        color_fifo_heart[i] = (color_fifo_heart[i] * 10.0 + receiver + exchange)/11.0;
        color_fifo_heart[i-1] = (color_fifo_heart[i-1] * 10.0 + donor - exchange)/11.0;

        clamp(&color_fifo_heart[i], 0.0, 1.0);
        
    }
    //printf("\n");

}


void Heart::setBrightness(float b){
    //color_fifo[0] = {0, 1, b};
    // if(color_fifo[1] > b){
    //     b *= 0.5;
    // }
    //color_fifo[0] = 1.5*b*b;
    b = b*b;
    speed = 1+b*0.5;
    color_fifo_heart[0] = b;
    // double fifo_avg = 0;
    // for(int i = 0; i < num_layers; i++){
    //     fifo_avg += color_fifo[i];
    // }
    // fifo_avg /= (double)num_layers;

    // if(b > fifo_avg*0.6){
    //     color_fifo[0] = b;
    // }else{
    //     color_fifo[0] = b*0.9;
    // }
    //color_fifo[0] = b > color_fifo[0] && b > color_fifo[1] ? b : color_fifo[0]*color_fifo[0]*color_fifo[0];
    //clamp(&color_fifo[0], 0, 1);
    //printf("b = %f\n", b);
    
}


void Heart::run(){
    
    // static int initted = 0;
    // if(!initted){
    //     init();
    //     initted = 1;
    // }
    
    // rgb8_t color = {0, 0, 0};
    // int r, c = 0;
    // for(int i = 0; i < NUM_LEDS; i++){
    //     pixel_to_array(i, &r, &c);
    //     // color.r = image[r][c][0];
    //     // color.g = image[r][c][1];
    //     // color.b = image[r][c][2];
    //     // LEDs::setRGB(i, color);
    //     LEDs::setHSV(i, image_hsv[r][c]);
    // }

    shiftFifo();
    
    

    //brightness = b; // using the brightness variable will break this.
    
    hue -= speed*0.001*hueTimer->takeMsEvery(4);//0.006;
    //printf("hue = %f\n", hue);
    int led = 0;
    hsv_t hsv = {0, 0, 0};
    for(int layer = 0; layer < num_layers_heart; layer++){
        for(int i = 0; i < image_lengths_heart[layer]; i++){
            led = image_pointers_heart[layer][i];
            //led.hsv.h = layer/(float)num_layers;
            //led.hsv.s = 1;

            hsv.s = 0;
            if(layer == 0){
                hsv.v =  0.3+(color_fifo_heart[0]+color_fifo_heart[1]+color_fifo_heart[2])*3.0;
                hsv.s = 1;
                hsv.h = 0.98;// + (i/256.0)*0.04;
                LEDs::setHSV(led, hsv);
                continue;
                //hsv.v = 0.6 + color_fifo[0] * 0.6;
            }else{
                hsv.v = color_fifo_heart[layer];
                
                // if(hsv.v > 0.3){
                //     hsv.v *= 1.5;
                // }else{
                //     hsv.v *= 0.75;
                // }
                clamp(&hsv.v, 0.0, 0.8);//(color_fifo[0]+color_fifo[1]+color_fifo[2])*3.0 + 0.6);
                hsv.s = 1;
            }
            // switch statement 84531 us
            hsv.h = hue + 0.4*(layer/(float)num_layers_heart);
            LEDs::setHSV(led, hsv);

            //printf("1. hsv.v = %f\n", led.hsv.v);
            //printf("1.5 adding brightness = %f\n", b);
            //hsv.v += b;
            
            
            
            //printf("2. hsv.v = %f\n", led.hsv.v);
            
            //printf("3. hsv.v = %f\n", led.hsv.v);
            //printf("set %d to %f\n", led.i, led.hsv.v);
            

        }
        
    }

    // Dim the outline by setting to dark
    for(int i = 0; i < 30; i++){
        LEDs::setHSV(image_outline_heart[i], {0,0,0.5});
        //LEDs::setHSV(image_outline[i], {0,0,0});
    }

    


    
}

Heart::~Heart(){
    
}