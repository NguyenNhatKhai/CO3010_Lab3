/*
 * output_traffic.h
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#ifndef INC_OUTPUT_TRAFFIC_H_
#define INC_OUTPUT_TRAFFIC_H_

#include "main.h"

#define TRAFFIC_NUMBER 2
#define TRAFFIC_SECOND_DURATION 1000
#define TRAFFIC_BLINKING_DURATION 250

enum TRAFFIC_STATE {TRAFFIC_OFF, TRAFFIC_RED, TRAFFIC_AMBER, TRAFFIC_GREEN};

extern int trafficRedDuration;
extern int trafficAmberDuration;
extern int trafficGreenDuration;
extern enum TRAFFIC_STATE trafficState[TRAFFIC_NUMBER];

void trafficInit(void);
void trafficReInit(enum TRAFFIC_STATE state, int index);

#endif /* INC_OUTPUT_TRAFFIC_H_ */
