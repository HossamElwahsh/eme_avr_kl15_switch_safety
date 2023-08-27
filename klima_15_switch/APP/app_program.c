/*
 * app_program.c
 *
 * Created: 8/26/2023 3:29:07 PM
 *  Author: Team GUCALEX
 */
#include "app_interface.h"

#include "lcd_interface.h"
#include "Timers.h"

#include "Led.h"

static void app_switch_state();

typedef enum
{
    CAR_OFF = 0 ,
    CAR_READY   ,
    CAR_ON      ,
    CAR_STATE_TOTAL
}en_app_state_t;

/* initial car state */
en_app_state_t en_gs_app_state = CAR_OFF;

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

    /* App super-loop */
    while (TRUE)
    {
        /* Check Switch */

    }
}

static void app_switch_state(en_app_state_t en_a_app_state)
{

}