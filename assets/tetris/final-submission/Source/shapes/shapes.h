#ifndef __SHAPES_H
#define __SHAPES_H

#include <stdint.h>
#include <stdbool.h>
#include "../startup/global.h"

// Ogni pezzo è contenuto in una matrice 4x4
// [7 tipi di pezzi] [4 rotazioni possibili] [16 celle (4x4)]
extern const uint8_t SHAPES[7][4][4][4];

// Definiamo i colori associati a ogni pezzo
extern const uint16_t SHAPE_COLORS[7];
extern const uint16_t COLORS[11];

void DrawTetromino(ActivePiece, uint16_t color);
bool CheckFreeSpace(ActivePiece);
bool CheckFreeSpaceLEFT(ActivePiece);
bool CheckFreeSpaceRIGHT(ActivePiece);
bool CheckFreeSpaceROTATION(ActivePiece);
bool FilledLine(int row);
void DeleteLine(int row);
void DeleteLinePowerup();
void AddPowerup(void);
void AddRandomMalus(void);
bool EmptySpace(ActivePiece);

#endif