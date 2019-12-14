/*
 * timers.c
 *
 *  Created on: Dec 7, 2019
 *      Author: ahmed
 */


#include "timers.h"

static uint8 gu8_timer0Prescaler;
static uint8 gu8_timer1Prescaler;
static uint8 gu8_timer2Prescaler;

uint32 TCNT1_Preload;

/*===========================Timer0 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer0Init(En_timer0Mode_t mode,En_timer0OC_t OC0,En_timer0perscaler_t prescal, uint8 initialValue, uint8 outputCompare, En_timer0Interrupt_t interruptMask){

    TCCR0 = mode | OC0;

    gu8_timer0Prescaler=prescal;

    TCNT0 = initialValue;

    OCR0 = outputCompare;

    TIMSK|=interruptMask;
}

/**
 * Description:
 * @param value
 */
void timer0Set(uint8 value){

    TCNT0 = value;
}

/**
 * Description:
 * @return
 */
uint8 timer0Read(void){

    return TCNT0;
}

/**
 * Description:
 */
void timer0Start(void){

    TCCR0|=gu8_timer0Prescaler;
}

/**
 * Description:
 */
void timer0Stop(void){

    TCCR0|=T0_NO_CLOCK;

}

/**
 * Description:
 * @param delay
 */
void timer0Delay_ms(uint16 delay){

    uint8 u8_timerModeCheck = GET_BIT(TCCR0,BIT3);

    switch(u8_timerModeCheck)
	{

	    case 0: //Normal Mode

		TCCR0 |= T0_PRESCALER_64;

		uint16 u16_OverflowCounterNM=0; //Count number of overflows

		timer0Set(130); //130 to trick only 125 tricks for 1 overflow

		timer0Start();


		for(u16_OverflowCounterNM=0; u16_OverflowCounterNM<delay; u16_OverflowCounterNM++)
		    {
			while(((TIFR)&(1<<0))==0){};
			SET_BIT(TIFR,BIT0);
			timer0Set(130);
		    }
		timer0Stop();
		break;

	    case 1: //Compare Mode

		TCCR0 |= T0_PRESCALER_64;

		uint16 u16_OverflowCounterCM=0; //Count number of overflows

		uint8  u8_flagCheckCM; //Check overflow

		timer0Set(0); //0 to trick for compared value to check

		timer0Start();

		while(u16_OverflowCounterCM != (delay)) //check delay equal overflow
		    {
			u8_flagCheckCM=0;
			u8_flagCheckCM=GET_BIT(TIFR,BIT1); //store status of TOV0 flag

			if(u8_flagCheckCM==1)//check for overflow
			    {
				u16_OverflowCounterCM++; //increase overflow by 1 everytime
				SET_BIT(TIFR,BIT1);
			    }
		    }
		timer0Stop();
		break;
	}
}

/**
 * Description:
 * @param dutyCycle
 */
void timer0SwPWM(uint8 dutyCycle,uint8 freq){
    float regu_DC = (dutyCycle/100)*250.00;

       timer0Init(T0_NORMAL_MODE,T0_OC0_DIS,T0_PRESCALER_64,0,0,T0_POLLING);

       float DC = regu_DC/250.00;

       SET_BIT(PORTD_DATA,MOTOR_EN_1_BIT);

       timer0Delay_ms(DC*freq);

       CLR_BIT(PORTD_DATA,MOTOR_EN_1_BIT);

       timer0Delay_ms((1-DC)*freq);


}


/*===========================Timer1 Control===============================*/
/**
 * Description:
 * @param controlA
 * @param controlB
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer1Init(En_timer1Mode_t mode,En_timer1OC_t OC,En_timer1perscaler_t prescal, uint16 initialValue, uint16 outputCompareA, uint16 outputCompareB, uint16 inputCapture, En_timer1Interrupt_t interruptMask){

    TCCR1 = mode | OC;

    gu8_timer1Prescaler=prescal;

    TCNT1 = initialValue;

    OCR1A = outputCompareA;

    OCR1B = outputCompareB;

    ICR1 = inputCapture;

    TIMSK |= interruptMask;


}

/**
 * Description:
 * @param value
 */
void timer1Set(uint16 value){

    TCNT1 = value;
}


/**
 * Description:
 * @return
 */
uint16 timer1Read(void){

    return TCNT1;
}



/**
 * Description:
 */
void timer1Start(void){

    TCCR1 |=gu8_timer1Prescaler;
}

/**
 * Description:
 */
void timer1Stop(void){

    TCCR1 &=~ gu8_timer1Prescaler;

}

/**
 * Description:
 * @param delay
 */
void timer1Delay_ms(uint16 delay){

		timer1Init(T1_NORMAL_MODE,T1_OC1_DIS,T1_PRESCALER_64,0,0,0,0,T1_POLLING);


    		uint32 u32_OverflowCounterNM=0; //Count number of overflows

    		timer1Set(65410); //65410 to trick only 125 tricks for 1 overflow

    		timer1Start();

		for(u32_OverflowCounterNM=0; u32_OverflowCounterNM<delay; u32_OverflowCounterNM++)
		    {
			while(((TIFR)&(1<<2))==0){};
			SET_BIT(TIFR,BIT2);
			timer1Set(65410);
		    }
    		timer1Stop();

}

/**
 * Description:
 * @param dutyCycle
 */
void timer1SwPWM(uint8 dutyCycle,uint8 freq){
/**

    uint32 TCNT_MAX = 8000000/(freq*1000*64);   			//Get the max of TCNT value

    uint32 tcnt_start = 0xFFFF - TCNT_MAX;

    TCNT1 = tcnt_start;

    uint32 ocr_ticks = ((TCNT_MAX*dutyCycle)/100)-1;

    uint32 ocr_value = tcnt_start + ocr_ticks;

    OCR1A = ocr_value;

    Led_On(0);

    while(((TIFR)&(BIT4)) >>4 == 0){}; //Compare flag
    SET_BIT(TIFR,BIT4);
    Led_Off(0);

    while(((TIFR)&(BIT2)) >>2 ==0){}; //Overflow flag
    SET_BIT(TIFR,BIT2);

    */

    uint32 Freq_Hz=freq*1000;
    	uint16 scalar;
    	switch(gu8_timer1Prescaler)
    	{
    	case T1_PRESCALER_NO:
    		scalar=1;
    		break;
    	case T1_PRESCALER_8:
    		scalar=8;
    		break;
    	case T1_PRESCALER_64:
    		scalar=64;
    		break;
    	case T1_PRESCALER_256:
    		scalar=256;
    		break;
    	case T1_PRESCALER_1024:
    		scalar=1024;
    		break;


    	}

    	uint32 Number_of_counts,TCNT1_Preload,OCR1A_value;
    	Number_of_counts=(8000000)/(scalar*Freq_Hz);
    	//Number_of_counts*=100;
    	TCNT1_Preload=0xFFFF-Number_of_counts;
    	TCNT1=TCNT1_Preload;
    	OCR1A_value=(((dutyCycle*Number_of_counts)/100))-1;
    	OCR1A=TCNT1+OCR1A_value;

    	timer1Start();

        gpioPinWrite(GPIOD,BIT4,HIGH);
        gpioPinWrite(GPIOD,BIT5,HIGH);

/*
    //	Led_On(0);
    //	while(!((TIFR&0x10)>>4));
    //	TIFR |=(1<<4);
   // 	gpioPinWrite(GPIOD,BIT4,LOW);
   // 	gpioPinWrite(GPIOD,BIT5,LOW);
   // 	Led_Off(0);
   // 	while(!((TIFR&0x04)>>2));
   // 	TIFR |=(1<<2);
    *
    *
    */
}





/*===========================Timer2 Control===============================*/
/**
 * Description:
 * @param control
 * @param initialValue
 * @param outputCompare
 * @param interruptMask
 */
void timer2Init(En_timer2Mode_t mode,En_timer2OC_t OC,En_timer2perscaler_t prescal, uint8 initialValue, uint8 outputCompare, uint8 assynchronous, En_timer2Interrupt_t interruptMask){

    TCCR2 = mode | OC;

    gu8_timer2Prescaler=prescal;

    TCNT2 = initialValue;

    OCR2 = outputCompare;

    TIMSK|=interruptMask;
}
/**
 * Description:
 * @param value
 */
void timer2Set(uint8 value){

    TCNT2 = value;
}

/**
 * Description:
 * @return
 */
uint8 timer2Read(void){

    return TCNT2;
}

/**
 * Description:
 */
void timer2Start(void){

    TCCR2 |= gu8_timer2Prescaler;
}

/**
 * Description:
 */
void timer2Stop(void){

    TCCR2 = T2_NO_CLOCK;
}

/**
 * Description:
 * @param delay
 */
void timer2Delay_ms(uint16 delay){

	TCCR2 |= T2_PRESCALER_64;

	uint16 u16_OverflowCounterNM=0; //Count number of overflows

	timer2Set(130); //5 to trick only 250 tricks for 1 overflow

	timer2Start();


	for(u16_OverflowCounterNM=0; u16_OverflowCounterNM<delay; u16_OverflowCounterNM++)
	    {
		while(((TIFR)&(1<<6))==0){};
		SET_BIT(TIFR,BIT6);
		timer2Set(130);
	    }
	timer2Stop();

}

/**
 * Description:
 * @param dutyCycle
 */
void timer2SwPWM(uint8 dutyCycle,uint8 freq){
    float regu_DC = (dutyCycle/100)*250.00;

    Led_Init(0);

    timer2Init(T2_NORMAL_MODE,T2_NO_CLOCK,T2_PRESCALER_64,0,0,0,T2_POLLING);

    float DC = regu_DC/250.00;

    Led_On(0);

    timer2Delay_ms(DC*freq);

    Led_Off(0);

    timer2Delay_ms((1-DC)*freq);


}

/*
 * user defined
 */
void timer2Delay_us(uint32 delay){

	TCCR2 |= T2_PRESCALER_NO;

	uint16 u16_OverflowCounterNM=0; //Count number of overflows

	timer2Set(247); //247 to trick only 8 tricks for 1 overflow

	timer2Start();


	for(u16_OverflowCounterNM=0; u16_OverflowCounterNM<delay; u16_OverflowCounterNM++)
	    {
		while(((TIFR)&(1<<6))==0){};
		SET_BIT(TIFR,BIT6);
		timer2Set(247);
	    }
	timer2Stop();

}
