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

typedef struct sSystickReg
{

    uint8_t  u8clock_src;
    uint8_t  interruptEn;
    uint8_t  start_counter;
    uint16_t count;
};

typedef sSystickReg tSystickReg;

void Drv_Reload_Systick(unsigned int u32_reload);
void Drv_GetSys_TickValue(unsigned int * SysValue);
void Drv_CtrlSysTick(tSystickReg * SystickCfg );

#endif /* SYSTICKDRV_H_ */
