/*
 * processing_fsm.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#include "processing_fsm.h"

enum FSM_STATE fsmState = 0;

void fsmInit(void) {
	trafficInit();
	fsmReInit(FSM_NORMAL);
}

void fsmReInit(enum FSM_STATE state) {
	switch (state) {
	case FSM_NORMAL:
		timerSet(TRAFFIC_SECOND_DURATION / TIMER_DURATION, 1);
		timerSet(trafficRedDuration * TRAFFIC_SECOND_DURATION / TIMER_DURATION, 2);
		timerSet(trafficGreenDuration * TRAFFIC_SECOND_DURATION / TIMER_DURATION, 3);
		led7segNumbers[0] = trafficRedDuration;
		led7segNumbers[1] = trafficGreenDuration;
		trafficReInit(TRAFFIC_RED, 0);
		trafficReInit(TRAFFIC_GREEN, 1);
		fsmState = FSM_NORMAL;
		break;
	case FSM_RED_MOD:
		timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
		led7segNumbers[0] = 2;
		led7segNumbers[1] = trafficRedDuration;
		trafficReInit(TRAFFIC_OFF, 0);
		trafficReInit(TRAFFIC_OFF, 1);
		fsmState = FSM_RED_MOD;
		break;
	case FSM_AMBER_MOD:
		timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
		led7segNumbers[0] = 3;
		led7segNumbers[1] = trafficAmberDuration;
		trafficReInit(TRAFFIC_OFF, 0);
		trafficReInit(TRAFFIC_OFF, 1);
		fsmState = FSM_AMBER_MOD;
		break;
	case FSM_GREEN_MOD:
		timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
		led7segNumbers[0] = 4;
		led7segNumbers[1] = trafficGreenDuration;
		trafficReInit(TRAFFIC_OFF, 0);
		trafficReInit(TRAFFIC_OFF, 1);
		fsmState = FSM_GREEN_MOD;
		break;
	default:
		break;
	}
}

void fsmProcessing(void) {
	switch (fsmState) {
	case FSM_NORMAL:
		if (timerFlags[1] == 1) {
			timerSet(TRAFFIC_SECOND_DURATION / TIMER_DURATION, 1);
			led7segNumbers[0] --;
			if (led7segNumbers[0] < 0) {
				led7segNumbers[0] = 0;
			}
			led7segNumbers[1] --;
			if (led7segNumbers[1] < 0) {
				led7segNumbers[1] = 0;
			}
		}
		if (timerFlags[2] == 1) {
			switch (trafficState[0]) {
			case TRAFFIC_RED:
				timerSet(trafficGreenDuration * TRAFFIC_SECOND_DURATION / TIMER_DURATION, 2);
				led7segNumbers[0] = trafficGreenDuration;
				trafficReInit(TRAFFIC_GREEN, 0);
				break;
			case TRAFFIC_AMBER:
				timerSet(trafficRedDuration * TRAFFIC_SECOND_DURATION / TIMER_DURATION, 2);
				led7segNumbers[0] = trafficRedDuration;
				trafficReInit(TRAFFIC_RED, 0);
				break;
			case TRAFFIC_GREEN:
				timerSet(trafficAmberDuration * TRAFFIC_SECOND_DURATION / TIMER_DURATION, 2);
				led7segNumbers[0] = trafficAmberDuration;
				trafficReInit(TRAFFIC_AMBER, 0);
				break;
			default:
				break;
			}
		}
		if (timerFlags[3] == 1) {
			switch (trafficState[1]) {
			case TRAFFIC_RED:
				timerSet(trafficGreenDuration * TRAFFIC_SECOND_DURATION / TIMER_DURATION, 3);
				led7segNumbers[1] = trafficGreenDuration;
				trafficReInit(TRAFFIC_GREEN, 1);
				break;
			case TRAFFIC_AMBER:
				timerSet(trafficRedDuration * TRAFFIC_SECOND_DURATION / TIMER_DURATION, 3);
				led7segNumbers[1] = trafficRedDuration;
				trafficReInit(TRAFFIC_RED, 1);
				break;
			case TRAFFIC_GREEN:
				timerSet(trafficAmberDuration * TRAFFIC_SECOND_DURATION / TIMER_DURATION, 3);
				led7segNumbers[1] = trafficAmberDuration;
				trafficReInit(TRAFFIC_AMBER, 1);
				break;
			default:
				break;
			}
		}
		if (buttonPressed(0)) {
			fsmReInit(FSM_RED_MOD);
		}
		break;
	case FSM_RED_MOD:
		if (timerFlags[1] == 1) {
			switch (trafficState[0]) {
			case TRAFFIC_OFF:
				timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
				trafficReInit(TRAFFIC_RED, 0);
				trafficReInit(TRAFFIC_RED, 1);
				break;
			case TRAFFIC_RED:
				timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
				trafficReInit(TRAFFIC_OFF, 0);
				trafficReInit(TRAFFIC_OFF, 1);
				break;
			default:
				break;
			}
		}
		if (buttonPressed(0)) {
			fsmReInit(FSM_AMBER_MOD);
		}
		break;
	case FSM_AMBER_MOD:
		if (timerFlags[1] == 1) {
			switch (trafficState[0]) {
			case TRAFFIC_OFF:
				timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
				trafficReInit(TRAFFIC_AMBER, 0);
				trafficReInit(TRAFFIC_AMBER, 1);
				break;
			case TRAFFIC_AMBER:
				timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
				trafficReInit(TRAFFIC_OFF, 0);
				trafficReInit(TRAFFIC_OFF, 1);
				break;
			default:
				break;
			}
		}
		if (buttonPressed(0)) {
			fsmReInit(FSM_GREEN_MOD);
		}
		break;
	case FSM_GREEN_MOD:
		if (timerFlags[1] == 1) {
			switch (trafficState[0]) {
			case TRAFFIC_OFF:
				timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
				trafficReInit(TRAFFIC_GREEN, 0);
				trafficReInit(TRAFFIC_GREEN, 1);
				break;
			case TRAFFIC_GREEN:
				timerSet(TRAFFIC_BLINKING_DURATION / TIMER_DURATION, 1);
				trafficReInit(TRAFFIC_OFF, 0);
				trafficReInit(TRAFFIC_OFF, 1);
				break;
			default:
				break;
			}
		}
		if (buttonPressed(0)) {
			fsmReInit(FSM_NORMAL);
		}
		break;
	default:
		break;
	}
}
