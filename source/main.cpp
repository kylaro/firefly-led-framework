#include "pico/stdlib.h"
#include "stdio.h"
#include "kylarLEDs/Controllers/Controller.h"

int main(){
    int LED_PIN = 25; // Built-in LED pin
    
    //Initialize built-in LED
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // initialize stdio
    stdio_init_all();

    Controller *controller = new Controller();
    
    while(1){
        printf("off\n");
        gpio_put(LED_PIN, 0);
        sleep_ms(250);
        printf("on\n");
        gpio_put(LED_PIN, 1);
        sleep_ms(250);
        printf("object proof 5 = %d\n",controller->getValue());
    }
    

    return 0;
}