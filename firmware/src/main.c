/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes
#include "Pharmeg/rtc.h"
#include "Pharmeg/LeakTester_Mainboard1V0.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
const char text_display[100] = "Hello World\n";
long num = 10000;
int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
//    GLCD_Init(true);
//    GLCD_SelectFontEx(System5x7, BLACK, ReadPgmData);
//    GLCD_PrintNumber(num);
//    GLCD_FillRect(0,0,40,40,BLACK);    
//    RTC_init();

    glcd_new_init();
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

