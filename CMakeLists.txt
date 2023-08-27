cmake_minimum_required(VERSION 3.26)
project(klima_15_switch C)

set(CMAKE_C_STANDARD 11)

include_directories(klima_15_switch/APP)
include_directories(klima_15_switch/COMMON)
include_directories(klima_15_switch/MCAL/gpio)
include_directories(klima_15_switch/HAL/lcd)
include_directories(klima_15_switch/HAL/led)
include_directories(klima_15_switch/MCAL/timer)
include_directories("C:/WinAVR-20100110/avr/include/")

add_executable(klima_15_switch
        klima_15_switch/APP/app_interface.h
        klima_15_switch/APP/app_program.c
        klima_15_switch/COMMON/bit_math.h
        klima_15_switch/COMMON/interrupts.h
        klima_15_switch/COMMON/mem_map.h
        klima_15_switch/COMMON/std.h
        klima_15_switch/MCAL/gpio/gpio.c
        klima_15_switch/MCAL/gpio/gpio.h
        klima_15_switch/MCAL/gpio/gpio_private.h
        klima_15_switch/MCAL/timer/Timers.c
        klima_15_switch/MCAL/timer/Timers.h
        klima_15_switch/main.c
        klima_15_switch/MCAL/adc/adc_program.c
        klima_15_switch/MCAL/adc/adc_private.h
        klima_15_switch/APP/app_config.h
        "C:/WinAVR-20100110/avr/include/util/delay.h"
        klima_15_switch/HAL/lcd/lcd_program.c
        klima_15_switch/HAL/lcd/lcd_interface.h
        klima_15_switch/HAL/lcd/lcd_private.h
        klima_15_switch/HAL/lcd/lcd_config.h
        klima_15_switch/HAL/led/Led.c

)
