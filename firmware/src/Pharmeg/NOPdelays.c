#include <xc.h>                                                                 /* Defines special funciton registers, CP0 regs  */
#include "NOPdelays.h"

void __attribute__((optimize("-O0")))  usDelay( unsigned int us )            //function overhead total is 11FCY with -O0
{   //6FCY to get here with -O0
                                        // 1us = 80INS @ 80MIPS (1 INS - 12.5nS)
    //80 - 11 = 69FCY for just first 1uS
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();        //1st uS needs to be 69INS
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();        //as it takes 6INS to get into this function
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();        //and 5INS to get back out
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
    Nop();Nop();Nop();                            //63 NOP
    us--;                                    // 3 DEC

while(us)                                    //while loop with --us=0 = 5FCY
    {                                        //all other uS loops need to be 80INS
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();    
        Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();Nop();        // 3 WHILE LOOP
        Nop();Nop();Nop();Nop();                        //74 NOP
    us--;                                    // 3 DEC
    }                                        //80 TOTAL
}   //5FCY to get from here to out with -O0
