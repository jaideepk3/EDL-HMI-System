
#include "../ui.h"
#include "distance_screen.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../distance.h"
#include "popup.h"
#include "../main.h"
#include "pico/time.h"
bool popup_opened =false;
//instructions to be displayed on popup screen
char * NavigationInfo []= {"Press Start to On/Off device","Press <- (1) to Navigate Left",
"Press -> (2) to Navigate Right","Press HOME (4) to return Home","Press OK (3) to PAUSE Simulation",
"Developed by TUES-25 EDL Group"};

//draw popup UI excluding instructions 
void display_info(){
    GPU_DrawFilledRectangle(BG_COLOR,40,TOP_MARGIN,270,160);
    char * title = "Press HOME/ESC";
    GPU_DrawText(GREEN,&fontDescription[1],125,TOP_MARGIN+10,title,strlen(title));
     title = "to close";
   GPU_DrawText(GREEN,&fontDescription[1],135,TOP_MARGIN+20,title,strlen(title));

    char * head = "INFO";
    GPU_DrawText(FLUORESCENT_ORANGE,&fontDescription[3],50,TOP_MARGIN+22,head,strlen(head));
    cross_sign();
    GPU_Render();

}
//clear popup area 
void clearPopup(){
    GPU_DrawFilledRectangle(BG_COLOR, 40,TOP_MARGIN,270,160-55);
    GPU_Render();
}

//popup screen 1 UI 
void pg1(){
    display_info();
    currPopupPage=0;
    for(int i=0;i<3;i++){
        char* info = NavigationInfo[i];
         GPU_DrawText(YELLOW,&fontDescription[1],45,TOP_MARGIN+65+i*25,info,strlen(info));
    }
    GPU_Render();
    return;
}

//popup screen 2 UI
void pg2(){
    display_info();
    currPopupPage=1;
    for(int i=3;i<6;i++){
        char* info = NavigationInfo[i];
         GPU_DrawText(i==5?WHITE:YELLOW,&fontDescription[1],45,TOP_MARGIN+65+(i-3)*25,info,strlen(info));
    }
    GPU_Render();
    return;
}

//default screen1 UI
void open_popup(char* title){
    pg1();
   return ;
}

//clear screen close popup
void close_popup(char* title){
    GPU_ClearFramebuffers();
   return ;
}