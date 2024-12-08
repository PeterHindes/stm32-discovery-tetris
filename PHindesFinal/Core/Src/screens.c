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
	LCD_Clear(0, LCD_COLOR_MAGENTA);

	Draw_Tetris_Block(40, 40, 20, 0x0679, 0x07FF, 0x04D3);

	// Start Button
//	LCD_Draw_Rectangle_Fill(START_AREA_X, START_AREA_Y, START_AREA_X_LEN, START_AREA_Y_LEN, LCD_COLOR_GREEN);
	LCD_Draw_Rounded_Rectangle_Fill(START_AREA_X, START_AREA_Y, START_AREA_X_LEN, START_AREA_Y_LEN, 20, LCD_COLOR_GREEN);

	LCD_SetTextColor(LCD_COLOR_BLACK);
	LCD_SetFont(&Font16x24);
	LCD_DisplayString(START_AREA_X + BORDER_GAP + 10, START_AREA_Y + BORDER_GAP /2, "Start Game");
}

bool startClicked(uint16_t x, uint16_t y) {
	return (x >= START_AREA_X && x <= (START_AREA_X + START_AREA_X_LEN) && y >= START_AREA_Y && y <= (START_AREA_Y + START_AREA_Y_LEN));
}
