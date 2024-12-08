/*
 * screens.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#include "screens.h"

uint16_t activeScreen = 0;

#define BORDER_GAP 30
#define START_AREA_X_LEN (LCD_PIXEL_WIDTH - BORDER_GAP *2)
#define START_AREA_Y_LEN (24*2)
#define START_AREA_X BORDER_GAP
#define START_AREA_Y (LCD_PIXEL_HEIGHT - START_AREA_Y_LEN - BORDER_GAP)

void showStartScreen(){
	LCD_Clear(0, LCD_COLOR_BLACK);

	LCD_SetFont(&Font16x24);

//	Draw_Tetris_Block(40, 40, 20, 0x0679, 0x07FF, 0x04D3);
	DrawTetrominoByIndex(0, 20, 40);
	DrawTetrominoByIndex(1, 20, 70);
	DrawTetrominoByIndex(2, 90, 40);
	DrawTetrominoByIndex(3, 140, 40);
	DrawTetrominoByIndex(4, 65, 80);
	DrawTetrominoByIndex(5, 100, 80);

	DrawTetrominoByIndex(6, 50, 140);
	LCD_SetTextColor(LCD_COLOR_MAGENTA);
	LCD_DisplayString(100, 152, "ETRIS");

	// Start Button
//	LCD_Draw_Rectangle_Fill(START_AREA_X, START_AREA_Y, START_AREA_X_LEN, START_AREA_Y_LEN, LCD_COLOR_GREEN);
	LCD_Draw_Rounded_Rectangle_Fill(START_AREA_X, START_AREA_Y, START_AREA_X_LEN, START_AREA_Y_LEN, 15, LCD_COLOR_GREEN);

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_DisplayString(START_AREA_X + BORDER_GAP + 24, START_AREA_Y + BORDER_GAP /2, "Start");
}

bool startClicked(uint16_t x, uint16_t y) {
	return (x >= START_AREA_X && x <= (START_AREA_X + START_AREA_X_LEN) && y >= START_AREA_Y && y <= (START_AREA_Y + START_AREA_Y_LEN));
}

void showGameScreen(){
	// Game Board
	Board shownBoard = boardWithPiece(& board, & currentPiece);
	Fill_Tetris_Board(
			& shownBoard,
			LCD_PIXEL_WIDTH /2 - BOARD_WIDTH*(BLOCK_SIZE + 1)/2 ,
			50
			);

	// Next Piece
//	DrawTetromino(& nextPiece, 130, 10);
}

void showEndScreen(){

}
