/*
 *  File name : Motor.h
 *	Layer 	  : HAL
 *  Created on: Feb 16, 2024
 *  Author	  : Mohamed Demrdash
 *  Brief	  : This is driver for DC motor with PID control based on specific board "STM32F103C8"
 */

#ifndef HAL_INC_MOTOR_H_
#define HAL_INC_MOTOR_H_

#include "stm32f10x.h"

//This parameters is set the maximum value of the operation of the motor

#define MAX_DUTY_CYCLE 		100

#define MAX_RPM 			160				     //This macro is related to the datasheet of the DC motor JGA25‐371
#define MAX_SPEED 			55.416			     //This macro is related to the motor and the diameter of the wheel and it is in CM/S
#define MAX_TIMER_VALUE 	((uint16_t)0xFFFF)   //This macro is related to the value of the Auto_reload Register
#define TIMER_PSC_VALUE		((uint16_t)0x0002)
#define MOTOR_STOP 			((uint16_t)0x0000)


//This parameter is related of the PID controller
//#define KP  				2
//#define KI					0.1
//#define KD					0.001
//#define ACCEPTABLE_ERROR 	0.0005

#define KP  				1
#define KI					0.5
#define KD					0.1
#define ACCEPTABLE_ERROR 	0.0005


typedef struct
{
	GPIO_TypeDef* GPIOx_pwm;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_pwm;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_in1;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_in1;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_in2;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_in2;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	TIM_TypeDef*  TIMx;				//TIMx: where x can be 1 to 5 and 9 to 11 to select the TIM peripheral.
	uint16_t 	  TIM_Channel_x;	//TIM_Channel_x :where x can be 1 ,2 ,3 or 4 to select the TIM channel.



	float 	error[2];			//This parameter is related to the PID control you don't have to set it
									//error[0] = The previous error for the differential controller
									//error[1] = The Cumulative error for the integral  controller
}Motor;

typedef enum
{
	FORWARD = 1,
	REVERSE,
	STOP,
	TURN_RIGHT,
	TURN_LEFT
}MOTOR_DIR;

void Motor_Init(Motor* motor);
void Motor_SetSpeed(Motor* motor,float speed);
void Motor_SetRPM(Motor* motor,float RPM);
void Motor_PIDSetSpeed(Motor* motor,float actual_speed,float desired_speed);
void Motor_SetCarDir(Motor* Rmotor,Motor* Lmotor,MOTOR_DIR direction);

#endif /* HAL_INC_MOTOR_H_ */
