#include "SysTick.h"
#include "tm4c123gh6pm_registers.h"

void SysTick_Init(uint16 a_TimeInMilliSeconds){
  SYSTICK_CTRL_REG = 0;
  SYSTICK_CURRENT_REG = 0;
  SYSTICK_RELOAD_REG = (16000 * a_TimeInMilliSeconds) - 1;
  SYSTICK_CURRENT_REG = 0x6;
}

void SysTick_StartBusyWait(uint16 a_TimeInMilliSeconds){
  SYSTICK_CTRL_REG = 0;
  SYSTICK_CURRENT_REG = 0;
  SYSTICK_RELOAD_REG = (16000 * a_TimeInMilliSeconds) - 1;
  SYSTICK_CURRENT_REG = 0x5;

  while((SYSTICK_CTRL_REG & SYSTICK_CTRL_COUNT_MASK) == 0);

  SysTick_DeInit();
}

void SysTick_Handler(void){
  (*SysTick_CallBack)();
}

void SysTick_SetCallBack(volatile void (*Ptr2Func) (void)){
  SysTick_CallBack = Ptr2Func;
}

void SysTick_Stop(void){
  SYSTICK_CTRL_REG &= ~SYSTICK_CTRL_ENABLE_MASK;
}

void SysTick_Start(void){
  SYSTICK_CTRL_REG |= SYSTICK_CTRL_ENABLE_MASK;
}

void SysTick_DeInit(void){
  SYSTICK_CTRL_REG = 0;
  SYSTICK_CURRENT_REG = 0;
}
