/*
 * CFile1.c
 *
 * Created: 8/27/2023 9:21:31 AM
 *  Author: A M
 */
#include "KL_switch.h"


en_klswitch_t KL_Switch_init(){
    en_adc_status_t ADC_status = adc_init();
    en_klswitch_t intial;

    if(ADC_STATUS_TOTAL <= ADC_status)
    {
        /* bad return value */
        intial = KLSWITCH_ERROR;
    }
    else
    {
        /* valid return */
        if(ADC_OK == ADC_status)
        {
            intial = KLSWITCH_OK;

        }
        else if (ADC_ERROR == ADC_status)
        {
            intial = KLSWITCH_ERROR;
        }
    }


}
en_read_states_t KL_Switch_Read_state(void){
    en_read_states_t state=OFF;

    adc_read(ADC_CH_1);
    if(uint16_g_last_reading[ADC_CH_1] < 430 )
    {
        state=OFF;
    }
    else if (uint16_g_last_reading[ADC_CH_1]>430 && uint16_g_last_reading[ADC_CH_1]<440){
        state=Ready;
    }
    else {
        state= ON;
    }
    return state;
}