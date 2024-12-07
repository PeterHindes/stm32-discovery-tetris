#ifndef PIECES_H
#define PIECES_H

#include "constants.h"

typedef struct {
    int matrix[4][4];
    int x, y;
} Piece;

void initializeRandomPiece(Piece *piece);
void displayPiece(Piece *piece);

#endif
