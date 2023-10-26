/*
 * processing_fsm.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#include "processing_fsm.h"

enum FSM_STATE fsmState = 0;

void fsmInit(void) {
	fsmReInit(FSM_NORMAL);
}

void fsmReInit(enum FSM_STATE state) {
	switch (state) {
	case FSM_NORMAL:
		fsmState = FSM_NORMAL;
		break;
	case FSM_RED_MOD:
		fsmState = FSM_RED_MOD;
		break;
	case FSM_AMBER_MOD:
		fsmState = FSM_AMBER_MOD;
		break;
	case FSM_GREEN_MOD:
		fsmState = FSM_GREEN_MOD;
		break;
	default:
		break;
	}
}

void fsmProcessing(void) {
	switch (fsmState) {
	case FSM_NORMAL:
		if (buttonPressed(0)) {
			fsmReInit(FSM_RED_MOD);
		}
		break;
	case FSM_RED_MOD:
		if (buttonPressed(0)) {
			fsmReInit(FSM_AMBER_MOD);
		}
		break;
	case FSM_AMBER_MOD:
		if (buttonPressed(0)) {
			fsmReInit(FSM_GREEN_MOD);
		}
		break;
	case FSM_GREEN_MOD:
		if (buttonPressed(0)) {
			fsmReInit(FSM_NORMAL);
		}
		break;
	default:
		break;
	}
}
