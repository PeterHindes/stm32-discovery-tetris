#include "pieces.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int TETROMINOS[7][4][4] = {
    {{1, 1, 1, 1}},             // I
    {{1, 1}, {1, 1}},           // O
    {{0, 1, 1}, {1, 1, 0}},     // S
    {{1, 1, 0}, {0, 1, 1}},     // Z
    {{1, 0}, {1, 0}, {1, 1}},   // L
    {{0, 1}, {0, 1}, {1, 1}},   // J
    {{0, 1, 0}, {1, 1, 1}},     // T
};

void initializeRandomPiece(Piece *piece) {
    int randomIndex = rand() % 7;
    memcpy(piece->matrix, TETROMINOS[randomIndex], sizeof(piece->matrix));
    piece->x = BOARD_WIDTH / 2 - 1;
    piece->y = 0;
}

void displayPiece(Piece *piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%d ", piece->matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
