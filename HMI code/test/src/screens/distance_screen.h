#ifndef DISTANCE_SCREEN_H
#define DISTANCE_SCREEN_H
#include <stdint.h>
#define ARROW_Y_OFFSET 15
#define ARROW_X_SIZE 25
#define ARROW_Y_SIZE 10 
#define TRIANGLE_SIDE 20 
#define TRIANGLE_HEIGHT 25
#define ARROW_X_OFFSET 15 
#include "../ui.h"

void value_box(char* value);
void draw_arrow(char* dir);
void distance_screen_init();
void bottomNavigation(char*title,GPU_Color color,int8_t size);
void generic_box(char* title);
#endif