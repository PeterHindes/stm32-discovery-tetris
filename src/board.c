#include "board.h"
#include <stdio.h>
#include <stdlib.h>

void initializeBoard(Board *board) {
    board->grid = malloc(BOARD_HEIGHT * sizeof(int *));
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        board->grid[i] = calloc(BOARD_WIDTH, sizeof(int));
    }
}

void displayBoard(Board *board) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            printf("%d ", board->grid[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void displayBoardWithPiece(Board *board, Piece *piece) {
    system("clear");
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        for (int j = 0; j < BOARD_WIDTH; j++) {
            int value = board->grid[i][j]; // Base board value

            // Overlay the active piece
            for (int pi = 0; pi < 4; pi++) {
                for (int pj = 0; pj < 4; pj++) {
                    int px = piece->x + pj;
                    int py = piece->y + pi;

                    if (pi + piece->y == i && pj + piece->x == j && piece->matrix[pi][pj] == 1) {
                        value = piece->matrix[pi][pj];
                    }
                }
            }

            printf("%d ", value);
        }
        printf("\n");
    }
    printf("\n");
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

void freeBoard(Board *board) {
    for (int i = 0; i < BOARD_HEIGHT; i++) {
        free(board->grid[i]);
    }
    free(board->grid);
}
