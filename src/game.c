#include "game.h"
#include <stdbool.h>
#include <string.h>

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

    memcpy(piece->matrix, tempMatrix, sizeof(piece->matrix));
}

void dropPiece(Board *board, Piece *piece) {
    while (movePieceDown(board, piece)) {
    }
    lockPiece(board, piece);
}

void handleInput(Board *board, Piece *piece, char command) {
    switch (command) {
        case 'a': // Move left
            piece->x--;
            break;
        case 'd': // Move right
            piece->x++;
            break;
        case 'w': // Rotate
            rotatePiece(piece);
            if (collision(board, piece)) {
                // Undo rotation if collision occurs
                for (int i = 0; i < 3; i++) {
                    rotatePiece(piece);
                }
            }
            break;
        case 's': // Soft drop
            movePieceDown(board, piece);
            break;
        case ' ': // Hard drop
            dropPiece(board, piece);
            break;
    }

    // Undo move if collision detected
    if (collision(board, piece)) {
        switch (command) {
            case 'a': piece->x++; break;
            case 'd': piece->x--; break;
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
