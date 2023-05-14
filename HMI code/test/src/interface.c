#include "interface.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include "./screens/popup.h"
#include "ili9341.h"
#include "./screens/simulator_screen.h"
#include "ui.h"
#include<stdint.h>
#include <string.h> 
#include <stdlib.h>
#include "pico/time.h"

// define GPIO pin values used for buttons
#define HOME_KEY_PIN 3
#define START_KEY_PIN 4
#define LEFT_KEY_PIN 0
#define RIGHT_KEY_PIN 1
#define INFO_KEY_PIN 5
#define SELECT_KEY_PIN 2
 
static uint32_t startTime = 0;
Screen list[] = {DISTANCE_SCREEN,SIMULATION_SCREEN,PARAMS_SCREEN,ADJUST_BRIGHTNESS_SCREEN};


void Interrup_callback(uint gpio, uint32_t events) {
	  
    int here = time_us_32(); 
	//Key debouncing 
	if(here-lastDetectedPress>1e6){
		
	if(gpio==LEFT_KEY_PIN){
		 GPU_ClearFramebuffers();
			if (gpio==LEFT_KEY_PIN && !popup_opened)
	{
		if(gpio==LEFT_KEY_PIN) currScreen = list[(currScreen-1+NUM_SCREENS)%NUM_SCREENS];
		else{
		currScreen = list[(currScreen+1+NUM_SCREENS)%NUM_SCREENS];
		}
		busy_wait_ms(100);
	}
	else if(gpio==LEFT_KEY_PIN &&  popup_opened){
		clearPopup();
		if(currPopupPage==0)pg2();
		else pg1();
	}
	 

	}else if(gpio==RIGHT_KEY_PIN){
		GPU_ClearFramebuffers();
		if ( !popup_opened)
		{
		
	currScreen = list[(currScreen+1+NUM_SCREENS)%NUM_SCREENS];
		busy_wait_ms(100);
		}
	else if(  popup_opened  )
	{	clearPopup();
		if(currPopupPage==0)pg2();
		else pg1();
		
	}
	 
	}else if(gpio==SELECT_KEY_PIN){
 
			 presses=SELECT_KEY_PIN;
		   if(currScreen==SIMULATION_SCREEN){
			pauseSimulation = true^pauseSimulation;
		   }else if(currScreen == DISTANCE_SCREEN){
			if(NUM_SCREENS==3)NUM_SCREENS = 4;
			else NUM_SCREENS=3;
		   } 
 
	}
 
	else if(gpio==HOME_KEY_PIN){
		presses = HOME_KEY_PIN;
			 	if(popup_opened){
			
		close_popup("Press 4 to Escape/go to Home");
		popup_opened=false;
		}else{
			if(currScreen!=HOMESCREEN) GPU_ClearFramebuffers();
			currScreen = HOMESCREEN;
		}
			
 
	}
	
		lastDetectedPress=time_us_32();
	}

}

  
void InterfaceSetup()
{
	startTime = IF_GetCurrentTime();
	ili9341_init_SPI();
	ili9341_init_display();
	ili9341_init_drawing();

//set interrupts for all buttons on edge rise and fall

gpio_set_irq_enabled_with_callback(LEFT_KEY_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &Interrup_callback);
gpio_set_irq_enabled(RIGHT_KEY_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
gpio_set_irq_enabled(SELECT_KEY_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
gpio_set_irq_enabled(START_KEY_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
gpio_set_irq_enabled(INFO_KEY_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
gpio_set_irq_enabled(HOME_KEY_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
 
 
}

uint32_t IF_GetCurrentTime()
{
	return to_us_since_boot(get_absolute_time());
}


void IF_DrawScreen(uint8_t * _framebuffer, size_t _framebufferSize)
{
	ili9341_write_buffer(_framebuffer, _framebufferSize);
}

static uint32_t last_seed = 0xdeadb0d1;

uint32_t IF_Random()
{
    uint32_t now = IF_GetCurrentTime();
    uint32_t result = ((uint32_t)(142*now * now + 13*now + 203) >> 4)+last_seed;
    last_seed = result;
    return result;
}

//register left keyboard events
void  Keyboard(void)
{ 
  
 busy_wait_ms(5);

	if(gpio_get(INFO_KEY_PIN)==1){
	
			popup_opened^=true;
		if(popup_opened){
			 open_popup("Press 2 to navigate Left");
		 
		} 
		busy_wait_ms(100);
	 
	}
	if (gpio_get(START_KEY_PIN) == 1)
		{
	 
		//add suitable code
		busy_wait_ms(300);
 
		}
 
return ;
	
 }
