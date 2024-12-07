#ifndef BOARD_H
#define BOARD_H

#include "pieces.h"
#include "constants.h"

typedef struct {
    int **grid;
} Board;

void initializeBoard(Board *board);
void displayBoard(Board *board);
void displayBoardWithPiece(Board *board, Piece *piece);
void clearCompletedRows(Board *board);
void freeBoard(Board *board);

#endif
