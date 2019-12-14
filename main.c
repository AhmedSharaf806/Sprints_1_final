/*
 * main.c
 *
 *  Created on: Dec 3, 2019
 *      Author: ahmed
 */

#include "led.h"
#include "gpio.h"
#include "softwareDelay.h"
#include "pushButton.h"
#include "timers.h"
#include "interrupt.h"
#include "SoftwarePWM.h"
#include "MotorDC.h"

extern uint8 close_flag;

int main(){

    Led_Init(0);
    Led_Init(1);

    Led_Off(0);
    Led_Off(1);

    sei();

    MotorDC_Init(MOT_1);
    MotorDC_Dir(MOT_1,FORWARD);

    MotorDC_Init(MOT_2);
    MotorDC_Dir(MOT_2,FORWARD);



    timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_64,0,0,0,0,(T1_INTERRUPT_CMP_1A | T1_INTERRUPT_NORMAL));
    timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,250,T0_INTERRUPT_NORMAL);

    //uint8 u8_iterator1=0;
    //uint16 u16_iterator2=0;
    //uint8 duty=20;
    timer0Start();

    while(1)
	{
	if(close_flag == 1)
	    break;
	}

}



