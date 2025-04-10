/*
 * screens.h
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */

#ifndef INC_SCREENS_H_
#define INC_SCREENS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "LCD_Driver.h"
#include "draw.h"
#include "game.h"

extern uint16_t activeScreen;

void shadingDemo();

void showStartScreen();
bool startClicked(uint16_t x, uint16_t y);

void showGameScreen();

void showEndScreen();

#endif /* INC_SCREENS_H_ */
