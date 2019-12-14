/*
 * MotorDC.c
 *
 *  Created on: Dec 9, 2019
 *      Author: ahmed
 */

/**
 * Description:
 * @param
 */

#include "MotorDC.h"
#include "timers.h"
#include "SoftwarePWM.h"

void MotorDC_Init(En_motorType_t MOT_x){


    switch(MOT_x)
	{

	    case MOT_1:
		   SET_BIT(PORTD_DIR,MOTOR_EN_1_BIT);

		   SET_BIT(PORTD_DIR,MOTOR_OUT_1A_BIT);

		   SET_BIT(PORTD_DIR,MOTOR_OUT_1B_BIT);
		   break;


	    case MOT_2:
		    SET_BIT(PORTD_DIR,MOTOR_EN_2_BIT);

		    SET_BIT(PORTD_DIR,MOTOR_OUT_2A_BIT);

		    SET_BIT(PORTD_DIR,MOTOR_OUT_2B_BIT);
		    break;

	}

}

/**
 * Description:
 * @param
 * @param
 */
void MotorDC_Dir(En_motorType_t MOT_x, En_motorDir_t dir){

    switch(MOT_x)
	{
	    case MOT_1:
		switch(dir)
		    {
			case STOP:
			    CLR_BIT(PORTD_DATA,MOTOR_OUT_1A_BIT);

			    CLR_BIT(PORTD_DATA,MOTOR_OUT_1B_BIT);
			    break;

			case FORWARD:
			    SET_BIT(PORTD_DATA,MOTOR_OUT_1A_BIT);

			    CLR_BIT(PORTD_DATA,MOTOR_OUT_1B_BIT);
			    break;

			case BACKWARD:
			    CLR_BIT(PORTD_DATA,MOTOR_OUT_1A_BIT);

			    SET_BIT(PORTD_DATA,MOTOR_OUT_1B_BIT);
			    break;
		    }
		break;

            case MOT_2:
		switch(dir)
		    {
			case STOP:
			    CLR_BIT(PORTD_DATA,MOTOR_OUT_2A_BIT);

			    CLR_BIT(PORTD_DATA,MOTOR_OUT_2B_BIT);
			    break;

			case FORWARD:
			    SET_BIT(PORTD_DATA,MOTOR_OUT_2A_BIT);

			    CLR_BIT(PORTD_DATA,MOTOR_OUT_2B_BIT);
			    break;

			case BACKWARD:
			    CLR_BIT(PORTD_DATA,MOTOR_OUT_2A_BIT);

			    SET_BIT(PORTD_DATA,MOTOR_OUT_2B_BIT);
			    break;
		    }
		break;

	}
}

/**
 * Description:
 * @param
 */
void MotorDC_Speed_PollingWithT0(uint8 speed){


    timer1SwPWM(speed,1);

}

/**
 * Description: set the port value (which is PORT register)
 * @param
 */
void MotorDC_Speed_HwPWM(uint8 speed){


}
