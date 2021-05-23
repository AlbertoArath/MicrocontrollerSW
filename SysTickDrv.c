

#include "SysTickDrv.h"



/* Systick: Reloads the timer
 *
 *
 */
void Drv_Reload_Systick(uint32_t u32_reload)
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
void Drv_GetSys_TickValue(uint32_t * SysValue)
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
    STCURRENT |= (SYSTICK_MAXCTS - 10); //Arbitrary number clears register
}

/*
 *
 * SysTick Control and Status (STCTRL): A control and status counter to configure its clock,
 * enable the counter, enable the SysTick interrupt, and determine counter status.
 *
 * The SysTick counter reload and current value are undefined at reset; the correct initialization
 * sequence for the SysTick counter is:
 * 1. Program the value in the STRELOAD register.
 * 2. Clear the STCURRENT register by writing to it with any value.
 * 3. Configure the STCTRL register for the required operation.
 */

void Drv_CtrlSysTick(tSystickReg * SystickCfg )
{

    /* 1. Program the value in the STRELOAD register. */
    Drv_Reload_Systick(SystickCfg->SysTick_CountLimit);

    /* 2. Clear the STCURRENT register by writing to it with any value. */
    Drv_ClearSystickCurrVal();
    /*
     * CLK_SRC
     * Value Description
     *
     * 0 = Precision internal oscillator (PIOSC) divided by 4
     * 1 = System clock
     */

    if( REGVAL_SYSCLOCK == (SystickCfg->u8clock_src & REGVAL_SYSCLOCK)){
        STCTRL |= (REGVAL_SYSCLOCK << CLK_FIELD_BIT_OFFSET);
    }
    else
    {
       STCTRL &=  ~((uint32_t)(REGVAL_SYSCLOCK << CLK_FIELD_BIT_OFFSET));
    }

    /*Interrupts enabled by systick*/
    if( SystickCfg->interruptEn == ENABLE_INT )
    {
        STCTRL |= ((uint32_t)(ENABLE_INT<< INTEN_FIELD_BIT_OFFSET));

    }else{
     
        STCTRL &= ~((uint32_t) (ENABLE_INT << INTEN_FIELD_BIT_OFFSET));
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

void Drv_SysTick_IsTimerElapsed(uint8_t * TimerPassed){

    if( (STCTRL & SYSTICK_COUNT) == SYSTICK_COUNT){
    *TimerPassed = TIMER_ELAPSED;
    }
    else{
    *TimerPassed = 0;
    }

}
