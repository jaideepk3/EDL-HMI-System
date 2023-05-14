
#include "../ui.h"
#include "distance_screen.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../distance.h"

//draw navigation arrows on UI
void draw_arrow(char* dir){
    GPU_DrawFilledRectangle(YELLOW,
        dir=="right"? (GPU_X- ARROW_X_OFFSET-TRIANGLE_HEIGHT-ARROW_X_SIZE ): (ARROW_X_OFFSET+TRIANGLE_HEIGHT) ,
        GPU_Y - ARROW_Y_OFFSET-ARROW_Y_SIZE,
        ARROW_X_SIZE,
        ARROW_Y_SIZE);
    DrawFilledTriangle(YELLOW,dir=="right"?(GPU_X - ARROW_X_OFFSET - TRIANGLE_HEIGHT):(ARROW_X_OFFSET+TRIANGLE_HEIGHT),
    GPU_Y - ARROW_Y_OFFSET - ARROW_Y_SIZE/2,
    TRIANGLE_SIDE,
    TRIANGLE_HEIGHT,
    dir
    );
    return;

    
}
 
void generic_box(char* title){
   
    GPU_DrawFilledRectangle(ORANGE,50,TOP_MARGIN,220,160);
    GPU_DrawText(BLACK,&fontDescription[2],55,TOP_MARGIN+60,title,strlen(title));
   return ;
}

void value_box(char* value){
    GPU_DrawFilledRectangle(BLACK,110,110,110,50);
  
    GPU_DrawText(YELLOW,&fontDescription[2],117,130,value,strlen(value));
    return ;
}

//draw bottom UI 
void bottomNavigation(char*title,GPU_Color color,int8_t size){
    draw_arrow("right");
    draw_arrow("left");
    if(strlen(title)){
        GPU_DrawText(color,&fontDescription[size],75,GPU_Y - ARROW_Y_OFFSET-5,title,strlen(title));
    }
    return ;
}

//draw complete UI for distance screen
void distance_screen_init(){
    bottomNavigation("",YELLOW,2);
    generic_box("Distance from wall");
    update_distance();
    return;
}



