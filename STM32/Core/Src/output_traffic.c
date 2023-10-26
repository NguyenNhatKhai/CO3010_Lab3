/*
 * output_traffic.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Nhat Khai
 */

#include "output_traffic.h"

int trafficRedDuration = 0;
int trafficAmberDuration = 0;
int trafficGreenDuration = 0;
enum TRAFFIC_STATE trafficState[TRAFFIC_NUMBER] = {0, 0};

static uint16_t trafficRedPins[TRAFFIC_NUMBER] = {TRAFFIC0_RED_Pin, TRAFFIC1_RED_Pin};
static uint16_t trafficAmberPins[TRAFFIC_NUMBER] = {TRAFFIC0_AMBER_Pin, TRAFFIC1_AMBER_Pin};
static uint16_t trafficGreenPins[TRAFFIC_NUMBER] = {TRAFFIC0_GREEN_Pin, TRAFFIC1_GREEN_Pin};

void trafficInit(void) {
	trafficRedDuration = 5;
	trafficAmberDuration = 2;
	trafficGreenDuration = 3;
	trafficReInit(TRAFFIC_OFF, 0);
	trafficReInit(TRAFFIC_OFF, 1);
}

void trafficReInit(enum TRAFFIC_STATE state, int index) {
	if (index < 0 || index >= TRAFFIC_NUMBER) return;
	switch (state) {
	case TRAFFIC_OFF:
		HAL_GPIO_WritePin(GPIOB, trafficRedPins[index], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, trafficAmberPins[index], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, trafficGreenPins[index], GPIO_PIN_SET);
		trafficState[index] = TRAFFIC_OFF;
		break;
	case TRAFFIC_RED:
		HAL_GPIO_WritePin(GPIOB, trafficRedPins[index], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, trafficAmberPins[index], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, trafficGreenPins[index], GPIO_PIN_SET);
		trafficState[index] = TRAFFIC_RED;
		break;
	case TRAFFIC_AMBER:
		HAL_GPIO_WritePin(GPIOB, trafficRedPins[index], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, trafficAmberPins[index], GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, trafficGreenPins[index], GPIO_PIN_SET);
		trafficState[index] = TRAFFIC_AMBER;
		break;
	case TRAFFIC_GREEN:
		HAL_GPIO_WritePin(GPIOB, trafficRedPins[index], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, trafficAmberPins[index], GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, trafficGreenPins[index], GPIO_PIN_RESET);
		trafficState[index] = TRAFFIC_GREEN;
		break;
	default:
		break;
	}
}
