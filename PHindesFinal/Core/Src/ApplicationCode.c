/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */


extern void initialise_monitor_handles(void); 

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#if TOUCH_INTERRUPT_ENABLED == 1
static EXTI_HandleTypeDef LCDTouchIRQ;
void LCDTouchScreenInterruptGPIOInit(void);
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
	initialise_monitor_handles(); // Allows printf functionality
    LTCD__Init();
    LTCD_Layer_Init(0);
    LCD_Clear(0,LCD_COLOR_WHITE);

    #if COMPILE_TOUCH_FUNCTIONS == 1
	InitializeLCDTouch();

	// This is the orientation for the board to be direclty up where the buttons are vertically above the screen
	// Top left would be low x value, high y value. Bottom right would be low x value, low y value.
	StaticTouchData.orientation = STMPE811_Orientation_Portrait_2;

	#if TOUCH_INTERRUPT_ENABLED == 1
	LCDTouchScreenInterruptGPIOInit();
	#endif // TOUCH_INTERRUPT_ENABLED

	#endif // COMPILE_TOUCH_FUNCTIONS
}

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


void LCD_Visual_Demo(void)
{
//	visualDemo();
	LCD_Clear(0, LCD_COLOR_BLACK);

	Board board;
	initializeBoard(& board);
	board.grid[0][0] = 6;
	board.grid[0][1] = 2;
	board.grid[1][0] = 5;

	Fill_Tetris_Board(
			& board,
			LCD_PIXEL_WIDTH /2 - BOARD_WIDTH*(BLOCK_SIZE + 1)/2 ,
			LCD_PIXEL_HEIGHT - 50
			);
	Draw_Arrows_On_Screen(-1);
}

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
			printf("Not Pressed\n\n");
			LCD_Clear(0, LCD_COLOR_GREEN);
		}
	}
}

uint8_t Determine_Touch_Quadrant(uint16_t x, uint16_t y, uint16_t screenWidth, uint16_t screenHeight)
{
    // Calculate center of the screen
    int16_t centerX = screenWidth / 2;
    int16_t centerY = screenHeight / 2;

    // Calculate relative position from the center
    int16_t relX = x - centerX;
    int16_t relY = centerY - y; // Invert Y-axis as screen Y grows downward

    // Determine the rotated quadrant based on diagonal boundaries
    if (relY > relX && relY > -relX) {
        return 0; // Up (Quadrant 1)
    } else if (relY <= relX && relY > -relX) {
        return 1; // Right (Quadrant 2)
    } else if (relY <= relX && relY <= -relX) {
        return 2; // Down (Quadrant 3)
    } else if (relY > relX && relY <= -relX) {
        return 3; // Left (Quadrant 4)
    }

    // Fallback (should not happen)
    return -1;
}

// TouchScreen Interrupt
#if TOUCH_INTERRUPT_ENABLED == 1

void LCDTouchScreenInterruptGPIOInit(void)
{
	GPIO_InitTypeDef LCDConfig = {0};
    LCDConfig.Pin = GPIO_PIN_15;
    LCDConfig.Mode = GPIO_MODE_IT_RISING_FALLING;
    LCDConfig.Pull = GPIO_NOPULL;
    LCDConfig.Speed = GPIO_SPEED_FREQ_HIGH;
    
    // Clock enable
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // GPIO Init
    HAL_GPIO_Init(GPIOA, &LCDConfig);

    // Interrupt Configuration
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	LCDTouchIRQ.Line = EXTI_LINE_15;
}

#define TOUCH_DETECTED_IRQ_STATUS_BIT   (1 << 0)  // Touchscreen detected bitmask

static uint8_t statusFlag;

void EXTI15_10_IRQHandler()
{
	HAL_NVIC_DisableIRQ(EXTI15_10_IRQn); // May consider making this a universial interrupt guard
	bool isTouchDetected = false;

	static uint32_t count;
	count = 0;
	while(count == 0){
		count = STMPE811_Read(STMPE811_FIFO_SIZE);
	}

	// Disable touch interrupt bit on the STMPE811
	uint8_t currentIRQEnables = ReadRegisterFromTouchModule(STMPE811_INT_EN);
	WriteDataToTouchModule(STMPE811_INT_EN, 0x00);

	// Clear the interrupt bit in the STMPE811
	statusFlag = ReadRegisterFromTouchModule(STMPE811_INT_STA);
	uint8_t clearIRQData = (statusFlag | TOUCH_DETECTED_IRQ_STATUS_BIT); // Write one to clear bit
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);
	
	uint8_t ctrlReg = ReadRegisterFromTouchModule(STMPE811_TSC_CTRL);
	if (ctrlReg & 0x80)
	{
		isTouchDetected = true;
	}

	// Determine if it is pressed or unpressed
	if(isTouchDetected) // Touch has been detected
	{
		printf("\nPressed");
		// May need to do numerous retries?
		DetermineTouchPosition(&StaticTouchData);
		/* Touch valid */
		printf("\nX: %03d\nY: %03d \n", StaticTouchData.x, StaticTouchData.y);
		LCD_Clear(0, LCD_COLOR_BLACK);

		Draw_Arrows_On_Screen(
			Determine_Touch_Quadrant(StaticTouchData.x,LCD_PIXEL_HEIGHT-StaticTouchData.y , LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT)
		);
	}else{
		/* Touch not pressed */
		printf("\nNot pressed \n");
//		DetermineTouchPosition(&StaticTouchData); // this dosent work here, just has old position
//		LCD_Clear(0, LCD_COLOR_GREEN);
//		LCD_Draw_Circle_Fill(StaticTouchData.x,LCD_PIXEL_HEIGHT-StaticTouchData.y,40,LCD_COLOR_BLACK);
	}

	STMPE811_Write(STMPE811_FIFO_STA, 0x01);
	STMPE811_Write(STMPE811_FIFO_STA, 0x00);

	// Re-enable IRQs
    WriteDataToTouchModule(STMPE811_INT_EN, currentIRQEnables);
	HAL_EXTI_ClearPending(&LCDTouchIRQ, EXTI_TRIGGER_RISING_FALLING);

	HAL_NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
	HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

	//Potential ERRATA? Clearing IRQ bit again due to an IRQ being triggered DURING the handling of this IRQ..
	WriteDataToTouchModule(STMPE811_INT_STA, clearIRQData);

}
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

