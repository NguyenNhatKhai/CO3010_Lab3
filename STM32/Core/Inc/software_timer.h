/*
 * software_timer.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "main.h"

#define TIMER_NUMBER 5
#define TIMER_DURATION 10

extern uint8_t timerFlags[TIMER_NUMBER];

void timerSet(int duration, int index);
void timerRun(void);

#endif /* INC_SOFTWARE_TIMER_H_ */
