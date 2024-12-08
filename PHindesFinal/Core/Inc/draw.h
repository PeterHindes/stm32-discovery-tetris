/*
 * draw.h
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#ifndef INC_DRAW_H_
#define INC_DRAW_H_

#include "gameBoard.h"
#include "LCD_Driver.h"
#include <stdint.h>
#include <stdbool.h>

void Draw_Tetris_Block(uint16_t Xpos, uint16_t Ypos, uint16_t size, uint16_t mainColor, uint16_t brightColor, uint16_t darkColor);
void Draw_Arrows_On_Screen(uint8_t activeArrow);
void Fill_Tetris_Board(Board *board, uint16_t startX, uint16_t startY);
void LCD_Draw_Rounded_Rectangle_Fill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t color);
void DrawTetromino(Piece * piece, uint16_t startX, uint16_t startY);
void DrawTetrominoByIndex(uint8_t pieceNumber, uint16_t startX, uint16_t startY);

#endif /* INC_DRAW_H_ */
