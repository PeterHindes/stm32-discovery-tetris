/*
 * gameBoard.h
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#ifndef INC_GAMEBOARD_H_
#define INC_GAMEBOARD_H_

#include "pieces.h"
#include "constants.h"

typedef struct {
    int grid [BOARD_HEIGHT][BOARD_WIDTH];
} Board;

void initializeBoard(Board *board);
Board boardWithPiece(Board *board, Piece *piece);

#endif /* INC_GAMEBOARD_H_ */
