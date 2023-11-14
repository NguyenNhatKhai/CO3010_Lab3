/*
 * output_led7seg.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#include "output_led7seg.h"

int led7segNumbers[LED7SEG_BLOCK_NUMBER] = {0};

static int led7segIndex = 0;
static int led7segOffset = 0;
static uint16_t led7segPins[LED7SEG_NUMBER] = {LED7SEG_0_Pin, LED7SEG_1_Pin, LED7SEG_2_Pin, LED7SEG_3_Pin};

static uint16_t led7segNum0s[11] = {0xBF, 0x86, 0xDB, 0xCF, 0xE6, 0xED, 0xFD, 0x87, 0xFF, 0xEF, 0x00};
static uint16_t led7segNum1s[11] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10, 0xFF};

static void led7segDisplay(int index, int offset) {
	if (index < 0 || index >= LED7SEG_BLOCK_NUMBER) return;
	if (offset < 0 || offset >= LED7SEG_DIGIT_NUMBER) return;
	int num = led7segNumbers[index] / (int)pow(10, LED7SEG_DIGIT_NUMBER - offset - 1) % 10;
	if (num >= 0 && num <= 9) {
		GPIOA->BSRR = led7segNum1s[num] << 8;
		GPIOA->BSRR = led7segNum0s[num] << (8 + 16);
	}
	else {
		GPIOA->BSRR = led7segNum1s[10] << 8;
		GPIOA->BSRR = led7segNum0s[10] << (8 + 16);
	}
	switch (index * LED7SEG_BLOCK_NUMBER + offset) {
	case 0:
		HAL_GPIO_WritePin(GPIOB, led7segPins[0], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[1], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[2], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[3], GPIO_PIN_SET);
		break;
	case 1:
		HAL_GPIO_WritePin(GPIOB, led7segPins[0], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[1], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[2], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[3], GPIO_PIN_SET);
		break;
	case 2:
		HAL_GPIO_WritePin(GPIOB, led7segPins[0], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[1], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[2], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[3], GPIO_PIN_SET);
		break;
	case 3:
		HAL_GPIO_WritePin(GPIOB, led7segPins[0], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[1], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[2], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, led7segPins[3], GPIO_PIN_RESET);
		break;
	default:
		break;
	}
}

void led7segInit(void) {
	timerSet(LED7SEG_SCANNING_DURATION / TIMER_DURATION, 0);
	HAL_GPIO_WritePin(GPIOB, led7segPins[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, led7segPins[1], GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, led7segPins[2], GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOB, led7segPins[3], GPIO_PIN_SET);
}

void led7segUpdate(int num, int index) {
	if (num < 0 || num >= pow(10, LED7SEG_DIGIT_NUMBER) || index < 0 || index >= LED7SEG_BLOCK_NUMBER) return;
	led7segNumbers[index] = num;
}

void led7segScanning(void) {
	led7segDisplay(led7segIndex, led7segOffset);
	if (timerFlags[0] == 1) {
		timerSet(LED7SEG_SCANNING_DURATION / TIMER_DURATION, 0);
		led7segOffset ++;
		if (led7segOffset >= LED7SEG_DIGIT_NUMBER) {
			led7segOffset = 0;
			led7segIndex ++;
		}
		if (led7segIndex >= LED7SEG_BLOCK_NUMBER) {
			led7segIndex = 0;
		}
	}
}

