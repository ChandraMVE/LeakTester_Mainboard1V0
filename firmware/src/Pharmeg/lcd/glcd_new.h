#include "../LeakTester_Mainboard1V0.h"

#define CS1     GPIO_PIN_RG6		// CS1 Bit   // swap pin assignments with CSEL2 if left/right image is reversed
#define CS2     GPIO_PIN_RG14		// CS2 Bit
#define R_W     GPIO_PIN_RG12		// R/W Bit
#define RS      GPIO_PIN_RG7		// RS/D/I Bit
#define EN      GPIO_PIN_RG13		// EN Bit
#define RST 	GPIO_PIN_RG1		// Reset Bit
#define LCD_DB0 GPIO_PIN_RE0        //LCD Data0
#define LCD_DB1 GPIO_PIN_RE1        //LCD Data1
#define LCD_DB2 GPIO_PIN_RE2        //LCD Data2
#define LCD_DB3 GPIO_PIN_RE3        //LCD Data3
#define LCD_DB4 GPIO_PIN_RE4        //LCD Data4
#define LCD_DB5 GPIO_PIN_RE5        //LCD Data5
#define LCD_DB6 GPIO_PIN_RE6        //LCD Data6
#define LCD_DB7 GPIO_PIN_RE7        //LCD Data7

#define LCD_data        LATE
#define Data_dir        TRISE

void new_GLCD_Init(void);
void new_GLCD_Command(char);
void new_GLCD_Char(char);
void new_GLCD_String(char page_no, char *str);
void new_GLCD_Clear(void);
void MSdelay(unsigned int);
void glcd_new_init(void);