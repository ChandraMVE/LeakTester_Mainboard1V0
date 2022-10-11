/*
 * File:   keypad.c
 * Author: ChandraShekhar V
 *
 * Created on Oct 10, 2022, 10:37 PM
 */


#include "keypad.h"

void InitKeypad(void)
{
    GPIO_PinOutputEnable(KEYROW0);
    GPIO_PinOutputEnable(KEYROW1);
    GPIO_PinOutputEnable(KEYROW2);
    GPIO_PinOutputEnable(KEYROW3);
    
    GPIO_PinInputEnable(KEYCOL0);
    GPIO_PinInputEnable(KEYCOL1);
    GPIO_PinInputEnable(KEYCOL2);
    GPIO_PinInputEnable(KEYCOL3);
    GPIO_PinInputEnable(KEYCOL4);
}

char keypad_scanner(void)  
{           
            GPIO_PinClear(KEYROW0);
            GPIO_PinSet(KEYROW1); 
            GPIO_PinSet(KEYROW2); 
            GPIO_PinSet(KEYROW3);    
            if (GPIO_PinRead(KEYCOL0) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL0)==0); return 'r'; }//right
            if (GPIO_PinRead(KEYCOL1) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL1)==0); return 'E'; }//enter
            if (GPIO_PinRead(KEYCOL2) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL2)==0); return 'd'; }//down
            if (GPIO_PinRead(KEYCOL3) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL3)==0); return 'n'; }//
            if (GPIO_PinRead(KEYCOL4) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL4)==0); return 'n'; }//
            
            GPIO_PinSet(KEYROW0);
            GPIO_PinClear(KEYROW1); 
            GPIO_PinSet(KEYROW2); 
            GPIO_PinSet(KEYROW3);  
            if (GPIO_PinRead(KEYCOL0) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL0)==0); return 'e'; }//esc
            if (GPIO_PinRead(KEYCOL1) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL1)==0); return 'm'; }//menu
            if (GPIO_PinRead(KEYCOL2) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL2)==0); return 's'; }//start/hold
            if (GPIO_PinRead(KEYCOL3) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL3)==0); return 'u'; }//up
            if (GPIO_PinRead(KEYCOL4) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL4)==0); return 'l'; }//left
            
            GPIO_PinSet(KEYROW0);
            GPIO_PinSet(KEYROW1); 
            GPIO_PinClear(KEYROW2); 
            GPIO_PinSet(KEYROW3);    
            if (GPIO_PinRead(KEYCOL0) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL0)==0); return '1'; }
            if (GPIO_PinRead(KEYCOL1) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL1)==0); return '2'; }
            if (GPIO_PinRead(KEYCOL2) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL2)==0); return '3'; }
            if (GPIO_PinRead(KEYCOL3) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL3)==0); return '4'; }
            if (GPIO_PinRead(KEYCOL4) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL4)==0); return '5'; }
           
            GPIO_PinSet(KEYROW0);
            GPIO_PinSet(KEYROW1); 
            GPIO_PinSet(KEYROW2); 
            GPIO_PinClear(KEYROW3);    
            if (GPIO_PinRead(KEYCOL0) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL0)==0); return '6'; }
            if (GPIO_PinRead(KEYCOL1) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL1)==0); return '7'; }
            if (GPIO_PinRead(KEYCOL2) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL2)==0); return '8'; }
            if (GPIO_PinRead(KEYCOL3) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL3)==0); return '9'; }
            if (GPIO_PinRead(KEYCOL4) == 0) { vTaskDelay(50 / portTICK_PERIOD_MS); while (GPIO_PinRead(KEYCOL4)==0); return '0'; }
            
    return 'n';                   
}


char switch_press_scan(void)                       // Get key from user
{
    char key = 'n';              // Assume no key pressed
    while(key=='n')              // Wait untill a key is pressed
    key = keypad_scanner();   // Scan the keys again and again
    return key;                  //when key pressed then return its value
}

void key_bounce_sound(char key)
{
    if(key != 'n')
    {
        BUZZER_Set();
        vTaskDelay(50 / portTICK_PERIOD_MS);
        BUZZER_Clear();        
    }
}

void get_key(void)
{    
    char Key = 'n';
    InitKeypad();

    Key = switch_press_scan();
    key_bounce_sound(Key);
}