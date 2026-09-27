#include "LPC17xx.h"
#include "timer.h"

void RIT_init(void)
{
	LPC_SC->PCONP |= (1<<16);
	LPC_RIT->RICOMPVAL = 100000; // 1 square/secondo = circa 800000, lo imposto a metà così nel frattempo controllo lo stato del joystick
	LPC_RIT->RICOUNTER = 0;
	LPC_RIT->RICTRL = (1<<3) | (1<<1);
	NVIC_EnableIRQ(RIT_IRQn);
	
}

/******************************************************************************
**                            End Of File
******************************************************************************/
