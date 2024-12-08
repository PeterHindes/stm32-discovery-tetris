/*
 * gameBoard.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#include "gameBoard.h"

void initializeBoard(Board *board) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            board->grid[i][j] = 0;
        }
    }
}

void clearCompletedRows(Board *board) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        int isComplete = 1;
        for (int j = 0; j < BOARD_WIDTH; j++) {
            if (board->grid[i][j] == 0) {
                isComplete = 0;
                break;
            }
        }

        if (isComplete) {
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
}

//void displayBoardWithPiece(Board *board, Piece *piece) {
//    int tempGrid[BOARD_HEIGHT][BOARD_WIDTH];
//
//    // Copy the board grid to a temporary grid
//    for (int i = 0; i < BOARD_HEIGHT; i++) {
//        for (int j = 0; j < BOARD_WIDTH; j++) {
//            tempGrid[i][j] = board->grid[i][j];
//        }
//    }
//
//    // Overlay the active piece onto the temporary grid
//    for (int pi = 0; pi < 4; pi++) {
//        for (int pj = 0; pj < 4; pj++) {
//            int px = piece->x + pj;
//            int py = piece->y + pi;
//
//            if (px >= 0 && px < BOARD_WIDTH && py >= 0 && py < BOARD_HEIGHT && piece->matrix[pi][pj] == 1) {
//                tempGrid[py][px] = piece->matrix[pi][pj];
//            }
//        }
//    }
//
//    // Display the temporary grid by calling out to the forign function in the pc module
//    Board tempBoard;
//    tempBoard.grid = tempGrid;
////    displayBoard(& tempBoard);
////	TODO implement
//}
