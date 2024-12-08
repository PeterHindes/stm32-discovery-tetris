/*
 * game.h
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#ifndef INC_GAME_H_
#define INC_GAME_H_

#include "gameBoard.h"
#include "pieces.h"
#include <stdbool.h>
#include <string.h>

extern Board board;
extern Piece currentPiece;
extern Piece nextPiece;

void initGame();
bool movePieceDown(Board *board, Piece *piece);
void lockPiece(Board *board, Piece *piece);
bool collision(Board *board, Piece *piece);
void handleInput(Board *board, Piece *piece, uint8_t command);
bool isGameOver(Board *board);
void rotatePiece(Piece *piece);
void dropPiece(Board *board, Piece *piece);


#endif /* INC_GAME_H_ */
