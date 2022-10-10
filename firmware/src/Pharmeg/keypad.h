#include "xc.h"
#include "app.h"
#include "LeakTester_Mainboard1V0.h"

#define KEYROW0    GPIO_PIN_RB7
#define KEYROW1    GPIO_PIN_RB8
#define KEYROW2    GPIO_PIN_RB9
#define KEYROW3    GPIO_PIN_RB10
#define KEYCOL0    GPIO_PIN_RA4
#define KEYCOL1    GPIO_PIN_RA5
#define KEYCOL2    GPIO_PIN_RA6
#define KEYCOL3    GPIO_PIN_RA7
#define KEYCOL4    GPIO_PIN_RA9

void InitKeypad(void);
char switch_press_scan(void);
void get_key(void);