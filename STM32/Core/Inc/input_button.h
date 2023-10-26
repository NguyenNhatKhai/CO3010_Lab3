/*
 * input_button.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#ifndef INC_INPUT_BUTTON_H_
#define INC_INPUT_BUTTON_H_

#include "main.h"
#include "software_timer.h"

#define BUTTON_NUMBER 4
#define BUTTON_PRESSED_DURATION 1000
#define BUTTON_HOLDING_DURATION 500
#define BUTTON_PRESSED GPIO_PIN_RESET
#define BUTTON_RELEASED GPIO_PIN_SET

void buttonReading(void);
int buttonPressed(int index);

#endif /* INC_INPUT_BUTTON_H_ */
