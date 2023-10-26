/*
 * software_timer.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#include "software_timer.h"

uint8_t timerFlags[TIMER_NUMBER];
static int16_t timerCounters[TIMER_NUMBER];

void timerSet(int duration, int index) {
	if (index >= 0 && index < TIMER_NUMBER) {
		timerCounters[index] = duration;
		timerFlags[index] = 0;
	}
}

void timerRun() {
	for (int i = 0; i < TIMER_NUMBER; i ++) {
		if (timerCounters[i] > 0) {
			timerCounters[i] --;
			if (timerCounters[i] <= 0) {
				timerFlags[i] = 1;
			}
		}
	}
}
