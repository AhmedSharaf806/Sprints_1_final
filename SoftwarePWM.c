/*
 * SoftwarePWM.c
 *
 *  Created on: Dec 9, 2019
 *      Author: ahmed
 */

#include "SoftwarePWM.h"


void timer0swPWM(uint8 dutycycle, uint8 freq){

    float regu_DC = (dutycycle/100)*250.00;

    timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,0,T0_POLLING);

    float DC = regu_DC/250.00;

    SET_BIT(PORTD_DATA,MOTOR_EN_1_BIT);

    timer0Delay_ms(DC*freq);

    CLR_BIT(PORTD_DATA,MOTOR_EN_1_BIT);

    timer0Delay_ms((1-DC)*freq);

}

void timer1swPWM(uint8 dutycycle, uint8 freq){

    float regu_DC = (dutycycle/100)*250.00;

    Led_Init(0);

    float DC = regu_DC/250.00;

    Led_On(0);

    timer1Delay_ms(DC*freq);

    Led_Off(0);

    timer1Delay_ms((1-DC)*freq);

}

void timer2swPWM(uint8 dutycycle, uint8 freq){

    float regu_DC = (dutycycle/100)*250.00;

    Led_Init(0);

    timer2Init(T2_NORMAL_MODE,T2_NO_CLOCK,T2_PRESCALER_64,0,0,0,T2_POLLING);

    float DC = regu_DC/250.00;

    Led_On(0);

    timer2Delay_ms(DC*freq);

    Led_Off(0);

    timer2Delay_ms((1-DC)*freq);

}
