/*
 * fsm_automatic.c
 *
 *  Created on: Oct 29, 2023
 *      Author: lequo
 */
#include "main.h"
#include "input_reading.h"
#include "timer.h"

int T_RED = 5000;
int T_AMBER = 2000;
int T_GREEN = 3000;

enum Status{INIT, RED_GREEN, RED_AMBER, GREEN_RED, AMBER_RED, CLEAR};
void LED_CONFIG(enum Status led_status);
enum Status status = INIT;

void fsm_for_automatic_mode() {
	switch (status) {
		case INIT:
			LED_CONFIG(CLEAR);
			setTimer1(T_GREEN);
			status = RED_GREEN;
			break;
		case RED_GREEN:
			LED_CONFIG(RED_GREEN);
			if (timer1_flag == 1) {
				status = RED_AMBER;
				setTimer1(T_AMBER);
			}
			break;
		case RED_AMBER:
			LED_CONFIG(RED_AMBER);
			if (timer1_flag == 1) {
				status = GREEN_RED;
				setTimer1(T_GREEN);
			}
			break;
		case GREEN_RED:
			LED_CONFIG(GREEN_RED);
			if (timer1_flag == 1) {
				status = AMBER_RED;
				setTimer1(T_AMBER);
			}
			break;
		case AMBER_RED:
			LED_CONFIG(AMBER_RED);
			if (timer1_flag == 1) {
				status = RED_GREEN;
				setTimer1(T_GREEN);
				is_button_pressed(0);
			}
			break;
		default:
			break;
	}
}

void LED_CONFIG(enum Status led_status) {
	switch (led_status) {
		case CLEAR:
			HAL_GPIO_WritePin(GPIOB, red_1_Pin | red_2_Pin | amber_1_Pin | amber_2_Pin | green_1_Pin | green_2_Pin, GPIO_PIN_SET);
			break;
		case RED_GREEN:
			HAL_GPIO_WritePin(GPIOB, red_1_Pin | green_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, amber_1_Pin | red_2_Pin, GPIO_PIN_SET);
			break;
		case RED_AMBER:
			HAL_GPIO_WritePin(GPIOB, green_2_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, amber_2_Pin, GPIO_PIN_RESET);
			break;
		case GREEN_RED:
			HAL_GPIO_WritePin(GPIOB, green_1_Pin | red_2_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, red_1_Pin | amber_2_Pin, GPIO_PIN_SET);
			break;
		case AMBER_RED:
			HAL_GPIO_WritePin(GPIOB, green_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, amber_1_Pin, GPIO_PIN_RESET);
			break;
		default:
			break;
	}
}
