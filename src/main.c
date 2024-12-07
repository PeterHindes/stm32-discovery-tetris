#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "pieces.h"
#include "game.h"
#include <stdbool.h>
#include "pc.h"

int main() {
    Board board;
    initializeBoard(&board);

    Piece currentPiece;
    initializeRandomPiece(&currentPiece);

    setup();

    bool exit = false;
    while (!isGameOver(&board) && !exit) {
        displayBoardWithPiece(&board, &currentPiece);

        exit = !handleInputAndTimeout(&board, &currentPiece);

        // Move the piece down every second
        if (!movePieceDown(&board, &currentPiece)) {
            lockPiece(&board, &currentPiece);
            clearCompletedRows(&board);
            initializeRandomPiece(&currentPiece);
        }
    }

    winddown();

    freeBoard(&board);
    return 0;
}
