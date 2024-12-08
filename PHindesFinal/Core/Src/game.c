/*
 * game.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#include "game.h"

Board board;
Piece currentPiece;
Piece nextPiece;

void initGame() {
	initializeBoard(& board);
	initializeRandomPiece(& currentPiece);
	initializeRandomPiece(& nextPiece);
	board.grid[0][0] = 6;
	board.grid[0][1] = 2;
	board.grid[1][0] = 5;
}

bool movePieceDown(Board *board, Piece *piece) {
    piece->y++;
    if (collision(board, piece)) {
        piece->y--;
        return false;
    }
    return true;
}

void lockPiece(Board *board, Piece *piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piece->matrix[i][j]) {
                int x = piece->x + j;
                int y = piece->y + i;
                if (y >= 0 && y < BOARD_HEIGHT && x >= 0 && x < BOARD_WIDTH) {
                    board->grid[y][x] = piece->matrix[i][j];
                }
            }
        }
    }
    currentPiece = nextPiece;
    initializeRandomPiece( & nextPiece);
}

bool collision(Board *board, Piece *piece) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (piece->matrix[i][j]) {
                int x = piece->x + j;
                int y = piece->y + i;

                if (x < 0 || x >= BOARD_WIDTH || y >= BOARD_HEIGHT) {
                    return true;
                }

                if (y >= 0 && board->grid[y][x]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void rotatePiece(Piece *piece) {
    int tempMatrix[4][4] = {0};

    // Transpose and reverse rows to achieve 90-degree clockwise rotation
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            tempMatrix[j][3 - i] = piece->matrix[i][j];
        }
    }

    // Manually copy tempMatrix to piece->matrix
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            piece->matrix[i][j] = tempMatrix[i][j];
        }
    }
}

void dropPiece(Board *board, Piece *piece) {
    while (movePieceDown(board, piece)) {
    }
    lockPiece(board, piece);
}

void handleInput(Board *board, Piece *piece, uint8_t command) {
    switch (command) {
        case 3: // Move left
            piece->x--;
            break;
        case 1: // Move right
            piece->x++;
            break;
        case 0: // Rotate
            rotatePiece(piece);
            if (collision(board, piece)) {
                // Undo rotation if collision occurs
                for (int i = 0; i < 3; i++) {
                    rotatePiece(piece);
                }
            }
            break;
        case 2: // Soft drop
            if (!movePieceDown(board, piece)){
            	lockPiece(board, piece);
            }
            break;
        case 4: // Hard drop
            dropPiece(board, piece);
            break;
    }

    // Undo move if collision detected
    if (collision(board, piece)) {
        switch (command) {
            case 3: piece->x++; break;
            case 1: piece->x--; break;
        }
    }
}

bool isGameOver(Board *board) {
    for (int i = 0; i < BOARD_WIDTH; i++) {
        if (board->grid[0][i] != 0) {
            return true;
        }
    }
    return false;
}

