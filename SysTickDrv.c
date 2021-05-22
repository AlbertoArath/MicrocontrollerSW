

#include "SysTickDrv.h"

#define HREG32(x)         (*((volatile unsigned int *)(x)))

#define SYSTICK_MAXCTS 0x00FFFFFF

/* Registers Map*/
#define STCTRL    HREG32(0xE000E000 + 0x010)
#define STRELOAD  HREG32(0xE000E000 + 0x014)
#define STCURRENT HREG32(0xE000E000 + 0x018)



/* CLK_SRC */
#define CLK_FIELD_BIT_OFFSET 2
#define REGVAL_SYSCLOCK      0
#define REGVAL_PIOSC         1

/* INTERRUPTS ENABLE */
#define INTEN_FIELD_BIT_OFFSET 1
#define ENABLE_INT             1

/* START TIMER */
#define ENABLE_OFFSET  0
#define ENABLE_SYSTICK 1


typedef sSystickReg tSystickReg;

/*
 *
 * Reloads the timer
 */
void Drv_Reload_Systick(unsigned int u32_reload)
{
    if(u32_reload > SYSTICK_MAXCTS) {

        u32_reload = SYSTICK_MAXCTS;
    }
    STRELOAD |= u32_reload;
}

/*
 *
 * Here we read the systick values
 *
 */
void Drv_GetSys_TickValue(unsigned int * SysValue)
{
    if( SysValue != NULL ) {
    *SysValue = SYSTICK_MAXCTS & STCURRENT;
    }
}
/*
 *
 * Clear current counts
 * SysTick Current Value (STCURRENT): The current value of the counter.
 *
 */
void Drv_ClearSystickCurrVal(void)
{
    STCURRENT |= 0x00FFFFFE; //Arbitrary number clears register
}

/*
 *
 * SysTick Control and Status (STCTRL): A control and status counter to configure its clock,
 * enable the counter, enable the SysTick interrupt, and determine counter status.
 *
 */

/*
The SysTick counter reload and current value are undefined at reset; the correct initialization
sequence for the SysTick counter is:
1. Program the value in the STRELOAD register.
2. Clear the STCURRENT register by writing to it with any value.
3. Configure the STCTRL register for the required operation.*/

void Drv_CtrlSysTick(tSystickReg * SystickCfg )
{

    /*
     * CLK_SRC
     * Value Description
     *
     * 0 Precision internal oscillator (PIOSC) divided by 4
     * 1 System clock
     */
    if( REGVAL_PIOSC == (SystickCfg->u8clock_src & REGVAL_PIOSC)){
        STCTRL |= (REGVAL_PIOSC << CLK_FIELD_BIT_OFFSET);
    }
    else
    {
       STCTRL &=  ~((uint32_t)(REGVAL_PIOSC << CLK_FIELD_BIT_OFFSET));
    }

    /*Interrupts enabled by systick*/
    if( SystickCfg->interruptEn == 1 )
    {
        STCTRL |= ((uint32_t)(ENABLE_INT<< INTEN_FIELD_BIT_OFFSET));

    }else{

        STCTRL &= ~((uint32_t) (ENABLE_INT << INTEN_FIELD_BIT_OFFSE0T));
    }

    /* Start Systick timer*/
    if( SystickCfg->start_counter == ENABLE_SYSTICK){
        STCTRL |= ENABLE_SYSTICK;
    }
    else{

        STCTRL &= ~((uint32_t)ENABLE_SYSTICK);
    }
}

/* Start Systick*/
void Drv_StartSysTick(uint8_t  StartSystick ){

    /* Start Systick timer*/
    if( ENABLE_SYSTICK == StartSystick){

        STCTRL |= ENABLE_SYSTICK;
    }
    else{
        STCTRL &= ~((uint32_t)ENABLE_SYSTICK);
    }

}

