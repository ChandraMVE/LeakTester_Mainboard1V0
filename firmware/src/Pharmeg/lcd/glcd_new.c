/*
 * GLCD128x64 interface with PIC18F4550
 * http://electronicwings.com
 * 
 */
#include "glcd_new.h"
#include "Font_Header.h"

void lcdpin_configuration (void)
{
    GPIO_PinOutputEnable(CS1);
    GPIO_PinOutputEnable(CS2);
    GPIO_PinOutputEnable(R_W);
    GPIO_PinOutputEnable(RS);
    GPIO_PinOutputEnable(EN);
    GPIO_PinOutputEnable(RST);
    GPIO_PortOutputEnable(GPIO_PORT_E,0x00);
}

/*****************************Delay Function*****************************/

void MSdelay(unsigned int val)
{
     unsigned int i,j;
        for(i=0;i<=val;i++)
            for(j=0;j<165;j++);
}

void new_GLCD_Command(char cmd)/* GLCD Command function */
{
    LCD_data = cmd;	/* Copy command on data pin */
    GPIO_PinClear(RS);		/* Make RS LOW for command register*/
    GPIO_PinSet(EN);		/* Make HIGH-LOW transition on Enable */
    usDelay(10);
    GPIO_PinClear(EN);
    usDelay(10);
}

void new_GLCD_Init()	/* GLCD Initialization function */
{
    lcdpin_configuration();	/* Make Control pin as output */
//    Data_dir = 0x00;	/* Make Data pin as output */
    GPIO_PinClear(RST);		/* Make reset pin LOW */
    usDelay(200);
    GPIO_PinSet(RST);		/* Make reset pin High */
	GPIO_PinSet(CS1); 
    GPIO_PinSet(CS2);/* Select Left half of display */
    GPIO_PinClear(R_W); /*always set at write mode*/
    GPIO_PinClear(RS); /*RS must be set low*/
    usDelay(2000);
    new_GLCD_Command(0x3E);	/* Display OFF */
    new_GLCD_Command(0x40);	/* Set Y address (column=0) */
    new_GLCD_Command(0xB8);	/* Set x address (page=0) */
    new_GLCD_Command(0xC0);	/* Set z address (start line=0) */
    new_GLCD_Command(0x3F);	/* Display ON */
}

void new_GLCD_Char(char data)/* GLCD Data function */
{
    LCD_data = data;	/* Copy Data on data pin */
    GPIO_PinSet(RS);		/* Make RS HIGH for data register */
    GPIO_PinSet(EN);		/* Make HIGH-LOW transition on Enable */
    usDelay(10);
    GPIO_PinClear(EN);
    usDelay(10);
}

void new_GLCD_Clear()
{
	int i,j;
	GPIO_PinSet(CS1);
    GPIO_PinSet(CS2);
	for(i=0;i<8;i++)
	{
		new_GLCD_Command((0xB8)+i);
		for(j=0;j<64;j++)
		{
			new_GLCD_Char(0x00);
		}
	}
	new_GLCD_Command(0x40);
	new_GLCD_Command(0xB8);
}

void new_GLCD_String(char page_no, char *str)/* GLCD string write function */
{
	unsigned int i,column,Page=((0xB8)+page_no),Y_address=0;	
	float Page_inc=0.5;													
	GPIO_PinSet(CS1);
    GPIO_PinClear(CS2);	/* Select Left half of display */
	new_GLCD_Command(Page);
	for(i=0;str[i]!=0;i++)	/* Print char in string till null */
	{
       if (Y_address>(1024-(((page_no)*128)+5)))
          break;
        if (str[i]!=32)
        {
            for (column=1;column<=5;column++)
            {
                if ((Y_address+column)==(128*((int)(Page_inc+0.5))))
                {
                    if (column==5)
                        break;
                    new_GLCD_Command(0x40);
                    Y_address = Y_address+column;
                    GPIO_PinToggle(CS1); 
                    GPIO_PinToggle(CS2);
                    new_GLCD_Command((Page+Page_inc));
                    Page_inc=Page_inc+0.5;
                }
            }
        }
        if (Y_address>(1024-(((page_no)*128)+5)))
            break;
        if((font[((str[i]-32)*5)+4])==0 || str[i]==32)
        {
            for(column=0;column<5;column++)
            {
                new_GLCD_Char(font[str[i]-32][column]);
                if((Y_address+1)%64==0)
                {
                    GPIO_PinToggle(CS1); 
                    GPIO_PinToggle(CS2);
                    new_GLCD_Command((Page+Page_inc));
                    Page_inc=Page_inc+0.5;
                }
                Y_address++;
            }
        }
        else
        {
            for(column=0;column<5;column++)
            {
                new_GLCD_Char(font[str[i]-32][column]);
                if((Y_address+1)%64==0)
                {
                    GPIO_PinToggle(CS1);
                    GPIO_PinToggle(CS2);
                    new_GLCD_Command((Page+Page_inc));
                    Page_inc=Page_inc+0.5;
                }
                Y_address++;
            }
            new_GLCD_Char(0);
            Y_address++;
            if((Y_address)%64==0)
            {
                GPIO_PinToggle(CS1);
                GPIO_PinToggle(CS2);
                new_GLCD_Command((Page+Page_inc));
                Page_inc=Page_inc+0.5;
            }
        }
    }
	new_GLCD_Command(0x40);
}

void glcd_new_init(void)
{
    new_GLCD_Init();	/* GLCD Initialize function */
    new_GLCD_Clear();	/* GLCD Display clear function */
    new_GLCD_String(0,"WELCOME TO MVE DEV TEAM - ABCDEFGHIJKLMNOPQRSTUVWXYZ 123456789 ~!@#$%^&*()-+-=<>?/;:`'{}[]| **********#########################HELLO PHARMEG###########################**");  /* Print string on 4th page of GLCD */
}