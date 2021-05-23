/*
 * SysTickDrv.h
 *
 *  Created on: May 18, 2021
 *      Author: lanit
 */

#ifndef SYSTICKDRV_H_
#define SYSTICKDRV_H_

#include <stdint.h>
#include <stdbool.h>


#define NULL (void *)0

#define HREG32(x)         (*((volatile uint32_t *)(x)))


/* Registers Map*/
#define STCTRL    HREG32(0xE000E010)
#define STRELOAD  HREG32(0xE000E014)
#define STCURRENT HREG32(0xE000E018)

#define SYSTICK_MAXCTS 0x00FFFFFF
/* CLK_SRC */
#define CLK_FIELD_BIT_OFFSET 2
#define REGVAL_SYSCLOCK      1
#define REGVAL_PIOSC         0

/* INTERRUPTS ENABLE */
#define INTEN_FIELD_BIT_OFFSET 1
#define ENABLE_INT             1

/* START TIMER */
#define ENABLE_OFFSET   0
#define ENABLE_SYSTICK  1

/* COUNT TO 0 FLAG */
#define SYSTICK_COUNT   ((uint32_t)(1<<16))
#define TIMER_ELAPSED       1

typedef struct sSystickReg
{

    uint8_t  u8clock_src;
    uint8_t  interruptEn;
    uint8_t  start_counter;
    uint32_t SysTick_CountLimit;
}sSystickReg;

typedef sSystickReg tSystickReg;

void Drv_Reload_Systick(unsigned int u32_reload);
void Drv_GetSys_TickValue(unsigned int * SysValue);
void Drv_CtrlSysTick(tSystickReg * SystickCfg );
void Drv_SysTick_IsTimerElapsed(uint8_t * TimerPassed);
#endif /* SYSTICKDRV_H_ */
