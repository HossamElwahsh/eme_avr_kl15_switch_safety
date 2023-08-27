/*
 * app_program.c
 *
 * Created: 8/26/2023 3:29:07 PM
 *  Author: Team GUCALEX
 */
#include "app_interface.h"
#include "app_config.h"

#include "lcd_interface.h"
#include "KL_switch.h"
#include "ldr.h"
#include "Timers.h"

#include "Led.h"


typedef enum
{
    INIT_UI = 0 ,
    CAR_OFF     ,
    CAR_READY   ,
    CAR_ON      ,
    CAR_STATE_TOTAL
}en_app_state_t;

static void app_switch_state(en_app_state_t en_a_app_state);
static void app_key_changed(en_read_states_t en_l_kl_state);

static boolean bool_gs_is_night = FALSE;

/* initial car state */
en_app_state_t en_gs_app_state = CAR_OFF;

void app_init()
{
    /* Init LCD */
    LCD_init();

    /* Init LDR */
    ldr_init();

    /* Init Timer */
    Timer1_Init(TIMER1_NORMAL_MODE, TIMER1_SCALER_256);
    Timer1_OVF_InterruptEnable();

    /* Init KL_Switch */
    KL_Switch_init();

    /* Init Interior LED */
    Led_Init(APP_INTERIOR_LIGHT_ARGS);

    /* Init Front LEDs */
    Led_Init(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
    Led_Init(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
}

void app_start()
{
    /* Switch app to initial state - CAR OFF */
    app_switch_state(INIT_UI);

    en_read_states_t en_l_kl_state;

    /* Read LDR */
    ldr_read();

    /* Update is night flag */
    bool_gs_is_night = LDR_40_PERCENT < LDR_VALUE;

    /* App super-loop */
    while (TRUE)
    {
        /* Read KL15 Switch State */
        en_l_kl_state = KL_Switch_Read_state();

        /* Check Switch */
        switch (en_gs_app_state)
        {
            case INIT_UI:
            {
                /* Init APP LCD UI */
                app_switch_state(CAR_OFF);
                break;
            }
            case CAR_OFF:
            {
                /* Check key state */
                if(OFF != en_l_kl_state)
                {
                    app_key_changed(en_l_kl_state);
                }
                else
                {
                    /* Do nothing */
                }

                break;
            }
            case CAR_READY:
                /* Check timer */

                /* Check key state */
                if(Ready != en_l_kl_state)
                {
                    app_key_changed(en_l_kl_state);
                }
                else
                {
                    /* Do nothing */
                }
                break;

            case CAR_ON:
            {
                /* Check key state */
                if(ON != en_l_kl_state)
                {
                    app_key_changed(en_l_kl_state);
                }
                else
                {
                    /* Do nothing */
                }
                break;
            }
            case CAR_STATE_TOTAL:
            {
                /* Reset state to OFF */
                app_switch_state(CAR_OFF);
                break;
            }
            default:
            {
                /* Reset state to OFF */
                app_switch_state(CAR_OFF);
                break;
            }
        }
    }
}

static void app_key_changed(en_read_states_t en_l_kl_state)
{
    switch (en_l_kl_state)
    {
        case OFF:
        {
            app_switch_state(CAR_OFF);
            break;
        }
        case Ready:
        {
            app_switch_state(CAR_READY);
            break;
        }
        case ON:
        {
            app_switch_state(CAR_ON);
            break;
        }
    }
}

static void app_switch_state(en_app_state_t en_a_app_state)
{
    switch (en_a_app_state)
    {
        case INIT_UI:
        {
            /* Init LCD UI */
            LCD_sendString(APP_STR_TITLE);
            break;
        }
        case CAR_OFF:
        {
            /* Turn off all car LEDs */
            Led_TurnOff(APP_INTERIOR_LIGHT_ARGS);
            Led_TurnOff(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
            Led_TurnOff(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);

            /* Update UI */
            LCD_setCursor(LCD_LINE2, LCD_COL6);
            LCD_sendString(APP_STR_CAR_OFF);
            break;
        }
        case CAR_READY:
        {
            /* Turn on car interior light */
            Led_TurnOn(APP_INTERIOR_LIGHT_ARGS);

            /* Update UI */
            LCD_setCursor(LCD_LINE2, LCD_COL0);
            LCD_sendString("Please Start Motor");

            /* Start watchdog timer to prevent battery drain */

            break;
        }
        case CAR_ON:
        {
            /* Turn on car interior */
            Led_TurnOn(APP_INTERIOR_LIGHT_ARGS);

            /* Check day/night light */
            if(TRUE == bool_gs_is_night)
            {
                /* Night, turn on car front lights */
                Led_TurnOn(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
                Led_TurnOn(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
            }
            else
            {
                /* Day, turn off car front lights */
                Led_TurnOff(APP_CAR_FRONT_LEFT_LIGHT_ARGS);
                Led_TurnOff(APP_CAR_FRONT_RIGHT_LIGHT_ARGS);
            }
            break;
        }
        case CAR_STATE_TOTAL:
        {
            /* Do Nothing, app super-loop will handle */
            break;
        }
        default:
        {
            /* Do Nothing, app super-loop will handle */
            break;
        }
    }

    en_gs_app_state = en_a_app_state;
}