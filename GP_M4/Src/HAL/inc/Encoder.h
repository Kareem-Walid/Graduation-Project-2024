/*
 *  File name : Encoder.h
 *	Layer 	  : HAL
 *  Created on: Feb 4, 2024
 *  Author	  : Mohamed Demrdash
 *  Brief	  :This is driver for encoder based on specific board "STM32F401CC"
 */

#ifndef HAL_INC_ENCODER_H_
#define HAL_INC_ENCODER_H_

#include "stm32f4xx.h"


//The following specifications is related to encoder datasheet
#define GEAR_RATIO 			46.8
#define ENCODER_RESOLUTION	11
#define PPR 				(GEAR_RATIO * ENCODER_RESOLUTION)
#define WHEEL_DIAMETER 		6.5 //This value is given in cm
#define PI 					3.14159265359
#define CLk					8000000
#define PRESCALE_TIM		1000


//The time interval is a parameter passed to ENC_GetMotorSpeed
//and ENC_GetMotorRPM function and you should define the value
//based on your application
// #define TIME_INTERVAL ((float)0xFFFF * (PRESCALE_TIM + 1)/CLk) //The value should be given in Second  ex, 10us

#define TIME_INTERVAL   0.05

#ifndef TIME_INTERVAL
#error YOU HAVE TO DEFINE THE TIME_INTERVAL MACRO WHICH USED IN ENCODER FUNCTIONS
#endif


//The following structure should be declared for every encoder in your project
//and it describe the hardware connection of the encoder and the related timers

typedef struct
{
	GPIO_TypeDef* GPIOx_chA;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_ChA;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_chB;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_ChB;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	TIM_TypeDef*  TIMx;				//TIMx: where x can be 1 to 5 and 9 to 11 to select the TIM peripheral.
	uint8_t		  TIM_Channel_x;    //TIM_Channel_x: where x can be 1 or 2 only
}ENCODER;




//This enum used for the direction of the motor
typedef enum
{
	FORWARD,
	REVERSE,
	STOP
}Direction_State;


//Functions prototype

void ENC_Init(ENCODER * ENCx);
uint16_t ENC_GetEncoderPulses(ENCODER * ENCx);
float ENC_GetMotorRPM(ENCODER * ENCx);
float ENC_GetMotorSpeed(ENCODER * ENCx);
Direction_State ENC_GetMototDirection(ENCODER * ENCx);
void ENC_DeInit(ENCODER * ENCx);

#endif /* HAL_INC_ENCODER_H_ */
