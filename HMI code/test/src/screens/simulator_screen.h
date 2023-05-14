#ifndef SIMULATOR_SCREEN_H
#define SIMULATOR_SCREEN_H
#include <stdint.h>

// #define BOTTOM_OFFSET (ARROW_Y_OFFSET+35)
#define BOTTOM_OFFSET 35
#define TOP_OFFSET 15
#define SCALE_END 8
#define X_START 20
#define X_STEP 25
#define Y_START (GPU_Y- BOTTOM_OFFSET)
#define Y_STEP 5
#define BAR_HALF_WIDTH 7
#define SCALE 180

extern int Y1;
extern int Y2;
// 1 depth cm = 5 real cm
void simulator_screen_init(int* depths,int end);

#endif