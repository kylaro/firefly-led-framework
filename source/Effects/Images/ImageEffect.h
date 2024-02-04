#pragma once
#include "../kylarLEDs/LEDInterface/LEDs.h"
#include "../kylarLEDs/EffectEngine/EffectEngine.h"
#include "../Effect.h" // Adjust the path as necessary
#include <vector>

class ImageEffect : public Effect {
public:
    ImageEffect();
    virtual ~ImageEffect();
    void run() override; // Implement the drawing logic in this method
    void init() override; // Initialize your image data here

    // Sets the image data; you might need a different method signature based on how your image data is structured
    //void setImage(const std::vector<std::vector<int>>& imageData);

    // Specify the drawing start coordinates
    void setXY(int x, int y);

private:
    std::vector<std::vector<int>> imageData; // 2D vector to store the image data
    int x = 0; // X-coordinate for the starting point of the image draw
    int y = 0; // Y-coordinate for the starting point of the image draw
    
    // Method to draw the image on the LED display
    void drawImage();
};
