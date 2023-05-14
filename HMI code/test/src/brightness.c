
#include "ui.h"
 #include "main.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include  "brightness.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "./screens/distance_screen.h"
#include "pico/time.h"
#define BB_PIN 28 //pin to adjust screen brightness using potentiometer

void bar_init(){
    adc_init();
    adc_gpio_init(BB_PIN);
    adc_select_input(2); //select ADC 2 to read value
}

float read_brightness(){
   
    busy_wait_ms(5);
    float val = 100*((float)adc_read())/4095.0; //convert adc reading to brightness value
    return val;
}

//draw ui for brightness screen
void brightness_screen_init(){
    bottomNavigation("",YELLOW,1);
    char value[25]="Adjust Brightness";
    GPU_DrawFilledRectangle(BLACK,60,190,100,60);
    GPU_DrawText(GREEN,&fontDescription[2],60,198,value,strlen(value));
}

//increase brightness value on UI 
void increase_brightness(int brightness){
   
     int bars = (brightness)/25;
    if(brightness>=95)bars=4;
     int rem = brightness%25;
    int offset = bars*BAROFFSET;
   
     for(int i=0;i<bars;i++){
     DrawSmoothBar(PURPLE,55+BAROFFSET*i,100,BARWIDTH,BARHEIGHT);
  } 

  if(bars==4){GPU_Render();
  return;}
 
      if(rem<=5 && rem>0 && bars<=3){
      LeftHalfFilledCircle(bars==0?RED:PURPLE,offset+RADIUS+55,107,7);
    }
    
    else{
         LeftHalfFilledCircle(bars==0?RED:PURPLE,offset+RADIUS+55,107,7);
        GPU_DrawFilledRectangle(bars==0?RED:PURPLE,55+offset+7,100,(rem-5)*2,BARHEIGHT);
    }
    return;
}

//decrease brightness value on UI 
void decrease_brightness(int brightness){

     int bars = (brightness)/25;
    if(brightness>95)return;
    int rem = brightness%25;
     int offset =bars*BAROFFSET   ;
  
       if(bars==0 || brightness==25){

          if(rem<=5 && rem>0 ){
         LeftHalfFilledCircle(RED,offset+RADIUS+55,107,7);
    }else if(rem<20){ 
          LeftHalfFilledCircle(RED,offset+RADIUS+55,107,7);
          GPU_DrawFilledRectangle(RED,55+offset+7,100,(rem-5)*2,BARHEIGHT);}  
       }
     for(int i=bars+1;i<4;i++){
     GPU_DrawFilledRectangle(BG_COLOR,55+BAROFFSET*i,100,BARWIDTH,BARHEIGHT);
  }  

  GPU_DrawFilledRectangle(BG_COLOR,55+offset+(rem)*2,100,200,BARHEIGHT);

  return;
}

//update UI  based on brightness value
void update_brightness(){
 
    char value0[20];
    float val = read_brightness();
 
    snprintf(value0, sizeof(value0), " %d", (int)val);  
    GPU_DrawFilledRectangle(BLACK,110,45,200,35);
  
    GPU_DrawText(GREEN,&fontDescription[2],115,47,value0,strlen(value0));
    if(val>=20 && val<=25){DrawSmoothBar(RED,55,100,BARWIDTH,BARHEIGHT);
  GPU_DrawFilledRectangle(BG_COLOR,55+BAROFFSET,100,200,BARHEIGHT);
 }
    else if(val-curr_brightness>3)increase_brightness((int)val); //increase bar size
    else if(curr_brightness-val>3)decrease_brightness((int)val);  // decrease bar size
    
curr_brightness = val;
   return;
}