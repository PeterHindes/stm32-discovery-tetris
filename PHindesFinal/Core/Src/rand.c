/*
 * rand.c
 *
 *  Created on: Dec 7, 2024
 *      Author: user
 */
#include "rand.h"
RNG_HandleTypeDef rng;
void initRng(RNG_HandleTypeDef hrng){
	rng=hrng;
}

uint32_t rand(){
	return rng.RandomNumber;
}
