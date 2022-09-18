/*
 * File:   buzzer.c
 * Author: ChandraShekhar V
 *
 * Created on September 11, 2022, 10:11 AM
 */


#include "xc.h"
#include "app.h"
#include "LeakTester_Mainboard1V0.h"

void buzzer_Tasks( void )
{
    BUZZER_Clear();
    vTaskDelay(500 / portTICK_PERIOD_MS);
    BUZZER_Set();
    vTaskDelay(500 / portTICK_PERIOD_MS);
}
