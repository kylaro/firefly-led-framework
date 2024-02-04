#include "SpaceXLogo.h"
#include "stdio.h"

const int num_layers = 3;
ihsv_t image_0_hsv_efficient[21] = {
{ 228, { 0.0, 0.0, 1.0 } },{ 37, { 0.0, 0.0, 1.0 } },{ 58, { 0.0, 0.0, 1.0 } },{ 197, { 0.0, 0.0, 1.0 } },{ 57, { 0.0, 0.0, 1.0 } },{ 70, { 0.0, 0.0, 1.0 } },{ 166, { 0.0, 0.0, 1.0 } },{ 135, { 0.0, 0.0, 1.0 } },{ 152, { 0.0, 0.0, 1.0 } },{ 104, { 0.0, 0.0, 1.0 } },{ 119, { 0.0, 0.0, 1.0 } },{ 86, { 0.0, 0.0, 1.0 } },{ 105, { 0.0, 0.0, 1.0 } },{ 53, { 0.0, 0.0, 1.0 } },{ 74, { 0.0, 0.0, 1.0 } },{ 149, { 0.0, 0.0, 1.0 } },{ 170, { 0.0, 0.0, 1.0 } },{ 43, { 0.0, 0.0, 1.0 } },{ 52, { 0.0, 0.0, 1.0 } },{ 171, { 0.0, 0.0, 1.0 } },{ 180, { 0.0, 0.0, 1.0 } },};
ihsv_t image_1_hsv_efficient[29] = {
{ 252, { 0.0, 0.0, 1.0 } },{ 219, { 0.0, 0.0, 1.0 } },{ 251, { 0.0, 0.0, 1.0 } },{ 26, { 0.0, 0.0, 1.0 } },{ 69, { 0.0, 0.0, 1.0 } },{ 186, { 0.0, 0.0, 1.0 } },{ 218, { 0.0, 0.0, 1.0 } },{ 38, { 0.0, 0.0, 1.0 } },{ 89, { 0.0, 0.0, 1.0 } },{ 153, { 0.0, 0.0, 1.0 } },{ 185, { 0.0, 0.0, 1.0 } },{ 71, { 0.0, 0.0, 1.0 } },{ 120, { 0.0, 0.0, 1.0 } },{ 87, { 0.0, 0.0, 1.0 } },{ 136, { 0.0, 0.0, 1.0 } },{ 73, { 0.0, 0.0, 1.0 } },{ 150, { 0.0, 0.0, 1.0 } },{ 85, { 0.0, 0.0, 1.0 } },{ 138, { 0.0, 0.0, 1.0 } },{ 181, { 0.0, 0.0, 1.0 } },{ 75, { 0.0, 0.0, 1.0 } },{ 148, { 0.0, 0.0, 1.0 } },{ 203, { 0.0, 0.0, 1.0 } },{ 19, { 0.0, 0.0, 1.0 } },{ 44, { 0.0, 0.0, 1.0 } },{ 51, { 0.0, 0.0, 1.0 } },{ 179, { 0.0, 0.0, 1.0 } },{ 204, { 0.0, 0.0, 1.0 } },{ 211, { 0.0, 0.0, 1.0 } },};
ihsv_t image_2_hsv_efficient[32] = {
{ 227, { 0.0, 0.0, 1.0 } },{ 4, { 0.0, 0.0, 1.0 } },{ 27, { 0.0, 0.0, 1.0 } },{ 36, { 0.0, 0.0, 1.0 } },{ 59, { 0.0, 0.0, 1.0 } },{ 196, { 0.0, 0.0, 1.0 } },{ 5, { 0.0, 0.0, 1.0 } },{ 90, { 0.0, 0.0, 1.0 } },{ 165, { 0.0, 0.0, 1.0 } },{ 229, { 0.0, 0.0, 1.0 } },{ 102, { 0.0, 0.0, 1.0 } },{ 134, { 0.0, 0.0, 1.0 } },{ 198, { 0.0, 0.0, 1.0 } },{ 56, { 0.0, 0.0, 1.0 } },{ 88, { 0.0, 0.0, 1.0 } },{ 103, { 0.0, 0.0, 1.0 } },{ 167, { 0.0, 0.0, 1.0 } },{ 151, { 0.0, 0.0, 1.0 } },{ 54, { 0.0, 0.0, 1.0 } },{ 118, { 0.0, 0.0, 1.0 } },{ 137, { 0.0, 0.0, 1.0 } },{ 169, { 0.0, 0.0, 1.0 } },{ 42, { 0.0, 0.0, 1.0 } },{ 106, { 0.0, 0.0, 1.0 } },{ 11, { 0.0, 0.0, 1.0 } },{ 20, { 0.0, 0.0, 1.0 } },{ 84, { 0.0, 0.0, 1.0 } },{ 212, { 0.0, 0.0, 1.0 } },{ 12, { 0.0, 0.0, 1.0 } },{ 76, { 0.0, 0.0, 1.0 } },{ 172, { 0.0, 0.0, 1.0 } },{ 236, { 0.0, 0.0, 1.0 } },};
 
ihsv_t* image_pointers[] = { image_0_hsv_efficient, image_1_hsv_efficient, image_2_hsv_efficient };
int image_lengths[] = { 21, 29, 32 };

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
    
    
}
void SpaceXLogo::setBrightness(float b){
    //color_fifo[0] = {0, 1, b};
    printf("b = %f\n", b);
    brightness = b; // using the brightness variable will break this.

    ihsv_t led = {0 , {0.0, 0.0, 0}};
    for(int layer = 0; layer < num_layers; layer++){
        for(int i = 0; i < image_lengths[layer]; i++){
            led = image_pointers[layer][i];
            //led.hsv.h = layer/(float)num_layers;
            //led.hsv.s = 1;
            led.hsv.v = 0;
            switch(layer){
                case 0:
                    led.hsv.v = 0.5;
                    break;
                case 1:
                    led.hsv.v = 0.2;
                    break;
                case 2:
                    led.hsv.v = 0.05;
                    break;
            }

            //printf("1. hsv.v = %f\n", led.hsv.v);
            //printf("1.5 adding brightness = %f\n", b);
            led.hsv.v += b;
            //printf("2. hsv.v = %f\n", led.hsv.v);
            
            //printf("3. hsv.v = %f\n", led.hsv.v);
            //printf("set %d to %f\n", led.i, led.hsv.v);
            LEDs::setHSV(led.i, led.hsv);

        }
        
    }
}


void SpaceXLogo::run(){
    //hue += 0.0015;
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

    


    
}

SpaceXLogo::~SpaceXLogo(){
    
}