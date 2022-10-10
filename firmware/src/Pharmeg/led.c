/*
 * File:   led.c
 * Author: ChandraShekhar V
 *
 * Created on September 10, 2022, 10:37 PM
 */


#include "xc.h"
#include "app.h"
#include "LeakTester_Mainboard1V0.h"
#include "rtc.h"

void led_D5_Tasks ( void )
{
    LED1_RED_Clear();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    LED1_RED_Set();
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    get_rtc();
}

void led_D6_Tasks ( void )
{
    LED2_RED_Clear();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    LED2_RED_Set();
    vTaskDelay(100 / portTICK_PERIOD_MS);
}