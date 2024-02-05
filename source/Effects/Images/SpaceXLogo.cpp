#include "SpaceXLogo.h"
#include "stdio.h"

uint8_t image_1_hsv_efficient[21] = 
{ 228, 37, 58, 197, 57, 70, 166, 135, 152, 104, 119, 86, 105, 53, 74, 149, 170, 43, 52, 171, 180,};
uint8_t image_2_hsv_efficient[29] = 
{ 252, 219, 251, 26, 69, 186, 218, 38, 89, 153, 185, 71, 120, 87, 136, 73, 150, 85, 138, 181, 75, 148, 203, 19, 44, 51, 179, 204, 211,};
uint8_t image_3_hsv_efficient[31] = 
{ 227, 4, 27, 36, 59, 196, 5, 90, 165, 229, 102, 134, 198, 56, 88, 103, 167, 151, 54, 118, 137, 169, 42, 106, 20, 84, 212, 12, 76, 172, 236,};
uint8_t image_4_hsv_efficient[4] = 
{ 120, 87, 136, 118,};
uint8_t image_5_hsv_efficient[10] = 
{ 134, 88, 103, 120, 87, 136, 151, 118, 137, 106,};
uint8_t image_6_hsv_efficient[16] = 
{ 102, 121, 134, 71, 120, 167, 72, 87, 151, 168, 73, 118, 169, 106, 117, 138,};
uint8_t image_7_hsv_efficient[23] = 
{ 90, 165, 102, 121, 134, 153, 185, 56, 71, 167, 72, 168, 54, 73, 150, 169, 85, 106, 117, 138, 181, 84, 148,};
uint8_t image_8_hsv_efficient[30] = 
{ 59, 196, 69, 90, 101, 122, 133, 154, 165, 186, 38, 185, 198, 56, 184, 55, 183, 54, 182, 42, 181, 202, 75, 84, 107, 116, 139, 148, 76, 172,};
uint8_t image_9_hsv_efficient[43] = 
{ 28, 227, 36, 59, 68, 91, 100, 123, 132, 155, 164, 187, 196, 219, 26, 218, 229, 38, 198, 39, 199, 40, 200, 41, 201, 42, 202, 20, 203, 212, 51, 76, 83, 108, 115, 140, 147, 172, 179, 204, 236, 50, 178,};
uint8_t image_10_hsv_efficient[54] = 
{ 2, 253, 3, 28, 35, 60, 67, 92, 99, 124, 131, 156, 163, 188, 195, 220, 227, 252, 4, 27, 251, 5, 26, 218, 229, 250, 25, 217, 24, 216, 23, 215, 22, 214, 21, 213, 20, 212, 12, 19, 44, 211, 236, 45, 50, 77, 82, 109, 114, 141, 146, 173, 178, 205,};
uint8_t image_11_hsv_efficient[53] = 
{ 2, 29, 34, 61, 66, 93, 98, 125, 130, 157, 162, 189, 194, 221, 226, 252, 4, 251, 229, 6, 25, 230, 7, 231, 8, 23, 232, 9, 233, 10, 21, 234, 11, 235, 19, 236, 13, 18, 210, 237, 242, 46, 49, 78, 81, 110, 113, 142, 145, 174, 177, 206, 209,};
uint8_t image_12_hsv_efficient[43] = 
{ 1, 30, 33, 62, 65, 94, 97, 126, 129, 158, 161, 190, 193, 222, 225, 254, 250, 6, 249, 248, 8, 247, 246, 10, 245, 244, 243, 14, 17, 238, 241, 47, 48, 79, 80, 111, 112, 143, 144, 175, 176, 207, 208,};
uint8_t image_13_hsv_efficient[28] = 
{ 0, 31, 32, 63, 64, 95, 96, 127, 128, 159, 160, 191, 192, 223, 224, 255, 250, 248, 246, 244, 15, 16, 79, 112, 175, 207, 239, 240,};
 
uint8_t image_outline[50] = 
{ 226, 253, 3, 28, 35, 60, 195, 220, 68, 91, 164, 187, 101, 133, 154, 250, 6, 25, 121, 217, 230, 39, 184, 199, 55, 72, 168, 41, 182, 21, 117, 202, 213, 11, 107, 139, 235, 83, 147, 243, 13, 18, 45, 50, 77, 173, 178, 205, 210, 237,};
 

const int num_layers = 13;
uint8_t* image_pointers[] = { image_1_hsv_efficient, image_2_hsv_efficient, image_3_hsv_efficient, image_4_hsv_efficient, image_5_hsv_efficient, image_6_hsv_efficient, image_7_hsv_efficient, image_8_hsv_efficient, image_9_hsv_efficient, image_10_hsv_efficient, image_11_hsv_efficient, image_12_hsv_efficient, image_13_hsv_efficient };
uint8_t image_lengths[] = { 21, 29, 31, 4, 10, 16, 23, 30, 43, 54, 53, 43, 28 };
float color_fifo[13]; // This is the number of images in the animation

// Input is the row and column of the array
// Output is the LED index in the "strip"
int array_to_pixel(int row, int col){
    // LED Matrix is 16 by 16, in a Zig-Zag arrangement
    // 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15
    // 31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16
    int index;

    // Check if the row is even or odd to determine the direction of the LED indices
    if (row % 2 == 0) {
        // For even rows, the index increases from left to right
        index = row * 16 + col;
    } else {
        // For odd rows, the index increases from right to left
        index = row * 16 + (15 - col); // 15 is the last index in a row of 16 LEDs
    }

    return index;
}

void pixel_to_array(int i, int* row, int* col) {
    *row = i / 16; // Determine the row
    int isOddRow = *row % 2; // Check if the row is odd

    // Determine the column based on whether the row is odd or even
    if (!isOddRow) {
        *col = i % 16; // For even rows, index increases from left to right
    } else {
        *col = 15 - (i % 16); // For odd rows, index increases from right to left
    }
}

void SpaceXLogo::init(){
    hueTimer = new Timing();
    fifoTimer = new Timing();
    
    
}

void SpaceXLogo::clamp(float *x, float min, float max){
    if( *x < min){
        *x = min;
    }else if(*x > max){
        *x = max;
    }
}

void SpaceXLogo::shiftFifo(){
    
    float exchange_rate = 0.4*fifoTimer->takeMsEvery(1); // 0.08
    // At the end the color falls into the void
    //printf("color fifo 0 = %f\n", color_fifo[0]);
    color_fifo[num_layers-1] -= 2*exchange_rate*color_fifo[num_layers-1];
    
    
    for(int i = num_layers - 1; i >= 1; i--){
        
        float receiver = color_fifo[i];
        float donor = color_fifo[i-1];
        float exchange = donor * exchange_rate;
        color_fifo[i] = (color_fifo[i] * 4.0 + receiver + exchange)/5.0;
        color_fifo[i-1] = (color_fifo[i-1] * 4.0 + donor - exchange)/5.0;
        //printf(" %d:%f ", i,color_fifo[i]);
        clamp(&color_fifo[i], 0.0, 1.0);
        
    }
    //printf("\n");

}


void SpaceXLogo::setBrightness(float b){
    //color_fifo[0] = {0, 1, b};
    // if(color_fifo[1] > b){
    //     b *= 0.5;
    // }
    //color_fifo[0] = 1.5*b*b;
    b = b*b;
    color_fifo[0] = b;
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


void SpaceXLogo::run(){
    
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
    
    hue -= 0.001*hueTimer->takeMsEvery(4);//0.006;
    //printf("hue = %f\n", hue);
    int led = 0;
    hsv_t hsv = {0, 0, 0};
    for(int layer = 0; layer < num_layers; layer++){
        for(int i = 0; i < image_lengths[layer]; i++){
            led = image_pointers[layer][i];
            //led.hsv.h = layer/(float)num_layers;
            //led.hsv.s = 1;

            hsv.s = 0;
            if(layer < 3){
                hsv.v =  0.3+(color_fifo[0]+color_fifo[1]+color_fifo[2])*3.0;
                //hsv.v = 0.6 + color_fifo[0] * 0.6;
            }else{
                hsv.v = color_fifo[layer];
                
                // if(hsv.v > 0.3){
                //     hsv.v *= 1.5;
                // }else{
                //     hsv.v *= 0.75;
                // }
                clamp(&hsv.v, 0.0, 0.8);//(color_fifo[0]+color_fifo[1]+color_fifo[2])*3.0 + 0.6);
                hsv.s = 1;
            }
            // switch statement 84531 us
            hsv.h = hue + 0.33*(layer/(float)num_layers);
            

            //printf("1. hsv.v = %f\n", led.hsv.v);
            //printf("1.5 adding brightness = %f\n", b);
            //hsv.v += b;
            
            
            
            //printf("2. hsv.v = %f\n", led.hsv.v);
            
            //printf("3. hsv.v = %f\n", led.hsv.v);
            //printf("set %d to %f\n", led.i, led.hsv.v);
            LEDs::setHSV(led, hsv);

        }
        
    }

    // Dim the outline by setting to dark
    for(int i = 0; i < 50; i++){
        LEDs::setHSV(image_outline[i], {0,0,0});
        LEDs::setHSV(image_outline[i], {0,0,0});
    }

    


    
}

SpaceXLogo::~SpaceXLogo(){
    
}