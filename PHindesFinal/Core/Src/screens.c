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

void shadingDemo(){
	LCD_Clear(0, LCD_COLOR_BLACK);

	Draw_Tetris_Block(40,40,80,0xCB20, 0xFC40, 0x9A20);
}
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

void uint32_to_string(uint32_t value, char *buffer, size_t buffer_size) {
    // Ensure the buffer is large enough to hold the maximum uint32_t value and a null terminator
    if (buffer_size < 11) {
        // Handle error: buffer too small
        return;
    }
    // Format the uint32_t value as a string and store it in the buffer
    snprintf(buffer, buffer_size, "%u", (unsigned int) value);
}

void showGameScreen(){
	LCD_SetFont(&Font16x24);
	LCD_SetTextColor(LCD_COLOR_WHITE);

	// Game Board
	Board shownBoard = boardWithPiece(& board, & currentPiece);
	Fill_Tetris_Board(
			& shownBoard,
			LCD_PIXEL_WIDTH /2 - BOARD_WIDTH*(BLOCK_SIZE + 1)/2 ,
			BLOCK_SIZE + 10
			);

	// Next Piece
	DrawTetromino(& nextPiece, 190, 10);

	// Score
	char scoreStr[11];
	uint32_to_string(pointsScored,(char *)&scoreStr,11);
	LCD_DisplayString(10,10,scoreStr);
}

void showEndScreen(){
	LCD_SetFont(&Font16x24);
	LCD_SetTextColor(LCD_COLOR_WHITE);

	LCD_Clear(0,0x2800); // DARK RED
	char scoreStr[11];
	uint32_to_string(pointsScored,(char *)&scoreStr,11);
	LCD_DisplayString(10,200,scoreStr);
	LCD_DisplayString(10,170,"You Scored:");

	LCD_DisplayString(10,10,"You Lasted:");
	uint32_t timeLasted = __HAL_TIM_GET_COUNTER(&htim5)/5000;
	uint32_t timeLastedSec = timeLasted % 60;
	uint32_t timeLastedMin = timeLasted / 60;
	uint32_t timeLastedHour = (timeLasted / 60) / 60;

	uint32_to_string(timeLastedHour, (char *)&scoreStr,11);
	LCD_DisplayString(40,40,scoreStr);
	LCD_DisplayChar(10,40,'H');
	uint32_to_string(timeLastedMin, (char *)&scoreStr,11);
	LCD_DisplayString(40,70,scoreStr);
	LCD_DisplayChar(10,70,'M');
	uint32_to_string(timeLastedSec, (char *)&scoreStr,11);
	LCD_DisplayString(40,100,scoreStr);
	LCD_DisplayChar(10,100,'S');
}
