/*
 * rand.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */
#include "rand.h"
uint32_t rand(){
	uint32_t rand;
	HAL_RNG_GenerateRandomNumber(& hrng, &rand);
	return rand;
}
