/*
 * pieces.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#include "pieces.h"

// 1 teal
// 2 yellow
// 3 magenta
// 4 dark blue
// 5 orange
// 6 lime green
// 7 red

int TETROMINOS[7][4][4] = {
    {{1, 1, 1, 1}},             // I
    {{2, 2}, {2, 2}},           // O
    {{0, 3, 3}, {3, 3, 0}},     // S
    {{4, 4, 0}, {0, 4, 4}},     // Z
    {{5, 0}, {5, 0}, {5, 5}},   // L
    {{0, 6}, {0, 6}, {6, 6}},   // J
    {{0, 7, 0}, {7, 7, 7}},     // T
};

uint16_t TETROMINO_COLORS[7][3] = {
	{0x0679, 0x07FF, 0x04D3}, // 1 teal
	{0xCE60, 0xFFE0, 0x9CC0}, // 2 yellow
	{0x9819, 0xC81F, 0x6013}, // 3 magenta
	{0x0019, 0x001F, 0x0013}, // 4 dark blue
	{0xCB20, 0xFC40, 0x9A20}, // 5 orange
	{0x0660, 0x07E0, 0x04C0}, // 6 lime green
	{0xC800, 0xF800, 0x9800}  // 7 red
};

void initializeRandomPiece(Piece *piece) {
    int randomIndex = rand() % 7;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece->matrix[i][j] = TETROMINOS[randomIndex][i][j];
        }
    }
    piece->x = BOARD_WIDTH / 2 - 1;
    piece->y = 0;
}

// base, light, dark
uint16_t * piceIndexToColors(int index) {
	return TETROMINO_COLORS[index];
}
