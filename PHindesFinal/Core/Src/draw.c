/*
 * draw.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#include "draw.h"


void Draw_Arrow_Up(uint16_t Xcenter, uint16_t Ytop, uint16_t size, uint16_t color)
{
    // Draw the shaft
    for (int i = 0; i < size; i++) {
        LCD_Draw_Pixel(Xcenter, Ytop + i, color);
    }

    // Draw the arrowhead
    for (int i = 0; i < size / 2; i++) {
        LCD_Draw_Pixel(Xcenter - i, Ytop + i, color); // Left diagonal
        LCD_Draw_Pixel(Xcenter + i, Ytop + i, color); // Right diagonal
    }
}

void Draw_Arrow_Down(uint16_t Xcenter, uint16_t Ytop, uint16_t size, uint16_t color)
{
    // Draw the shaft (vertical line)
    for (int i = 0; i < size; i++) {
        LCD_Draw_Pixel(Xcenter, Ytop + i, color);
    }

    // Draw the arrowhead (ensure it fits within the shaft)
    for (int i = 0; i < size / 2; i++) {
        LCD_Draw_Pixel(Xcenter + i, Ytop - i + size, color); // Left diagonal
        LCD_Draw_Pixel(Xcenter - i, Ytop - i + size, color); // Right diagonal
    }
}

void Draw_Arrow_Left(uint16_t Xleft, uint16_t Ycenter, uint16_t size, uint16_t color)
{
    // Draw the shaft
    for (int i = 0; i < size; i++) {
        LCD_Draw_Pixel(Xleft + i, Ycenter, color);
    }

    // Draw the arrowhead
    for (int i = 0; i < size / 2; i++) {
        LCD_Draw_Pixel(Xleft + i, Ycenter - i, color); // Top diagonal
        LCD_Draw_Pixel(Xleft + i, Ycenter + i, color); // Bottom diagonal
    }
}

void Draw_Arrow_Right(uint16_t Xright, uint16_t Ycenter, uint16_t size, uint16_t color)
{
    // Draw the shaft
    for (int i = 0; i < size; i++) {
        LCD_Draw_Pixel(Xright - i, Ycenter, color);
    }

    // Draw the arrowhead
    for (int i = 0; i < size / 2; i++) {
        LCD_Draw_Pixel(Xright - i, Ycenter - i, color); // Top diagonal
        LCD_Draw_Pixel(Xright - i, Ycenter + i, color); // Bottom diagonal
    }
}

#define arrowSize 20
#define arrowColor LCD_COLOR_WHITE
#define activeArrowColor LCD_COLOR_GREEN
void Draw_Arrows_On_Screen(uint8_t activeArrow) {

    Draw_Arrow_Up(LCD_PIXEL_WIDTH / 2, 10, arrowSize, activeArrow == 0 ? activeArrowColor : arrowColor);
    Draw_Arrow_Right(LCD_PIXEL_WIDTH - 10, LCD_PIXEL_HEIGHT / 2, arrowSize, activeArrow == 1 ? activeArrowColor : arrowColor);
    Draw_Arrow_Down(LCD_PIXEL_WIDTH / 2, LCD_PIXEL_HEIGHT - arrowSize - 10, arrowSize, activeArrow == 2 ? activeArrowColor : arrowColor);
    Draw_Arrow_Left(10, LCD_PIXEL_HEIGHT / 2, arrowSize, activeArrow == 3 ? activeArrowColor : arrowColor);
}

void Draw_Tetris_Block(uint16_t Xpos, uint16_t Ypos, uint16_t size, uint16_t mainColor, uint16_t brightColor, uint16_t darkColor)
{
    uint16_t shadingThickness = size / 6; // Thickness of the shading

    // 1. Draw the main square
    LCD_Draw_Rectangle_Fill(Xpos, Ypos, size, size, mainColor);

    // 2. Draw the top bright rectangle
    LCD_Draw_Rectangle_Fill(Xpos, Ypos, size, shadingThickness, brightColor);

    // 3. Draw the left bright rectangle
    LCD_Draw_Rectangle_Fill(Xpos, Ypos, shadingThickness, size, brightColor);

    // 4. Draw the bottom dark rectangle
    LCD_Draw_Rectangle_Fill(Xpos, Ypos + size - shadingThickness, size, shadingThickness, darkColor);

    // 5. Draw the right dark rectangle
    LCD_Draw_Rectangle_Fill(Xpos + size - shadingThickness, Ypos, shadingThickness, size, darkColor);

    // 6. Draw the bottom-left bright triangle
    Draw_BottomLeft_to_TopRight_Triangle_Fill(Xpos, Ypos + size - 1, shadingThickness, brightColor);

    // 7. Draw the top-right bright triangle
    Draw_BottomLeft_to_TopRight_Triangle_Fill(Xpos + size - shadingThickness, Ypos + shadingThickness - 1, shadingThickness, brightColor);
}

void Fill_Tetris_Board(Board *board, uint16_t startX, uint16_t startY)
{
    for (uint16_t row = 0; row < BOARD_HEIGHT; row++) {
        for (uint16_t col = 0; col < BOARD_WIDTH; col++) {
            // Calculate the position of the current block
            uint16_t xPos = startX + col * BLOCK_SIZE + col;
            uint16_t yPos = startY - row * BLOCK_SIZE + row; // Bottom-up positioning

            // Get the colors for this position
            int index = board->grid[row][col];
            if (index != 0){
				uint16_t * colors = piceIndexToColors(index);

				// Draw the Tetris block
				Draw_Tetris_Block(xPos, yPos, BLOCK_SIZE, colors[0], colors[1], colors[2]);
            }
        }
    }
}

void LCD_Draw_Rounded_Rectangle_Fill(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint16_t radius, uint16_t color) {
    // Draw central rectangle
    LCD_Draw_Rectangle_Fill(x + radius, y + radius, width - 2 * radius, height - 2 * radius, color);

    // Draw top and bottom rectangles
    LCD_Draw_Rectangle_Fill(x + radius, y, width - 2 * radius, radius, color); // Top
    LCD_Draw_Rectangle_Fill(x + radius, y + height - radius, width - 2 * radius, radius, color); // Bottom

    // Draw left and right rectangles
    LCD_Draw_Rectangle_Fill(x, y + radius, radius, height - 2 * radius, color); // Left
    LCD_Draw_Rectangle_Fill(x + width - radius, y + radius, radius, height - 2 * radius, color); // Right

    // Draw corner circles
    LCD_Draw_Circle_Fill(x + radius, y + radius, radius, color);                  // Top-left
    LCD_Draw_Circle_Fill(x + width - radius, y + radius, radius, color);         // Top-right
    LCD_Draw_Circle_Fill(x + radius, y + height - radius, radius, color);        // Bottom-left
    LCD_Draw_Circle_Fill(x + width - radius, y + height - radius, radius, color);// Bottom-right
}

