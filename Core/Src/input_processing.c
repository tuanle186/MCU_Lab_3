/*
 * input_processing.c
 *
 *  Created on: Oct 22, 2023
 *      Author: lequo
 */

#include "main.h"
#include "input_reading.h"
#include "red_man.h"

enum ButtonState{BUTTON_RELEASED, BUTTON_PRESSED, BUTTON_PRESSED_MORE_THAN_1_SECOND};
enum ButtonState button_1_state = BUTTON_PRESSED;
enum ButtonState button_2_state = BUTTON_PRESSED;
enum ButtonState button_3_state = BUTTON_PRESSED;

void fsm_for_button_processing(int* mode_state) {
	switch (button_1_state) {
		case BUTTON_RELEASED:
			if (is_button_pressed(0)) {
				button_1_state = BUTTON_PRESSED;
				++*mode_state;
				if (*mode_state >= 5)
					*mode_state = 1;
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(0)) {
				button_1_state = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(0)) {
					button_1_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!is_button_pressed(0)) {
				button_1_state = BUTTON_RELEASED;
			}
			// do nothing, wait for the button to be released
			break;
	}

	switch (button_2_state) {
		case BUTTON_RELEASED:
			if (is_button_pressed(1)) {
				button_2_state = BUTTON_PRESSED;
				increase_T_RED();
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(1)) {
				button_2_state = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(1)) {
					button_2_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!is_button_pressed(1)) {
				button_2_state = BUTTON_RELEASED;
			}
			// do nothing, wait for the button to be released
			break;
	}

	switch (button_3_state) {
		case BUTTON_RELEASED:
			if (is_button_pressed(2)) {
				button_3_state = BUTTON_PRESSED;
			}
			break;
		case BUTTON_PRESSED:
			if (!is_button_pressed(2)) {
				button_3_state = BUTTON_RELEASED;
			} else {
				if (is_button_pressed_1s(2)) {
					button_3_state = BUTTON_PRESSED_MORE_THAN_1_SECOND;
				}
			}
			break;
		case BUTTON_PRESSED_MORE_THAN_1_SECOND:
			if (!is_button_pressed(2)) {
				button_3_state = BUTTON_RELEASED;
			}
			// do nothing, wait for the button to be released
			break;
	}
}
