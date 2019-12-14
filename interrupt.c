/*
 * interrupt.c
 *
 *  Created on: Dec 9, 2019
 *      Author: ahmed
 */
#include "interrupt.h"
#include "led.h"
#include "pushButton.h"
#include "timers.h"


extern uint32 TCNT1_Preload;
uint8 close_flag;

uint8 u8_duty=20;
ISR(INT0_vect){


}


ISR(INT1_vect){


}


ISR(INT2_vect){


    //pushButton_Update();
    //uint8 u8_buttonCheckedStatus = pushButton_GetStatus(1);
    //if(u8_buttonCheckedStatus==Pressed)
    Led_Toggle(0);


}


ISR(TIMER2_COMP_vect){



}

ISR(TIMER2_OVF_vect){


}

ISR(TIMER1_CAPT_vect){


}

ISR(TIMER1_COMPA_vect){


    gpioPinWrite(GPIOD,BIT4,LOW);
    gpioPinWrite(GPIOD,BIT5,LOW);
    timer1Set(TCNT1_Preload);

}

ISR(TIMER1_COMPB_vect){


}

ISR(TIMER1_OVF_vect){

    gpioPinWrite(GPIOD,BIT4,HIGH);
    gpioPinWrite(GPIOD,BIT5,HIGH);

}

ISR(TIMER0_COMP_vect){

}


ISR(TIMER0_OVF_vect){

    static uint16 u16_tricks=1;
    u16_tricks++;

    timer1SwPWM(u8_duty,1);

   if(u16_tricks > 0 && u16_tricks % 500 == 0 && u16_tricks <= 2500)
	{
	    u8_duty+=48;

	    timer1SwPWM(u8_duty,1);
	}
    else if(u16_tricks>5000)
	{
	MotorDC_Dir(MOT_1,STOP);
	MotorDC_Dir(MOT_2,STOP);
	SwDelay_ms(1000);

	MotorDC_Dir(MOT_1,FORWARD);
	uint16 u16_iterator2=0;
	for(u16_iterator2=0; u16_iterator2<1000; u16_iterator2++)
	    MotorDC_Speed_PollingWithT0(25);

	MotorDC_Dir(MOT_1,STOP);
	close_flag=1;
	}
   if(u16_tricks > 0 && u16_tricks % 500 == 0 && u16_tricks >= 2500)
	{
	u8_duty-=48;

	timer1SwPWM(u8_duty,1);
	}


}

ISR(SPI_STC_vect){


}

ISR(USART_RXC_vect){


}

ISR(USART_UDRE_vect){


}

ISR(SIG_USART_TRANS){


}

ISR(ADC_vect){


}

ISR(EE_RDY_vect){


}

ISR(TWI_vect){


}

ISR(SPM_RDY_vect){


}
