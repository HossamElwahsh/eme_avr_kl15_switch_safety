/*
 * app_program.c
 *
 * Created: 8/26/2023 3:29:07 PM
 *  Author: Team GUCALEX
 */
#include "app_interface.h"

#include "lcd_interface.h"
#include "Timers.h"

#include "led_interface.h"

void app_init()
{
    /* Init LCD */
    LCD_init();

    /* Init Timer */
    TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_STOP);

    /* Init LED */

}

void app_start()
{

}