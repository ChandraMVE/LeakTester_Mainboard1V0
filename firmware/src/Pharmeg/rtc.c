/*
 * File:   RTC_TEST_5.c
 * Author: Devilal
 *
 * Created on 5 May, 2021, 8:43 PM
 */
 
 
// add freqency 
//#define _XTAL_FREQ 20000000
#define    FCY    10000000UL    // Instruction cycle frequency, Hz - required for __delayXXX() to work
//  add delay header file
#include "string.h"
#include "xc.h"
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
 
#include "xc.h"
#include "rtc.h"
 
#define  ADDR_RTCC_WRITE   0xA2       //  DEVICE ADDR for RTCC MCHP  (writes) 
#define  ADDR_RTCC_READ    0xA3       //  DEVICE ADDR for RTCC MCHP  (reads) 
 
#define  ADDR_RTCC_WRITE   0xA2       //  DEVICE ADDR for RTCC MCHP  (writes) 
#define  ADDR_RTCC_READ    0xA3       //  DEVICE ADDR for RTCC MCHP  (reads) 
 
#define  ADDR_SEC          0x02       //  address of SECONDS      register 
#define  ADDR_MIN          0x03       //  address of MINUTES      register 
#define  ADDR_HOUR         0x04       //  address of HOURS        register 
#define  ADDR_DATE         0x05       //  address of DATE         register  
#define  ADDR_DAY          0x06       //  address of DAY OF WK    register 
#define  ADDR_MNTH         0x07       //  address of MONTH        register 
#define  ADDR_YEAR         0x08       //  address of YEAR         register 
 
#define OSC_STAT           0x00     
 
#define  OSCRUN            0x00       //  state of the oscillator(running or not)
 
#define I2C_CLK 100000      //100KHz
 
#define OK      0
#define ERROR   1 
unsigned char err_flg           ;   // global error flag 
typedef unsigned char uchar8;
 
uchar8          SetSec = 0x00;
uchar8          SetMin = 0x00;
uchar8          SetHour = 0x00;
char timer[30];
char calender[20];
uchar8  RtcInitFlag = 0;
 
 
uchar8 ReadYear = 0x00,ReadMonth = 0x00,ReadDay = 0x00,ReadDate = 0x00,ReadWeek = 0x00,ReadHour = 0x00,ReadMin = 0x00,ReadSec = 0x00;
 
 
 unsigned char sec, min1,min, hr, day, wkday, mn, year;
  int hr2,min2;
 long rtc_tseconds;
 int flag;
  
 int son;
 int soff;
typedef union
{
    unsigned char RTCRawBuffer[7];
    struct
    {
        unsigned char RTC_Sec;
        unsigned char RTC_Min;
        unsigned char RTC_Hour;
        unsigned char RTC_Day;
        unsigned char RTC_Date;
        unsigned char RTC_Month;
        unsigned char RTC_Year;
 
    }RTCReg;
}RTC_t;
 
void poll_tim1(void)
{
    vTaskDelay(1 / portTICK_PERIOD_MS);
}

RTC_t RTC;
   
void ini_i2c2(void);
void ini_i2c2(void)
{
//I2C2BRG = 0x009d                ;     // Fcy = 16 MHz -> Fscl = 100 kHz
I2C2BRG = 49                ;   // Fcy = 5 MHz -> Fscl = 100 kHz
I2C2STAT= 0X0000                ;
I2C2CON = 0x1200                ;   // release SCL1 clock, 7-bit slave address
                                    // slew rate control disabled
I2C2RCV = 0x0000                ;   // clear the transmit and receive registers
I2C2TRN = 0x0000;
I2C2CONbits.I2CEN=1             ; } // enable the I2C2 module
 
 
void i2c_start(void)
{
while (I2C2STATbits.TRSTAT);        // Wait for bus Idle
I2C2CONbits.SEN = 1        ;        // Generate Start Condition
poll_tim1()                ;   
}   // Wait for I2C/Timer1 interrupt flag
 
void i2c_wr(unsigned char i2c_data){
while (I2C2STATbits.TRSTAT);        // Wait for bus Idle
I2C2TRN=i2c_data           ;        // Load byte in the transmit buffer
poll_tim1()                ;    
}   // Wait for I2C/Timer1 interrupt flag
 
 
 
void i2c_stop(void){
while (I2C2STATbits.TRSTAT);        // Wait for bus Idle
I2C2CONbits.PEN = 1        ;        // Generate Stop Condition
poll_tim1()                ;    
}   // Wait for I2C/Timer1 interrupt flag
 
 
void i2c_restart(void){
while (I2C2STATbits.TRSTAT);        // Wait for bus Idle
I2C2CONbits.RSEN = 1       ;        // Generate a Restart       
poll_tim1()                ;    
}   // Wait for I2C/Timer1 interrupt flag
 
 
void RTC_init()      //rtc initialization
{
ini_i2c2();
i2c_start(); // issue start signal
i2c_wr(0x51); // slave address PCF8563
i2c_stop();
}

void i2c_ack(void)
{
I2C2CONbits.ACKDT = 0      ;        // Clear  the related flag for Ack
I2C2CONbits.ACKEN = 1      ;        // Start Ack sequence
poll_tim1()                ;    
}   // Wait for I2C/Timer1 interrupt flag
 
void i2c_nack(void)
{
I2C2CONbits.ACKDT = 1      ;        // Set   the related flag for NotAck
I2C2CONbits.ACKEN = 1      ;        // Start Ack sequence
poll_tim1()                ;        // Wait  for I2C/Timer1 interrupt flag
I2C2CONbits.ACKDT = 0      ;    
}   // Clear the related flag for ACk

unsigned char i2c_rd1(unsigned ack)
{
unsigned char rx_byte = 0xff;
 
while (I2C2STATbits.TRSTAT);        // Wait for bus Idle
I2C2CONbits.RCEN = 1       ;        // Enable Master receive
//IFS2bits.MI2C1IF = 0;
poll_tim1();        // Wait for I2C/Timer1 interrupt flag
rx_byte = I2C2RCV;
if(ack == 0)
    i2c_ack();
else
    i2c_nack();
 
return(rx_byte)            ;    }   // Return data in buffer
 
 
void Read_Time(uint8_t *sec, uint8_t *min1, uint8_t *hr) 
{
    
 i2c_start();
 i2c_wr(0xA2);             // read address universal    pcf8563
 i2c_wr(0x02);             //starts from addres for  seconds
 i2c_restart();
 i2c_wr(0xA3);             //A0+1         read data
  
 *sec =i2c_rd1(0) & 0b01111111;           //seconds   and ignoring vl bit
 *min1 =i2c_rd1(0)& 0b01111111;          //minutes  and ignoring unwanted msb bit (7 bit as per datasheet pcf8563 6th page)
 *hr =i2c_rd1(1)& 0b00111111;            //hours , ignoring unwanted msb bits (6,7 bits)
 i2c_stop();
//UART1_Write(13);UART1_Write(10); //Delay_ms(100);
}
  
void Read_calendar(uint8_t *day,uint8_t *wkday,uint8_t *mn,uint8_t *year)
  {
       i2c_start();
       i2c_wr(0xA2);            //like A0  Example
       i2c_wr(0x05);            //starts from
       i2c_restart();
       i2c_wr(0xA3);            //A0+1
       *day =i2c_rd1(0)& 0b00111111;           //day , ignoring unwanted msb bits (6,7 bits)
       *wkday =i2c_rd1(0)& 0b00000111;        //wkday   , ignoring unwanted msb bits (3,4,5,6,7 bits)
       *mn =i2c_rd1(0)& 0b00011111;           //month     , ignoring unwanted msb bits (5,6,7 bits)
       *year =i2c_rd1(1);         //year
       i2c_stop();
      //UART1_Write(13);UART1_Write(10); //Delay_ms(100);
  }//~
 
int BCDToDecimal(int BCD)
{
   return (((BCD>>4)*10) + (BCD & 0xF));
}
 
void Transform_Time(uint8_t *sec, uint8_t *min, uint8_t *hr)
  {
     *sec  =  BCDToDecimal(*sec);  // Transform seconds
     *min  =  BCDToDecimal(*min); // Transform minutes
     *hr   =  BCDToDecimal(*hr);// Transform hours
      
      
     //UART4TransmitString(hr2,sizeof(hr2));
      
     memset(timer,'\0',sizeof(timer));
    
     hr2=(*hr*100)+(*min);   //atoi(timer);      
      
  }//~
 
void Transform_calendar(uint8_t *day ,uint8_t *wkday, uint8_t *mn, uint8_t *year)
  {  
     *day       =  BCDToDecimal(*day);// Transform day
     *wkday     =  BCDToDecimal(*wkday);  // Transform weakday
     *mn        =  BCDToDecimal(*mn); // Transform months
     *year      =  BCDToDecimal(*year);// Transform year
     memset(calender,'\0',sizeof(calender));
     sprintf(calender,"%d-%d-%d\r\n",*day,*mn,*year);
     strcat(timer,calender);
  }//~
 
void rtc_time_write()
{
                ini_i2c2();
                i2c_start(); // issue I2C start signal
                i2c_wr(0xA2); // send byte via I2C (command to 24cO2)
                i2c_wr(0x02); // seconds address
                i2c_wr(0x00); // seconds
                i2c_wr(0x37); // minutes
                i2c_wr(0x13); // hours
                i2c_stop();
}//~!
 
void rtc_calender_write()
 {
                ini_i2c2();
                i2c_start(); // issue I2C start signal
                i2c_wr(0xA2); // send byte via I2C (command to 24cO2)
                i2c_wr(0x05); // starts from days  address asper pcf8623 data sheet
                i2c_wr(0x06);  // current date(live date)
                i2c_wr(0x01); // weak day like 0 t0 7
                i2c_wr(0x05); // centure months
                i2c_wr(0x21); // year
                i2c_stop();
 }
 
  
int get_rtc(void)  
{
     
//    OSCCON = 0x0000;
//    OSCTUN = 0x0000;
    //resetSource = RCON;
//    RCON = 0x00;
     
    RTC_init();
    son=1300;
    soff=1339;
    
//    vTaskDelay(1000 / portTICK_PERIOD_MS);
//    while (1) 
    {
       Read_Time(&sec,&min1,&hr); // read time from RTC(PCF8583)
       Transform_Time(&sec,&min1,&hr); // format date and time
       
       Read_calendar(&day,&wkday,&mn,&year);
       Transform_calendar(&day,&wkday,&mn,&year);
        
      if(( (hr2>son) && (hr2<2400) )&& ((hr2>0000) && (hr2<soff)))
       {
            flag = 1;
       }
        
       else
       {
         
          flag = 0;
       }
 
//    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
 
    return 0;
}