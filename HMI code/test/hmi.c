#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "src/interface.h"
#include "src/main.h"
#include "src/ui.h"
#define LM35_PIN 27

int main()
{
    stdio_init_all();
    InterfaceSetup();//buttons related initialization
    GPU_Init();//LCD related initialization
    DoMainLoop();//while loop 
    return 0;
}