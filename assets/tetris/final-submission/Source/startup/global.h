#ifndef __GLOBAL_H
#define __GLOBAL_H

#include <stdint.h>

#define MARGINE_X 10
#define MARGINE_Y 10
#define QUADRATO 10

extern volatile uint16_t score; 
extern volatile uint16_t lines;
extern volatile uint16_t top;
extern volatile uint8_t speed;
extern  volatile uint8_t random_block_x;
extern volatile uint8_t  random_block_y;
extern volatile uint8_t random_block_type;
extern volatile uint8_t powerup_activated;
extern volatile uint8_t cleared_lines_powerup;
extern volatile int slow_down_counter;

typedef enum {
    pause, 
    play,
		gameover
} GameState;

typedef struct {
    int type;      // da 0 a 6
    int rotation;  // da 0 a 3
    int x, y;
} ActivePiece;

extern uint8_t grid[20][10];

#endif