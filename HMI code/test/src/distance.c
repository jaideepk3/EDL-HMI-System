 
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "./screens/distance_screen.h"
#include "distance.h"
#include "temp.h"
#include <math.h>
#define GPIO_TRIGGER  22
#define GPIO_ECHO 21
#define v0 331.3
#define Tk 273.15
float vsound, temperature;

//initialize hardware pins (Trigger and Echo)
void distance_sensor_init(){
    gpio_init(GPIO_ECHO);
    gpio_set_dir(GPIO_ECHO,false);
    gpio_init(GPIO_TRIGGER);
    gpio_set_dir(GPIO_TRIGGER,true);
}

//find distance using ultrasonic sensor
float calc_distance(){
    uint32_t s,e;
  
    gpio_put(GPIO_TRIGGER,true);
    busy_wait_us(20);
    gpio_put(GPIO_TRIGGER,false);

    uint32_t t0 = time_us_32();
    
    while(gpio_get(GPIO_ECHO)==0){
        s = time_us_32();
    }
  
    while(gpio_get(GPIO_ECHO)>0){
        e = time_us_32();
    }
    
 
    //temperature = (int16_t)read_temperature();
    temperature  = 30;
    vsound = v0 * sqrt(1 + temperature/Tk);
    //time for which echo pin was on
    uint32_t time_elapsed = e-s;

    //calculate distance value
    float distance =  (((float)time_elapsed)*1e-4*vsound)/2;
    distance = roundf(100*distance)/100.0;
    return distance;
}

//update distance value on UI
void update_distance(){
    char value[15];
    float distance = calc_distance();
    if(distance>400){
        snprintf( value, sizeof(value), " > %d cm", 400);
    }
    else snprintf( value, sizeof(value), "%.2f cm", distance);    // convert distance to a string using the snprintf()
    value_box(value);   
    return ;
} 