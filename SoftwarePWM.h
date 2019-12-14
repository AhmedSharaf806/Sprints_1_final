/*
 * SoftwarePWM.h
 *
 *  Created on: Dec 9, 2019
 *      Author: ahmed
 */

#ifndef SOFTWAREPWM_H_
#define SOFTWAREPWM_H_

#include "registers.h"
#include "gpio.h"
#include "led.h"
#include "timers.h"
#include "MotorDC.h"

void timer0swPWM(uint8 dutycycle, uint8 freq);

void timer1swPWM(uint8 dutycycle, uint8 freq);

void timer2swPWM(uint8 dutycycle, uint8 freq);


#endif /* SOFTWAREPWM_H_ */
