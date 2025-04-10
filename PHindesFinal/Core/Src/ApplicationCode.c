/*
 * ApplicationCode.c
 *
 *  Created on: Dec 30, 2023 (updated 11/12/2024) Thanks Donavon! 
 *      Author: Xavion
 */

#include "ApplicationCode.h"

/* Static variables */


//extern void initialise_monitor_handles(void);

#if COMPILE_TOUCH_FUNCTIONS == 1
static STMPE811_TouchData StaticTouchData;
#if TOUCH_INTERRUPT_ENABLED == 1
static EXTI_HandleTypeDef LCDTouchIRQ;
void LCDTouchScreenInterruptGPIOInit(void);
#endif // TOUCH_INTERRUPT_ENABLED
#endif // COMPILE_TOUCH_FUNCTIONS

void ApplicationInit(void)
{
//	initialise_monitor_handles(); // Allows printf functionality
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

#if COMPILE_TOUCH_FUNCTIONS == 1
void LCD_Touch_Polling_Demo(void)
{
	LCD_Clear(0,LCD_COLOR_GREEN);
	while (1) {
		/* If touch pressed */
		if (returnTouchStateAndLocation(&StaticTouchData) == STMPE811_State_Pressed) {
			/* Touch valid */
#if USEDEBUG == 1
			printf("\nX: %03d\nY: %03d\n", StaticTouchData.x, StaticTouchData.y);
#endif
			LCD_Clear(0, LCD_COLOR_RED);
		} else {
			/* Touch not pressed */
#if USEDEBUG == 1
			printf("Not Pressed\n\n");
#endif
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
		// May need to do numerous retries?
		DetermineTouchPosition(&StaticTouchData);
//		printf("\nPressed\nX: %03d\nY: %03d \n", StaticTouchData.x, StaticTouchData.y);
//		printf("Tim: %u", __HAL_TIM_GET_COUNTER(&htim2));

		if (activeScreen == 0) {
			if (startClicked(StaticTouchData.x, LCD_PIXEL_HEIGHT-StaticTouchData.y)){
				LCD_SetTextColor(LCD_COLOR_WHITE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayString(30,190, "Starting...");
#if USEDEBUG == 1
				printf("Starting...\n");
#endif
//				HAL_Delay(200);
				activeScreen = 1;
				initGame();
//				HAL_Delay(2);
				LCD_Clear(0, LCD_COLOR_BLACK);
				showGameScreen();
				Draw_Arrows_On_Screen(-1);

//				HAL_TIM_Base_Start_IT(& htim2);
//			    HAL_TIM_Base_Start(& htim5);
			    startTimers();
#if USEDEBUG == 1
			    printf("Started Timers\n");
#endif
			}
		} else if (activeScreen == 1) {
			LCD_Clear(0, LCD_COLOR_BLACK);

			uint8_t activeArrow = Determine_Touch_Quadrant(StaticTouchData.x,LCD_PIXEL_HEIGHT-StaticTouchData.y , LCD_PIXEL_WIDTH, LCD_PIXEL_HEIGHT);
			Draw_Arrows_On_Screen(activeArrow);

//			currentPiece = nextPiece;
//			initializeRandomPiece( & nextPiece);

			if (activeArrow == 2){
				if (tim2CallCounter >= 3){
					tim2CallCounter = 0;
					__HAL_TIM_SET_COUNTER(&htim2, 0);
				} else {
					activeArrow = -1;
				}

			}
			handleInput(& board, & currentPiece, activeArrow);

			showGameScreen();
			Draw_Arrows_On_Screen(activeArrow);
		}
	} else {
		/* Touch not pressed */
		if (activeScreen == 1) {
			Draw_Arrows_On_Screen(-1);
		}
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

