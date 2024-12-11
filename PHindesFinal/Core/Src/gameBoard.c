/*
 * gameBoard.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#include "gameBoard.h"

void initializeBoard(Board *board) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board->grid[i][j] = 0;
        }
    }
}

Board boardWithPiece(Board *board, Piece *piece) {
	Board tempBoard;

    // Copy the board grid to a temporary grid
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
        	tempBoard.grid[i][j] = board->grid[i][j];
        }
    }

    // Overlay the active piece onto the temporary grid
    for (int pi = 0; pi < 4; pi++) {
        for (int pj = 0; pj < 4; pj++) {
            int px = piece->x + pj;
            int py = piece->y + pi;

//            if (px >= 0 && px < BOARD_WIDTH && py >= 0 && py < BOARD_HEIGHT && piece->matrix[pi][pj] == 1) {
            if (piece->matrix[pi][pj])
            	tempBoard.grid[py][px] = piece->matrix[pi][pj];
//            }
        }
    }

    return tempBoard;
}
