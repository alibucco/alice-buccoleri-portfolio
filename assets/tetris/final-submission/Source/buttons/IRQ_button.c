#include "button.h"
#include "LPC17xx.h"
#include "..\startup\global.h"

extern volatile GameState current_state;
volatile uint8_t ground = 0;


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	for(volatile int i = 0; i < 500000; i++); // per evitare il debouncing
	
	if (current_state == pause) {
		current_state = play;
	} else {
		current_state = pause;
	}
	
	LPC_SC->EXTINT = (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)     /* KEY2														 */
{
	for(int i = 0; i < 500000; i++); // per evitare il debouncing
	
	ground = 1;
	
	LPC_SC->EXTINT = (1 << 2);     /* clear pending interrupt         */
}



