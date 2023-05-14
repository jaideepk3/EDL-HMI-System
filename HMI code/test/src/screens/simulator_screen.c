
#include "../ui.h"
#include "simulator_screen.h"
#include "distance_screen.h"
#include <string.h>
#include <stdlib.h>
#include "../main.h"
#define N 12
// int depths[15] ={ 552, 188, 92, 372, 545, 74, 129, 351, 301, 184, 308, 586, 269, 478, 294};
int Y1 = (GPU_Y-BOTTOM_OFFSET);
int Y2  = GPU_Y-BOTTOM_OFFSET;

//scale depth to display on UI 
// 1 pixel height(depth) cm = 5 real cm
int16_t scaled_depth(int16_t depth){
    if(depth>=180)return 180;
    return depth;
}

//draw simulator screen UI 
void simulator_screen_init(int depths[],int end){

    bottomNavigation("Rebar Depth Simulation", GREEN,1);
    GPU_DrawFilledRectangle(LAVENDER,0,GPU_Y-BOTTOM_OFFSET,GPU_X-1,3);
    int time = 0;
    char* status = "None";

   if(end>=Q_SIZE)end=Q_SIZE-1;
    int16_t height;

    //draw depth array in form of bars on UI
     for(int i=X_START;i<=(GPU_X-X_START);i+=X_STEP){
        if(time>=0){
             height= scaled_depth(depths[time]);
            if(depths[time]>=0 && depths[time]<50){
            status = "Warning" ;
             DrawVerticalRectangle(BG_COLOR,i-BAR_HALF_WIDTH,GPU_Y-BOTTOM_OFFSET,BAR_HALF_WIDTH*2+2,200);
            DrawVerticalRectangle(GREEN,i-BAR_HALF_WIDTH,GPU_Y-BOTTOM_OFFSET,BAR_HALF_WIDTH*2,height);
}
            else if(depths[time]>=50){
                status ="Detected";
                DrawVerticalRectangle(BG_COLOR,i-BAR_HALF_WIDTH,GPU_Y-BOTTOM_OFFSET,BAR_HALF_WIDTH*2+2,200);
                DrawVerticalRectangle(BLUE,i-BAR_HALF_WIDTH,GPU_Y-BOTTOM_OFFSET,BAR_HALF_WIDTH*2,height);
                GPU_DrawFilledCircle(RED,i,TOP_OFFSET+175-height+6,5);
            } 
        }
        GPU_DrawLine(PEACH,i,GPU_Y-BOTTOM_OFFSET+1,i,GPU_Y-BOTTOM_OFFSET-5);
        if(time ==end || end>=Q_SIZE-1){
                GPU_DrawLine(RED,i,GPU_Y-BOTTOM_OFFSET,i,GPU_Y-BOTTOM_OFFSET - height);
            }
        time+=1;
        
            
     }

    GPU_DrawText(RED, &fontDescription[1],1*fontDescription[1].width, 0, "cm", 2);

    DrawVerticalRectangle(LIGHT_BLUE,0,GPU_Y-BOTTOM_OFFSET-1,SCALE_END,180);
    int counter=0;
    //draw scales on Y-axis
    for(int j=Y_START;j>TOP_OFFSET+10;j-=Y_STEP){
        counter+=1;
        GPU_DrawLine(YELLOW,SCALE_END,j,SCALE_END+counter&1?11:7,j);
     } 
     GPU_DrawLine(RED,SCALE_END+10,Y1,320,Y1);
     GPU_DrawLine(RED,SCALE_END+10,Y2,320,Y2);

return ;
}



