/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "..\lcd\GLCD.h" 
#include "..\buttons\button.h"
#include "..\timer\timer.h"
#include "global.h"
#include "..\shapes\shapes.h"
#include "..\joystick\joystick.h"
#include "..\adc\adc.h"
#include <stdlib.h>
#include <stdio.h>

#ifdef SIMULATOR
#endif

volatile GameState current_state = pause;
volatile ActivePiece current_piece;
uint8_t grid[20][10] = {0};
extern volatile uint8_t step;
extern volatile uint8_t left;
extern volatile uint8_t right;
extern volatile uint8_t up;
extern volatile uint8_t down;
extern volatile uint8_t ground;

uint16_t volatile score = 0;
uint16_t volatile lines = 0;
uint16_t volatile top = 0;
uint8_t volatile speed = 1;

uint8_t volatile random_block_x = 0;
uint8_t volatile random_block_y = 0;
uint8_t volatile random_block_type = 0;
uint8_t volatile powerup_activated = 0;
uint8_t volatile cleared_lines_powerup = 0;
int volatile slow_down_counter;

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	BUTTON_init();
	joystick_init();
	ADC_init();
	
  LCD_Initialization();
	LCD_Clear(Black);
	Screen_SetUp();
	
	RIT_init();
	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);		
	
  while (1)	
  {
		if (current_state == pause) {
			GUI_Text(30, 250, (uint8_t *)"PREMI KEY1 PER INIZIARE", White, Black);
			while (current_state == pause) {
				__ASM("wfi");
			}
			srand(LPC_RIT->RICOUNTER);
			GUI_Text(30, 250, (uint8_t *)"                           ", Black, Black);
		}
		
	
		current_piece.type = rand() % 7;
		current_piece.x = rand() % 7;
		current_piece.y = 0;  // parte dall'alto
		current_piece.rotation = 0; // default
		step = 0;
		
		ground = 0; 
    step = 0;
    up = 0;
    left = 0;
    right = 0;
		down = 0;
		
		if (EmptySpace(current_piece)) {
			DrawTetromino(current_piece, SHAPE_COLORS[current_piece.type]);
		}
		else {
			current_state = gameover;
			GUI_Text(60, 220, (uint8_t *)" GAME OVER! ", Red, White);
		}
		
			
		while (current_piece.y < 18) {
			if (current_state == pause) {
                GUI_Text(25, 250, (uint8_t *)"PREMI KEY1 PER RIPRENDERE", White, Black);
                while (current_state == pause) {
                    __ASM("wfi");
                }
                GUI_Text(25, 250, (uint8_t *)"                           ", Black, Black);
            }
			
									
			if (ground) {
				ground = 0;
				
				DrawTetromino(current_piece, Black);
				
				while (CheckFreeSpace(current_piece)) {
					current_piece.y++; // vado verso terra fin dove posso
				}
				
				DrawTetromino(current_piece, SHAPE_COLORS[current_piece.type]);
			
				break;
			}
				
			
			if (up) {
				up = 0;
				if (CheckFreeSpaceROTATION(current_piece)) {
					DrawTetromino(current_piece, Black);
					
					if (current_piece.rotation != 3) {
						current_piece.rotation++;
					} else {
						current_piece.rotation = 0;
					}
					
					DrawTetromino(current_piece, SHAPE_COLORS[current_piece.type]);
				}
			}
			
			if (left) {
				left = 0;
				if (CheckFreeSpaceLEFT(current_piece)) {
					DrawTetromino(current_piece, Black);
					current_piece.x--;
					DrawTetromino(current_piece, SHAPE_COLORS[current_piece.type]);
				}
			}
			
			if (right) {
				right = 0;
				if (CheckFreeSpaceRIGHT(current_piece)) {
					DrawTetromino(current_piece, Black);
					current_piece.x++;
					DrawTetromino(current_piece, SHAPE_COLORS[current_piece.type]);	
				}
			}
			
			if (step == 1) {
				if (CheckFreeSpace(current_piece)) {
					DrawTetromino(current_piece, Black);
					current_piece.y++; // discesa di 1 allo scattare del doppio RIT
					DrawTetromino(current_piece, SHAPE_COLORS[current_piece.type]);
					step = 0;
				}
				else {
					for (int r = 0; r < 4; r++) {
						for (int c = 0; c < 4; c++) {
							if (SHAPES[current_piece.type][current_piece.rotation][r][c] != 0) {
								grid[current_piece.y + r][current_piece.x + c] = current_piece.type + 1; 
								// segno il current_piece nella griglia non appena tocca un altro tetromino
							}
						};
					};
					break;
				}
			}
		}
		
		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				if (SHAPES[current_piece.type][current_piece.rotation][r][c] != 0) {
					grid[current_piece.y + r][current_piece.x + c] = current_piece.type + 1; 
					// segno il current_piece nella griglia non appena tocca terra
				}
			}
		};
		
		score += 10;
		UpdateScore(score);
		
		int filled = 0;
				
				// controllo se le righe appena scritte sono piene; se sì, le cancello
				for (int r = 3; r >= 0; r--) {
					int current_row = current_piece.y + r;		
					
					if (current_row <= 19) {
						if (FilledLine(current_row)) {
							lines++;
							DeleteLine(current_row);
							filled++;
								
							score += 10;
							UpdateLines(lines);
							
							if (lines % 5 == 0) {
								AddPowerup();
							}
							
							if (lines % 10 == 0) {
								AddRandomMalus();
							}
							
							if (filled > 0) {
								if (filled == 4) {
									score += 600;
									UpdateScore(score);
								} else {
									score += (filled * 100);
									UpdateScore(score);
								}
							}	
							r++; // ricontrollo la stessa riga, che ora corrisponde a quella precedente
						}
						
						if (powerup_activated) {
							cleared_lines_powerup = 0; // resetto la variabile
							
							DeleteLinePowerup();
							powerup_activated = 0;
							
							lines += cleared_lines_powerup;
							UpdateLines(lines);
							
							while (cleared_lines_powerup >= 4) {
								score += 600;
								cleared_lines_powerup -= 4;
							}
							
							if (cleared_lines_powerup > 0) {
								score += (cleared_lines_powerup * 100);
							}
							
							UpdateScore(score);
							
							slow_down_counter = 300;
						}
					}
				}
				
				if (current_state == gameover) {
					for (int r = 0; r < 20; r++) {
						for (int c = 0; c < 10; c++) {
							grid[r][c] = 0; // reset della grid
						}
					}
					
					
					
					if (score > top) {
						top = score;
					}
					
					score = 0;
					lines = 0;
					
					LCD_Clear(Black);
					Screen_SetUp();
					current_state = pause;
					
				}
	};
}



/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
