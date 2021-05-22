//*****************************************************************************
//
// blinky.c - Simple example to blink the on-board LED.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "driverlib/sysctl.h"
#include "SystickDrv.h"
//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>Blinky (blinky)</h1>
//!
//! A very simple example that blinks the on-board LED using direct register
//! access.
//
//*****************************************************************************



#define GPIOODR        0x50C
#define GPIOAFSEL      0x420
#define GPIODIR        0x400
#define GPIODEN        0x51C
#define GPIODATA       0x000
#define PORTF_BASE_ADD 0x40025000

#define HREG32(x)    (*((volatile unsigned int *)(x)))

#define GPIODATA_PORTF  HREG32(PORTF_BASE_ADD + GPIODATA + 0x3FC)
#define GPIODIR_PORTF   HREG32(PORTF_BASE_ADD + GPIODIR)
#define GPIOAFSEL_PORTF HREG32(PORTF_BASE_ADD + GPIOAFSEL)
#define GPIODR_PORTF    HREG32(PORTF_BASE_ADD + GPIOODR)
#define GPIODEN_PORTF   HREG32(PORTF_BASE_ADD + GPIODEN)
#define RCGCGPIO        HREG32(0x400FE608)

#define GPIO_PORTF      (0x1<<5)

#define SW1_PIN          (1<<4)
#define SW2_PIN          (1<<0)

#define RGB_LED_RED      (1<<1)
#define RGB_LED_BLUE     (1<<2)
#define RGB_LED_GREEN    (1<<3)

#define OFFSET_BB            2


#define RGB_PINS (RGB_LED_BLUE | RGB_LED_GREEN)

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
    while(1);
}
#endif


void delay_ms(unsigned int dela_ms)
{
    volatile unsigned int delay = 3180;
    delay *= dela_ms;
    while(delay--);
}


int main(void)
{

    //init modules
    //Enable PORTF Clocking
    RCGCGPIO |= GPIO_PORTF;
    //Enable GPIO function
    GPIOAFSEL_PORTF &= ~(RGB_PINS);
    GPIODIR_PORTF |= (RGB_PINS);
    GPIODR_PORTF &= ~(RGB_PINS);
    GPIODEN_PORTF |= (RGB_PINS);

    while(1)
    {
       GPIODATA_PORTF |= (RGB_PINS);
       delay_ms(500);
       GPIODATA_PORTF &= ~(RGB_PINS);
       delay_ms(500);
    }
    // Pin PF4 SW1
    // Pin PF0 SW2
    // Pin PF1 RGB LED Red
    // Pin PF2 RGB LED Blue
    // Pin PF3 RGB LED Green
    return 0;
}
