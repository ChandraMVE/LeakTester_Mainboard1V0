/*******************************************************************************
  System Interrupts File

  Company:
    Microchip Technology Inc.

  File Name:
    interrupt_a.S

  Summary:
    Raw ISR definitions.

  Description:
    This file maps all the interrupt vectors to their corresponding
    implementations. If a particular module interrupt is used, then its ISR
    definition can be found in corresponding PLIB source file. If a module
    interrupt is not used, then its ISR implementation is mapped to dummy
    handler.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *******************************************************************************/
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <xc.h>
#include "ISR_Support.h"

   .extern  ADC_Handler

   .section .vector_27,code, keep
   .equ     __vector_dispatch_27, IntVectorADC_Handler
   .global  __vector_dispatch_27
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorADC_Handler

IntVectorADC_Handler:
    la    $26,  _ADC_Handler
    jr    $26
    nop
    .end    IntVectorADC_Handler

   .section .ADC_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _ADC_Handler

_ADC_Handler:
    portSAVE_CONTEXT
    la    s6,  ADC_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _ADC_Handler
   .extern  UART_2_Handler

   .section .vector_32,code, keep
   .equ     __vector_dispatch_32, IntVectorUART_2_Handler
   .global  __vector_dispatch_32
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorUART_2_Handler

IntVectorUART_2_Handler:
    la    $26,  _UART_2_Handler
    jr    $26
    nop
    .end    IntVectorUART_2_Handler

   .section .UART_2_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _UART_2_Handler

_UART_2_Handler:
    portSAVE_CONTEXT
    la    s6,  UART_2_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _UART_2_Handler
   .extern  I2C_2_Handler

   .section .vector_33,code, keep
   .equ     __vector_dispatch_33, IntVectorI2C_2_Handler
   .global  __vector_dispatch_33
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorI2C_2_Handler

IntVectorI2C_2_Handler:
    la    $26,  _I2C_2_Handler
    jr    $26
    nop
    .end    IntVectorI2C_2_Handler

   .section .I2C_2_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _I2C_2_Handler

_I2C_2_Handler:
    portSAVE_CONTEXT
    la    s6,  I2C_2_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _I2C_2_Handler
   .extern  USB_1_Handler

   .section .vector_45,code, keep
   .equ     __vector_dispatch_45, IntVectorUSB_1_Handler
   .global  __vector_dispatch_45
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  IntVectorUSB_1_Handler

IntVectorUSB_1_Handler:
    la    $26,  _USB_1_Handler
    jr    $26
    nop
    .end    IntVectorUSB_1_Handler

   .section .USB_1_Handler_vector_text, code, keep
   .set     nomicromips
   .set     noreorder
   .set     nomips16
   .set     noat
   .ent  _USB_1_Handler

_USB_1_Handler:
    portSAVE_CONTEXT
    la    s6,  USB_1_Handler
    jalr  s6
    nop
    portRESTORE_CONTEXT
    .end    _USB_1_Handler

