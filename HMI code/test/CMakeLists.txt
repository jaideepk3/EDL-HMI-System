# Set minimum required version of CMake
cmake_minimum_required(VERSION 3.12)

# Include build functions from Pico SDK
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Set name of project (as PROJECT_NAME) and C/C++ standards
project(HMI C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Creates a pico-sdk subdirectory in our project for the libraries
pico_sdk_init()

# Tell CMake where to find the executable source file
add_executable(${PROJECT_NAME} 
hmi.c
src/ili9341.c
src/ui.c
src/interface.c
src/main.c
src/menu.c
src/screens/distance_screen.c
src/screens/simulator_screen.c
src/temp.c
src/distance.c
src/simulation.c
src/brightness.c
src/screens/popup.c

)
# Create map/bin/hex/uf2 files
pico_add_extra_outputs(${PROJECT_NAME})
# Link to pico_stdlib (gpio, time, etc. functions)
target_link_libraries(${PROJECT_NAME}
    pico_stdlib hardware_adc hardware_spi
)
# Enable usb output, disable uart output
pico_enable_stdio_usb(${PROJECT_NAME}   1)
pico_enable_stdio_uart(${PROJECT_NAME}   0)
 
 