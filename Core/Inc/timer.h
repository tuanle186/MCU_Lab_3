/*
 * timer.h
 *
 *  Created on: Oct 22, 2023
 *      Author: lequo
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

extern int timer0_flag;
extern int timer1_flag;

void setTimer0(int duration);
void setTimer1(int duration);

void timer_run();

#endif /* INC_TIMER_H_ */
