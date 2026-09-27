#include "LPC17xx.h"
#include "timer.h"
#include "..\joystick\joystick.h"
#include "..\adc\adc.h"
#include "..\startup\global.h"

extern volatile uint8_t speed;
extern volatile uint8_t down;
extern volatile int slow_down_counter;
extern volatile GameState current_state;
volatile uint8_t ground = 0;

static int ticks = 10;
volatile uint8_t step;
volatile uint8_t final_speed = 0;

static int active_key1 = 0;
static int active_key2 = 0;

void RIT_IRQHandler (void)
{
	if ((LPC_GPIO2->FIOPIN & (1 << 11)) == 0) {
		if (active_key1 == 0) {                   // Debouncing
			if (current_state == pause) {
				current_state = play;
			} else {
				current_state = pause;
			}
			active_key1 = 1;
		}
	}
	else {
		active_key1 = 0;
	}

	if ((LPC_GPIO2->FIOPIN & (1 << 12)) == 0) { 
		if (active_key2 == 0) {
			ground = 1;
			active_key2 = 1;
		}
	}
	else {
		active_key2 = 0;
	}
	
	if (current_state == play) {
		ADC_start_conversion();
	
		ticks--;
	
		if (slow_down_counter > 0) {
			final_speed = 1;
			slow_down_counter--;
		} else {
			if (down) {
				final_speed = speed * 2 ;
			} else {
				final_speed = speed;
			}
		}
	
		if (ticks <= final_speed) {
			step = 1;
			ticks = 10;
			down = 0;
		}
	}
	
	if ((LPC_GPIO1->FIOPIN & (1 << 27)) == 0 ) {
		// joystick LEFT premuto
		JOYSTICK_LEFT();
	}
	
	if ((LPC_GPIO1->FIOPIN & (1 << 28)) == 0) {
		// joystick RIGHT premuto
		JOYSTICK_RIGHT();
	}
	
	if ((LPC_GPIO1->FIOPIN & (1 << 29)) == 0) {
		// joystick UP premuto
		JOYSTICK_UP();
	}
	
	if ((LPC_GPIO1->FIOPIN & (1 << 26)) == 0) {
		// joystick DOWN premuto
		JOYSTICK_DOWN();
	}
		
	LPC_RIT->RICTRL |= 0x1;
	
}
/******************************************************************************
**                            End Of File
******************************************************************************/
