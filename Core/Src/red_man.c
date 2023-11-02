/*
 * red_man.c
 *
 *  Created on: Oct 30, 2023
 *      Author: lequo
 */
#include "main.h"
#include "timer.h"
#include "fsm_automatic.h"

enum RedManStatus{INIT, BLINK};
enum RedManStatus redManStatus = INIT;

void fsm_for_red_man_mode() {
	switch(redManStatus) {
		case INIT:
			HAL_GPIO_WritePin(GPIOB, red_1_Pin | red_2_Pin | amber_1_Pin | amber_2_Pin | green_1_Pin | green_2_Pin, GPIO_PIN_SET);
			setTimer0(500);
			redManStatus = BLINK;
			break;
		case BLINK:
			if (timer0_flag == 1) {
				HAL_GPIO_TogglePin(GPIOB, red_1_Pin | red_2_Pin);
				setTimer0(500);
			}
			break;
		default:
			break;
	}
}

void increase_T_RED() {
	T_RED = T_RED + 1000;
	T_GREEN = T_GREEN + 1000;
}
