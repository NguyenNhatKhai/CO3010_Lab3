/*
 * input_button.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#include "input_button.h"

static uint16_t buttonPins[BUTTON_NUMBER] = {BUTTON_0_Pin, BUTTON_1_Pin, BUTTON_2_Pin, BUTTON_3_Pin};

static GPIO_PinState buttonStates[BUTTON_NUMBER];
static GPIO_PinState buttonDebounce0[BUTTON_NUMBER];
static GPIO_PinState buttonDebounce1[BUTTON_NUMBER];
static GPIO_PinState buttonDebounce2[BUTTON_NUMBER];

static uint8_t buttonFlags[BUTTON_NUMBER];
static int16_t buttonCounters[BUTTON_NUMBER];

void buttonReading(void) {
	for (int i = 0; i < BUTTON_NUMBER; i ++) {
		buttonDebounce2[i] = buttonDebounce1[i];
		buttonDebounce1[i] = buttonDebounce0[i];
		buttonDebounce0[i] = HAL_GPIO_ReadPin(GPIOB, buttonPins[i]);
		if ((buttonDebounce0[i] == buttonDebounce1[i]) && (buttonDebounce0[i] == buttonDebounce2[i])) {
			if (buttonStates[i] != buttonDebounce0[i]) {
				buttonStates[i] = buttonDebounce0[i];
				if (buttonStates[i] == BUTTON_PRESSED) {
					buttonFlags[i] = 1;
					buttonCounters[i] = BUTTON_PRESSED_DURATION / TIMER_DURATION;
				}
			}
			else {
				if (buttonStates[i] == BUTTON_PRESSED) {
					buttonCounters[i] --;
					if (buttonCounters[i] <= 0) {
						buttonFlags[i] = 1;
						buttonCounters[i] = BUTTON_HOLDING_DURATION / TIMER_DURATION;
					}
				}
			}
		}
	}
}

int buttonPressed(int index) {
	if (index < 0 || index >= BUTTON_NUMBER) return 0;
	if (buttonFlags[index] == 1) {
		buttonFlags[index] = 0;
		return 1;
	}
	return 0;
}
