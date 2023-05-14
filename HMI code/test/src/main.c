#include "main.h"
#include "ui.h"
#include "interface.h"
#include "temp.h"
#include "pico/time.h"
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "./screens/simulator_screen.h"
#include "./screens/distance_screen.h"
#include "simulation.h"
#include "distance.h"
 #include "./screens/popup.h"
#include<stdint.h>
#include<stdlib.h>
#include "brightness.h"
float univ = 27;
int NUM_SCREENS = 4;
uint32_t curr_brightness =  0;
 uint8_t currPopupPage =0;
 int lastDetectedPress = 0;
GPU_Color BG_COLOR= BLACK;
int presses = 0;

bool pauseSimulation = false;
static uint32_t _lastDrawTime;
Screen currScreen = DISTANCE_SCREEN;
#define INTERVAL 5*1e6

float random_wait_time(int maxtime){
    return  (((float) rand() / (float)(RAND_MAX))*maxtime);
}

  
int end=-1;
int dist;
int new_draw_time;


//update rebar depth on simulation screen 
void distance_callback(){
    dist = (int)calc_distance();
    end+=1;
    if(end>=Q_SIZE)end=Q_SIZE;
    simulate(end,dist);
    busy_wait_ms(130);
}

void DoMainLoop()
{   
    _lastDrawTime = IF_GetCurrentTime();
  distance_sensor_init();
  bar_init();
  temp_sensor_init();
  simulation_init();
  distance_screen_init();
 
    int old=time_us_32();
    lastDetectedPress = time_us_32();
 

    while (1)
    {
       int now = time_us_32();
        //Register left keyboard events
        Keyboard();

        //update UI if popup isn't opened and achieve desired FPS
             if (( new_draw_time - _lastDrawTime > (ONE_SECOND/GPU_TARGET_FPS)) && !popup_opened)
             {
              _lastDrawTime = new_draw_time;
              GPU_Render(); //update UI on LCD screen
       } new_draw_time= IF_GetCurrentTime();
 
//rebar simulation done at regular intervals      
if((now-old>INTERVAL)&&(!pauseSimulation)){
    distance_callback();
    old=now;
}

//update UI on LCD based on current screen  
  if(currScreen ==DISTANCE_SCREEN){
   distance_screen_init();
  }
  else if(currScreen==PARAMS_SCREEN){
    update_temperature();
    display_png();//thermometer image

  }else if(currScreen == SIMULATION_SCREEN){
    display_simulation(end);
  }else if(currScreen == ADJUST_BRIGHTNESS_SCREEN) {
    brightness_screen_init();
    update_brightness();
    increase_brightness(curr_brightness);
 
  } else{
  GPU_ClearFramebuffers();
  }
  	 
  if(popup_opened){GPU_DrawFilledRectangle(BLACK,40,TOP_MARGIN,270,160);}
 
  
    }
}