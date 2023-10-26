/*
 * output_led7seg.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#ifndef INC_OUTPUT_LED7SEG_H_
#define INC_OUTPUT_LED7SEG_H_

#include "main.h"
#include "math.h"
#include "software_timer.h"

#define LED7SEG_NUMBER 4
#define LED7SEG_BLOCK_NUMBER 2
#define LED7SEG_DIGIT_NUMBER LED7SEG_NUMBER / LED7SEG_BLOCK_NUMBER
#define LED7SEG_SCANNING_DURATION 250

extern int led7segNumbers[LED7SEG_BLOCK_NUMBER];

void led7segInit(void);
void led7segScanning(void);

#endif /* INC_OUTPUT_LED7SEG_H_ */
