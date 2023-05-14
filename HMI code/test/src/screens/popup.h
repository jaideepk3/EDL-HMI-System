#ifndef POPUP_H 
#define POPUP_H
#include <stdbool.h>
extern bool popup_opened ;
void close_popup(char* title);
void open_popup(char* title);
void pg1();
void pg2();
void clearPopup();
#endif