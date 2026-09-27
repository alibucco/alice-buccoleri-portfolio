#include "LPC17xx.h"
#include "joystick.h"
#include "..\startup\global.h"
#include "..\shapes\shapes.h"
#include "..\timer\timer.h"
#include "..\lcd\GLCD.h" 
#include <stdlib.h>

extern volatile ActivePiece current_piece;
extern volatile uint8_t step;
volatile uint8_t left = 0;
volatile uint8_t right = 0;
volatile uint8_t up = 0;
volatile uint8_t down = 0;

void JOYSTICK_UP(void) {
	up = 1;
}

void JOYSTICK_DOWN(void) {
	down = 1;
}

void JOYSTICK_LEFT(void) {
	left = 1;
}

void JOYSTICK_RIGHT(void) {
	right = 1;
}

	

	