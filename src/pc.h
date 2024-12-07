#ifndef PC_H
#define PC_H

#include <stdbool.h>
#include <sys/time.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include "board.h"
#include "pieces.h"

void disableRawMode();
void setup();
void winddown();
bool handleInputAndTimeout(Board *board, Piece *piece);

#endif