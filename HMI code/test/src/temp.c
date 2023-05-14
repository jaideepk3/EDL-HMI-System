#include "ui.h"
#include "temp.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./screens/distance_screen.h"
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "brightness.h"
#include <math.h>
#include "main.h"
#define LM35_PIN 27
 
void temp_sensor_init() {
    // adc_init();
    adc_gpio_init(LM35_PIN);
    adc_select_input(1);
}
// Initializes the temperature sensor
int a = 0;
float read_temperature() {
    // Read the voltage from the LM35 pin
   adc_select_input(1);
   float voltage = 3.3 * adc_read() / 1024;
    
    // Convert the voltage to a temperature in degrees Celsius
    float temperature = (voltage)/0.01;

    return roundf(temperature*10)/10.0;
}

// updates the temperature value displayed on the screen
void update_temperature() {
    bottomNavigation("", YELLOW, 2);
    char value[20];
    float temp = read_temperature();
    sleep_us(10);
    snprintf(value, sizeof(value), "%.1f degrees", temp);   
    GPU_DrawFilledRectangle(BLACK,120,50,100,60);
    GPU_DrawText(YELLOW,&fontDescription[2],120,75,value,strlen(value));

}


// void battery(){ char value[25];
     
//     sleep_us(10);
//     int percentage = 100-getMinutes();
//     if(percentage<5)percentage=5;
//     snprintf(value, sizeof(value), "%d%% Battery percentage", percentage);   

//     GPU_DrawFilledRectangle(BLACK,0,130,320,40);
  
//     GPU_DrawText(YELLOW,&fontDescription[2],45,140,value,strlen(value));

// }

