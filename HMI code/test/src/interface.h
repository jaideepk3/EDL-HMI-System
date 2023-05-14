#ifndef INTERFACE_H
#define INTERFACE_H
#include <stdio.h>
#include "main.h"
#include <stdint.h>
#define ONE_SECOND (1000*1000)


void InterfaceSetup();
uint32_t IF_GetCurrentTime();
 
void Keyboard(void);
void IF_DrawScreen(uint8_t *_framebuffer, size_t _framebufferSize);
#endif