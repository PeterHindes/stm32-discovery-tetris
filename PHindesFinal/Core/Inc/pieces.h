/*
 * pieces.h
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#ifndef INC_PIECES_H_
#define INC_PIECES_H_

#include "constants.h"
#include <stdint.h>
#include "rand.h"

typedef struct {
    int matrix[4][4];
    int x, y;
//    uint16_t color, lightColor, darkColor;
} Piece;

void initializeRandomPiece(Piece *piece);
uint16_t * piceIndexToColors(int index);

#endif /* INC_PIECES_H_ */