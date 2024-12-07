#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "pieces.h"
#include <stdbool.h>

bool movePieceDown(Board *board, Piece *piece);
void lockPiece(Board *board, Piece *piece);
bool collision(Board *board, Piece *piece);
void handleInput(Board *board, Piece *piece, char command);
bool isGameOver(Board *board);
void rotatePiece(Piece *piece);
void dropPiece(Board *board, Piece *piece);

#endif
