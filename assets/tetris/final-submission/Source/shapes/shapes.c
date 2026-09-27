#include "shapes.h"
#include "../lcd/GLCD.h"
#include "../startup/global.h"
#include <stdbool.h>
#include <stdlib.h>

extern volatile GameState current_state;

// Colori per i 7 pezzi (I, O, T, J, L, S, Z)
const uint16_t SHAPE_COLORS[7] = {
    Cyan, Yellow, Purple, Blue, Orange, Green, Red
};

const uint16_t COLORS[11] = {
	White, Grey, Blue, Blue2, Red, Magenta, Purple, Green, Cyan, Yellow, Orange
};

const uint8_t SHAPES[7][4][4][4] = {
    // 0: I-shaped
    {
        { {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} }, // Rotazione 0
        { {0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0} }, // Rotazione 1
        { {0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0} }, // Rotazione 2
        { {0,0,1,0}, {0,0,1,0}, {0,0,1,0}, {0,0,1,0} }  // Rotazione 3
    },
    // 1: O-shaped
    {
        { {0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} },
        { {0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} },
        { {0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} },
        { {0,1,1,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} }
    },
		// 2: T-shaped
    {
				{ {1,1,1,0}, {0,1,0,0}, {0,0,0,0}, {0,0,0,0} },
				{ {0,1,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0} },
				{ {0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0} },
				{ {1,0,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0} }
		},
		// 3: J-shaped
		{
				{ {1,1,1,0}, {0,0,1,0}, {0,0,0,0}, {0,0,0,0} },
				{ {0,1,0,0}, {0,1,0,0}, {1,1,0,0}, {0,0,0,0} },
				{ {1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0} },
				{ {1,1,0,0}, {1,0,0,0}, {1,0,0,0}, {0,0,0,0} },
		},
		// 4: L-shaped
		{
				{ {1,1,1,0}, {1,0,0,0}, {0,0,0,0}, {0,0,0,0} },
				{ {1,1,0,0}, {0,1,0,0}, {0,1,0,0}, {0,0,0,0} },
				{ {0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0} },
				{ {1,0,0,0}, {1,0,0,0}, {1,1,0,0}, {0,0,0,0} },
		},
		// 5: S-shaped
		{
				{ {0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0} },
				{ {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0} },
				{ {0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0} },
				{ {1,0,0,0}, {1,1,0,0}, {0,1,0,0}, {0,0,0,0} },
		},
		// 6: Z-shaped
		{
				{ {1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} },
				{ {0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0} },
				{ {1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0} },
				{ {0,1,0,0}, {1,1,0,0}, {1,0,0,0}, {0,0,0,0} },	
		}
};


void drawBlock(int gridX, int gridY, uint16_t color) {
	int i;
	
	int x = MARGINE_X + (gridX * QUADRATO);
	int y = MARGINE_Y + (gridY * QUADRATO);
	
	for (i=0; i < QUADRATO; i++) {
		LCD_DrawLine(x, y+i, x+QUADRATO-1, y+i, color);
	}
}


void DrawTetromino(ActivePiece p, uint16_t color) {
    int r, c;
    
    for (r = 0; r < 4; r++) {
        for (c = 0; c < 4; c++) {
            if (SHAPES[p.type][p.rotation][r][c] != 0) {
                // gridX = p.x (posizione globale) + c (colonna interna 4x4)
                // gridY = p.y (posizione globale) + r (riga interna 4x4)
                drawBlock(p.x + c, p.y + r, color);
            }
        }
    }
}

bool CheckFreeSpace(ActivePiece p) {
	int r, c;
	int next_y = p.y + 1;
	
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			if (SHAPES[p.type][p.rotation][r][c] == 1) {
				if (grid[next_y + r][p.x + c] != 0) return false;
				if (next_y + r > 19) return false;
			};
		}
	}
	
	return true;
}

bool CheckFreeSpaceLEFT(ActivePiece p) {
	int r, c;
	int previous_x = p.x - 1;
	
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			if (SHAPES[p.type][p.rotation][r][c] == 1) {
				int shift = previous_x + c;
				if (shift < 0) return false;
				if (grid[p.y + r][shift] != 0) return false;	
			}
		}
	}
	return true;
}

bool CheckFreeSpaceRIGHT(ActivePiece p) {
	int r, c;
	int next_x = p.x + 1;
	
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			if (SHAPES[p.type][p.rotation][r][c] == 1) {
				int shift = next_x + c;
				if (shift > 9) return false;
				if (grid[p.y + r][shift] != 0) return false;
			}
		}
	}
	return true;
}

bool CheckFreeSpaceROTATION(ActivePiece p) {
	int r, c;
	int next_rotation = 0;
	
	if (p.rotation != 3 ){next_rotation = p.rotation + 1;} else {next_rotation = 0;};
	
	for (r = 0; r < 4; r++) {
		for (c = 0; c < 4; c++) {
			if (SHAPES[p.type][next_rotation][r][c] == 1) {
				if (p.x + c > 9) return false;
				if (p.x + c < 0) return false;
				if (p.y + r < 0) return false;
				if (p.y + r > 19) return false;
				if (grid[p.y + r][p.x + c] != 0) return false;
			}
		}
	}
	
	return true;
}

bool FilledLine(int row) {
	int c;
	int filled = 0;
	
	for (c = 0; c < 10; c++) {
		if (grid[row][c] != 0) {
			filled++;
		}
	}
	
	if (filled == 10) {
		return true;
	}
	return false;
}

bool NotEmptyLine (int row) {
	int c;
	int filled = 0;
	
	for (c = 0; c < 10; c++) {
		if (grid[row][c] != 0) {
			filled++;
			if (grid[row][c] == 10) {
				powerup_activated = 1;
			}
		}
	}
	
	if (filled > 0) {
		return true;
	}
	return false;
}


void DeleteLine(int row) {
	int r, c;
	
	for (c = 0; c < 10; c++) {
		if (grid[row][c] == 10) {
			powerup_activated = 1;
    }
  }
	
	for (r = row; r >= 1; r--) {
		for (c = 0; c < 10; c++) {
			grid[r][c] = grid[r-1][c]; // shifto tutte le righe in quelle sottostanti
			
			if (grid[r][c] == 0) {
				drawBlock(c, r, Black);
			} else if (grid[r][c] == 10) {
				drawBlock(c, r, White);
			}	else if (grid[r][c] == 11) {
				drawBlock(c, r, Magenta);
			} else {
				drawBlock(c, r, SHAPE_COLORS[grid[r][c] - 1]);
			}
		}
	}
	
	for (c = 0; c < 10; c++) {
		grid[0][c] = 0; // svuoto l'ultima riga (che è già stata shiftata)
		drawBlock(c, 0, Black);
	}
}

void DeleteLinePowerup(void) {
	int r, c;
	
	for (r = 10; r < 20; r++) {
		if (NotEmptyLine(r)) {
			cleared_lines_powerup++;
		}
	}
	
	for (r = 9; r >= 0; r--) {
		for (c = 0; c <= 9; c++) {
			grid[r+10][c] = grid[r][c];
			
			if (grid[r+10][c] == 0) {
				drawBlock(c, r+10, Black);
			} 
			else if (grid[r+10][c] == 10) {
				drawBlock(c, r+10, White);
			} 
			else if (grid[r+10][c] == 12) {
				drawBlock(c, r+10, Magenta);
			}
			else {
				// Attenzione: grid contiene type+1, quindi per SHAPE_COLORS serve -1
				drawBlock(c, r+10, SHAPE_COLORS[grid[r+10][c] - 1]);
			}
		}
	}
	
	for (r = 0; r <= 9; r++) {
		for (c = 0; c <= 9; c++) {
			grid[r][c] = 0;
			drawBlock(r, c, Black);
		}
	}
}

bool EmptySpace(ActivePiece p) {
	for (int r = 0; r < 4; r++) {
		for (int c = 0; c < 4; c++) {
			if (SHAPES[p.type][p.rotation][r][c] != 0) {
				if (grid[p.y + r][p.x + c] != 0) {
					return false;
				}
			}
		}
	}
	return true;
}


void PowerupBlock(int x, int y, int type, int new_id) {
	if (x < 0 || x >= 10 || y < 0 || y >= 20) return; // interno alla griglia
	if (grid[y][x] != type) return; // stesso colore
	
	grid[y][x] = new_id;
	drawBlock(x, y, White);
	
	PowerupBlock(x + 1, y, type, new_id);
	PowerupBlock(x - 1, y, type, new_id);
	PowerupBlock(x, y + 1, type, new_id);
	PowerupBlock(x, y - 1, type, new_id);
	
	// cerco nella matrice 4x4 i quadrati dello stesso colore, quindi dello stesso blocco
	// devo controllare che siano esattamente 4 quadrati in totale (quindi nelle 4 direzioni)
	// sovrascrivo quel blocco con un nuovo colore randomico
}


void AddPowerup(void) {
	do {
		random_block_x = rand() % 10;
		random_block_y = rand() % 20; // salvo un quadratino randomico
	}
	while (grid[random_block_y][random_block_x] == 0);
		
	random_block_type = grid[random_block_y][random_block_x];
		
	PowerupBlock(random_block_x, random_block_y, random_block_type, 10);
}

void AddRandomMalus(void) {
	if (NotEmptyLine(0)) {
		current_state = gameover;
		return;
	}
	
	for (int r = 0; r <= 18; r++) {
		for (int c = 0; c <= 9; c++) {
			grid[r][c] = grid[r+1][c];
				
			if (grid[r][c] == 0) {
				drawBlock(c, r, Black);
			} else if (grid[r][c] == 10) {
				drawBlock(c, r, White);
			}	else if (grid[r][c] == 11) {
				drawBlock(c, r, Magenta);
			} else {
				drawBlock(c, r, SHAPE_COLORS[grid[r][c] - 1]);
			}
		}
	}
		
	for (int c = 0; c < 10; c++) {
		grid[19][c] = 0; // svuoto l'ultima riga
		drawBlock(c, 19, Black);
	}
		
	int cn = 0;
		
	while (cn < 7) {
		int random_c = rand() % 10;
			
		if (grid[19][random_c] == 0) {
			grid[19][random_c] = 11;
			drawBlock(random_c, 19, Magenta);
			cn++;
		}
	}
}