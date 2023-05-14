#include "ui.h"
#include "fonts.h"
#include <string.h>
#include <math.h>
#include "pico/time.h"
#include <stdio.h>
#include "interface.h"
//buffer to store pixel values
 uint16_t _framebuffer[GPU_X*GPU_Y];  // GPU VRAM (16bits per color)


void GPU_Init()
{  GPU_ClearFramebuffers();
}
 

void GPU_ClearFramebuffers()
{
    memset(_framebuffer, 0, sizeof(_framebuffer));
}



#define SHOW_FPS

#ifdef SHOW_FPS
uint32_t oldTime = 0;
#endif

uint32_t getMinutes(){
    uint32_t nowTime = IF_GetCurrentTime();
    uint32_t currentTime = to_ms_since_boot(nowTime)/1000;
        uint8_t seconds = ((currentTime/10%60)*10)%60;
     uint32_t minutes= currentTime/60;
     return minutes;
}

//update LCD screen pixel values by sending buffer data
void GPU_Render()
{ 
#ifdef SHOW_FPS
	char t[25] = "";
	uint16_t len = 0;
	uint32_t nowTime = IF_GetCurrentTime();

#define COLOR_INFO RGB(217,207,38)
	if (oldTime != nowTime)
	{   
		uint16_t fps = (float)ONE_SECOND / (float)(nowTime-oldTime);
        uint32_t currentTime = to_ms_since_boot(nowTime)/1000;
        uint8_t seconds = ((currentTime/10%60)*10)%60;
        uint32_t minutes= currentTime/60;
		len = sprintf(t, "On Time = %d min %d sec", minutes, seconds);
   
        GPU_DrawFilledRectangle(BG_COLOR,GPU_X-len*fontDescription[1].width - 10,0,
        len*fontDescription[1].width+30,fontDescription[1].height+1);
		GPU_DrawText(COLOR_INFO, &fontDescription[1], GPU_X-len*fontDescription[1].width, 0, t, len);
	}

	oldTime = nowTime;

#endif
    IF_DrawScreen((uint8_t *)_framebuffer, sizeof(_framebuffer));
}

///////////////////////////////////////////////

void GPU_DrawPixel(GPU_Color color, uint16_t x, uint16_t y)
{
    if (x >= GPU_X || y >= GPU_Y)
        return;
    uint16_t * pix = &_framebuffer[(GPU_X-x-1)*GPU_Y+y];
    (*pix) = (uint16_t) color;
}

void GPU_DrawLine(GPU_Color color, int16_t x0, int16_t y0, int16_t x1, int16_t y1)
{
    // Bresenhams line algorithm
    x0 = (x0 >= GPU_X) ? GPU_X-1 : x0;
    x1 = (x1 >= GPU_X) ? GPU_X-1 : x1;
    y0 = (y0 >= GPU_Y) ? GPU_Y-1 : y0;
    y1 = (y1 >= GPU_Y) ? GPU_Y-1 : y1;
    int16_t dx =  x1>x0 ? x1-x0 : x0-x1;
    int16_t sx = x0<x1 ? 1 : -1;
    int16_t dy = y1 > y0 ? -(y1-y0): y1-y0;
    int16_t sy = y0<y1 ? 1 : -1;
    int16_t err = dx+dy;  /* error value e_xy */
    while (1)   /* loop */
    {
        GPU_DrawPixel(color, x0, y0);
        if (x0 == x1 && y0 == y1) 
            break;
        int16_t e2 = 2*err;
        if (e2 >= dy) /* e_xy+e_x > 0 */
        {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) /* e_xy+e_y < 0 */
        {
            err += dx;
            y0 += sy;
        }
    }
}

void GPU_DrawLetter(GPU_Color color, const FontDescription * fontDescription, int16_t x, int16_t y, char letter)
{
    for (uint16_t i=0; i<fontDescription->height; i++)
    {
        uint16_t current_pic = fontDescription->fontArray[(letter-32)*fontDescription->height+i];
        for (uint8_t j=0; j<fontDescription->width; j++)
        {
            if (current_pic & (1<<(16-j)))
                GPU_DrawPixel(color, x+j, y+i);
        }
    }
}

void GPU_DrawText(GPU_Color color, const FontDescription * fontDescription, int16_t x, int16_t y, const char * text, uint16_t len)
{
    for (uint16_t i=0; i<len; i++)
    {
        GPU_DrawLetter(color, fontDescription, x+i*fontDescription->width, y, text[i]);
    }
}

void GPU_DrawEmptyRectangle(GPU_Color color, int16_t x, int16_t y, int16_t width, int16_t height)
{
    GPU_DrawLine(color, x, y, x+width, y);
    GPU_DrawLine(color, x, y+height, x+width, y+height);
    GPU_DrawLine(color, x, y, x, y+height);
    GPU_DrawLine(color, x+width, y, x+width, y+height);
}

void GPU_DrawFilledRectangle(GPU_Color color, int16_t x, int16_t y, int16_t width, int16_t height)
{
    for (int16_t i=0; i<width; i++)
    {
        for (int16_t j=0; j<height; j++)
        {
            GPU_DrawPixel(color, x+i, y+j);
        }    
    }
}
void DrawSmoothBar(GPU_Color color, int16_t x, int16_t y, int16_t width, int16_t height)
{
    int radius = height/2;
    GPU_DrawFilledRectangle(color,x+radius,y,width,height);
    GPU_DrawFilledCircle(color,x+radius,y+radius,radius);
    GPU_DrawFilledCircle(color,x+width+radius,y+radius,radius);
    return;
}
 
void DrawVerticalRectangle(GPU_Color color, int16_t x, int16_t y, int16_t width, int16_t height)
{
    for (int16_t i=0; i<width; i++)
    {
        for (int16_t j=0; j<height; j++)
        {
            GPU_DrawPixel(color, x+i, y-j);
        }    
    }
}

void DrawFilledTriangle(GPU_Color color, int16_t x, int16_t y, int16_t side,int16_t height,char* dir){
    if(dir=="right"){
        for(int i=0;i<height;i++){
            for(int j=side/2-i;j>=0;j--){
                GPU_DrawPixel(color,x+i,y-j);
            }
        }
        for(int i=0;i<height;i++){
            for(int j=side/2-i;j>=0;j--){
                GPU_DrawPixel(color,x+i,y+j);
            }
        }
    }else if(dir=="left"){
        for(int i=0;i<height;i++){
            for(int j=side/2-i;j>=0;j--){
                GPU_DrawPixel(color,x-i,y-j);
            }
        }
        for(int i=0;i<height;i++){
            for(int j=side/2-i;j>=0;j--){
                GPU_DrawPixel(color,x-i,y+j);
            }
        }
    } 
    }


void LeftHalfFilledCircle(GPU_Color color, int16_t x, int16_t y, int16_t radius)
{
    uint16_t xd = 0, yd = radius;
    int16_t d = 3 - 2 * radius;
    int16_t mxxd = x-xd > 0 ? x-xd : 0;
    int16_t myyd = y-yd > 0 ? y-yd : 0;
    int16_t mxyd = x-yd > 0 ? x-yd : 0;
    int16_t myxd = y-xd > 0 ? y-xd : 0;
    GPU_DrawLine(color, mxxd, myyd, x, myyd);
    GPU_DrawLine(color, mxxd, y+yd, x, y+yd);
    GPU_DrawLine(color, mxyd, myxd, x, myxd);
    GPU_DrawLine(color, mxyd, y+xd, x, y+xd);
    while (yd >= xd)
    {
        xd++;
        if (d > 0)
        {
            yd--;
            d = d + 4 * (xd - yd) + 10;
        }
        else
            d = d + 4 * xd + 6;
        
        mxxd = x-xd > 0 ? x-xd : 0;
        myyd = y-yd > 0 ? y-yd : 0;
        mxyd = x-yd > 0 ? x-yd : 0;
        myxd = y-xd > 0 ? y-xd : 0;
        GPU_DrawLine(color, x-xd, y-yd, x , y-yd);
        GPU_DrawLine(color, x-xd, y+yd, x , y+yd);
        GPU_DrawLine(color, x-yd, y-xd, x , y-xd);
        GPU_DrawLine(color, x-yd, y+xd, x , y+xd);
    }
}
void RightHalfFilledCircle(GPU_Color color, int16_t x, int16_t y, int16_t radius)
{
uint16_t xd = 0, yd = radius;
    int16_t d = 3 - 2 * radius;
    int16_t mxxd = x-xd > 0 ? x-xd : 0;
    int16_t myyd = y-yd > 0 ? y-yd : 0;
    int16_t mxyd = x-yd > 0 ? x-yd : 0;
    int16_t myxd = y-xd > 0 ? y-xd : 0;
    GPU_DrawLine(color, x, myyd, x+xd, myyd);
    GPU_DrawLine(color, x, y+yd, x+xd, y+yd);
    GPU_DrawLine(color, x, myxd, x+yd, myxd);
    GPU_DrawLine(color, x, y+xd, x+yd, y+xd);
    while (yd >= xd)
    {
        xd++;
        if (d > 0)
        {
            yd--;
            d = d + 4 * (xd - yd) + 10;
        }
        else
            d = d + 4 * xd + 6;
        
        mxxd = x-xd > 0 ? x-xd : 0;
        myyd = y-yd > 0 ? y-yd : 0;
        mxyd = x-yd > 0 ? x-yd : 0;
        myxd = y-xd > 0 ? y-xd : 0;
        GPU_DrawLine(color, x, y-yd, x+xd, y-yd);
        GPU_DrawLine(color, x, y+yd, x+xd, y+yd);
        GPU_DrawLine(color, x, y-xd, x+yd, y-xd);
        GPU_DrawLine(color, x, y+xd, x+yd, y+xd);
    }
}
void GPU_DrawFilledCircle(GPU_Color color, int16_t x, int16_t y, int16_t radius)
{
    uint16_t xd = 0, yd = radius;
    int16_t d = 3 - 2 * radius;
    int16_t mxxd = x-xd > 0 ? x-xd : 0;
    int16_t myyd = y-yd > 0 ? y-yd : 0;
    int16_t mxyd = x-yd > 0 ? x-yd : 0;
    int16_t myxd = y-xd > 0 ? y-xd : 0;
    GPU_DrawLine(color, mxxd, myyd, x+xd, myyd);
    GPU_DrawLine(color, mxxd, y+yd, x+xd, y+yd);
    GPU_DrawLine(color, mxyd, myxd, x+yd, myxd);
    GPU_DrawLine(color, mxyd, y+xd, x+yd, y+xd);
    while (yd >= xd)
    {
        xd++;
        if (d > 0)
        {
            yd--;
            d = d + 4 * (xd - yd) + 10;
        }
        else
            d = d + 4 * xd + 6;
        
        mxxd = x-xd > 0 ? x-xd : 0;
        myyd = y-yd > 0 ? y-yd : 0;
        mxyd = x-yd > 0 ? x-yd : 0;
        myxd = y-xd > 0 ? y-xd : 0;
        GPU_DrawLine(color, x-xd, y-yd, x+xd, y-yd);
        GPU_DrawLine(color, x-xd, y+yd, x+xd, y+yd);
        GPU_DrawLine(color, x-yd, y-xd, x+yd, y-xd);
        GPU_DrawLine(color, x-yd, y+xd, x+yd, y+xd);
    }
}
//thermometer image 
void display_png(){
    for(int i=65;i<125;i++){
        for(int j=35;j<95;j++){
          uint32_t pix = temp[(i-65)*60+(j-35)];

            GPU_DrawPixel(pix,j,i);
        }
    }
}

void cross_sign(){
    for(int i=0;i<30;i++){
         
        for(int j=0;j<30;j++){
          uint32_t pix = cross[(i)*30+(j)];

            GPU_DrawPixel(pix,i+235,j+TOP_MARGIN+5);
        }
    }
    return;
}
 