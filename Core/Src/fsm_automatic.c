/*
 * fsm_automatic.c
 *
 *  Created on: Oct 29, 2023
 *      Author: lequo
 */
#include "main.h"
#include "global.h"
#include "fsm_automatic.h"
#include "timer.h"
#include "input_reading.h"
#include "seven_seg.h"

void fsm_automatic() {
	switch (status) {
		case INIT:
			status = MODE1;
			break;
		case MODE1:
			led_config();
			setTimer0(T_GREEN);
			status = RED_GREEN;
			break;
		case RED_GREEN:
			led_config();
			if (timer0_flag == 1) {
				setTimer0(T_AMBER);
				status = RED_AMBER;
			}
			break;
		case RED_AMBER:
			led_config();
			if (timer0_flag == 1) {
				setTimer0(T_GREEN);
				status = GREEN_RED;
			}
			break;
		case GREEN_RED:
			led_config();
			if (timer0_flag == 1) {
				setTimer0(T_AMBER);
				status = AMBER_RED;
			}
			break;
		case AMBER_RED:
			led_config();
			if (timer0_flag == 1) {
				setTimer0(T_GREEN);
				status = RED_GREEN;
			}
			break;
		default:
			break;
	}
}
