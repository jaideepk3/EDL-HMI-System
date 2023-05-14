#ifndef BRIGHTNESS_H
#define BRIGHTNESS_H
#include <stdint.h>

#define BARWIDTH 40 
#define BARHEIGHT 15
#define RADIUS BARHEIGHT/2
#define BAROFFSET 60
void brightness_screen_init();
float read_brightness();
void bar_init();
void update_brightness();
void increase_brightness(int brightness);
#endif 