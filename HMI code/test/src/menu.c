#include "main.h"
#include "interface.h"
#include "ui.h"
#include "menu.h"
#include <math.h>
#include "./screens/distance_screen.h"
MainMemory mainMemory;

typedef struct {
    uint8_t _choiceStart;
    uint8_t _choiceCurrent;
    uint8_t _choiceEnd;
    uint8_t screenLines;
} MainScreenMemory;

static MainScreenMemory * const memory = (MainScreenMemory*)(&mainMemory.sharedMemory.memblocks[0]);
 
#define NUM_TICKS 10

static const FontDescription * f_big = &fontDescription[2];
static const FontDescription * f_huge = &fontDescription[3];

static uint32_t CalculateTick()
{
    return IF_GetCurrentTime()/(ONE_SECOND/NUM_TICKS);
}

  