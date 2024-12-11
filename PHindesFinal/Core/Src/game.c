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
uint32_t pointsScored;

void initGame() {
	initializeBoard(& board);
	initializeRandomPiece(& currentPiece);
	initializeRandomPiece(& nextPiece);
	pointsScored = 0;
}

bool movePieceDown(Board *board, Piece *piece) {
    piece->y++;
    if (collision(board, piece)) {
        piece->y--;
        lockPiece(board, piece);
        return false;
    }
    return true;
}
void dropPiece(Board *board, Piece *piece) {
    while (movePieceDown(board, piece)) {
    }
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

    if (isGameOver(board)){
    	showEndScreen();
    	Error_Handler();
    }


    currentPiece = nextPiece;
    initializeRandomPiece( & nextPiece);
    switch (clearCompletedRows(board)){
		case 4:
			pointsScored+=300;
		case 3:
			pointsScored+=200;
		case 2:
			pointsScored+=200;
		case 1:
			pointsScored+=100;
		case 0:
			break;
    }
}
uint16_t clearCompletedRows(Board *board) {
	uint16_t clearedRows = 0;
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        int isComplete = 1;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board->grid[i][j] == 0) {
                isComplete = 0;
                break;
            }
        }

        if (isComplete) {
            clearedRows++;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < BOARD_WIDTH; j++) {
                    board->grid[k][j] = board->grid[k - 1][j];
                }
            }

            for (int j = 0; j < BOARD_WIDTH; j++) {
                board->grid[0][j] = 0;
            }
        }
    }
    return clearedRows;
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
        	movePieceDown(board, piece);
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

