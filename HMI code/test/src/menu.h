#ifndef MENU_H
#define MENU_H
#include<stdint.h>
typedef enum {
    DISTANCE_SCREEN = 0,
    SIMULATION_SCREEN = 1,
    PARAMS_SCREEN = 2,
    INFO_SCREEN   = 4,
    ADJUST_BRIGHTNESS_SCREEN = 3,
} Screen;
#define HOMESCREEN  DISTANCE_SCREEN

typedef struct {
    uint32_t memblocks[2*1024];
} SharedMemory;

typedef struct {
    SharedMemory sharedMemory;
    Screen current_screen;
	uint32_t _lastRenderedTime;
    uint32_t _lastRenderedTick;
} MainMemory;

extern MainMemory mainMemory;
#endif