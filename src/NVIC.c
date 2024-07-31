#include "NVIC.h"

void NVIC_EnableIRQ(NVIC_IRQType IRQ_Num){
  uint8 regOffset = IRQ_Num / 32;
  uint8 regPos = IRQ_Num % 32;

  volatile uint32* regAddress = NVIC_EN_REG + (regOffset*4);
  *regAddress |= (1<<regPos);
}

void NVIC_DisableIRQ(NVIC_IRQType IRQ_Num){
  uint8 regOffset = IRQ_Num / 32;
  uint8 regPos = IRQ_Num % 32;

  volatile uint32* regAddress = NVIC_DIS_REG + (regOffset*4);
  *regAddress |= (1<<regPos);
}

void NVIC_SetPriorityIRQ(NVIC_IRQType IRQ_Num, NVIC_IRQPriorityType IRQ_Priority){
  uint8 regOffset = IRQ_Num / 4;
  uint8 regPos = IRQ_Num % 4;

  volatile uint32* regAddress = NVIC_PRI_REG + (regOffset*4);
  uint32 priority = IRQ_Priority << ((regPos*8) + 5);
  *regAddress &= ~(7 << ((regPos*8) + 5));
  *regAddress |= priority;
}

void NVIC_EnableException(NVIC_ExceptionType Exception_Num){
  NVIC_SYSTEM_SYSHNDCTRL |= (1<<(Exception_Num + 12));
}

void NVIC_DisableException(NVIC_ExceptionType Exception_Num){
  NVIC_SYSTEM_SYSHNDCTRL &= ~(1<<(Exception_Num + 12));
}

void NVIC_SetPriorityException(NVIC_ExceptionType Exception_Num, NVIC_ExceptionPriorityType Exception_Priority){
  uint8 regOffset = (Exception_Num / 4) - 1;
  uint8 regPos = Exception_Num % 4;

  volatile uint32* regAddress = NVIC_SYSTEM_PRI_REG + (regOffset*4);
  uint32 priority = Exception_Priority << ((regPos*8) + 5);
  *regAddress &= ~(7 << ((regPos*8) + 5));
  *regAddress |= priority;
}
