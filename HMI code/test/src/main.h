#ifndef MAIN_H
#define MAIN_H
#include "menu.h"
#include <stdbool.h>
 extern int presses;
extern int lastDetectedPress ; 
extern Screen currScreen;
extern uint8_t currPopupPage ;
extern bool pauseSimulation;
extern float univ;
#define Q_SIZE 13 //rebar simulation queue size
extern int NUM_SCREENS ;
extern uint32_t curr_brightness ; 
void DoMainLoop();
  
#endif