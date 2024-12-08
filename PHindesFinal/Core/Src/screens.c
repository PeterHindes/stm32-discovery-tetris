/*
 * screens.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#include "screens.h"

#define BORDER_GAP 30
#define START_AREA_X_LEN (LCD_PIXEL_WIDTH - BORDER_GAP *2)
#define START_AREA_Y_LEN (24*2)
#define START_AREA_X BORDER_GAP
#define START_AREA_Y (LCD_PIXEL_HEIGHT - START_AREA_Y_LEN - BORDER_GAP)

void showStartScreen(){
	LCD_Clear(0, LCD_COLOR_BLACK);

	LCD_SetFont(&Font16x24);

//	Draw_Tetris_Block(40, 40, 20, 0x0679, 0x07FF, 0x04D3);
	DrawTetromino(0, 20, 40);
	DrawTetromino(1, 20, 70);
	DrawTetromino(2, 90, 40);
	DrawTetromino(3, 140, 40);
	DrawTetromino(4, 65, 80);
	DrawTetromino(5, 100, 80);

	DrawTetromino(6, 50, 140);
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
