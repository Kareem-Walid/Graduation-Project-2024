/*
 *  File name : Encoder.c
 *  Layer	  : HAL
 *  Created on: Feb 4, 2024
 *  Author	  : Mohamed Demrdash
 *  Brief	  : This file contain the definition of the Encoder function based on specific board "STM32F401CC"
 */

#include "Encoder.h"

static TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;

static GPIO_InitTypeDef GPIO_InitStruct_ChA = {GPIO_Pin_0,
										   	   GPIO_Mode_AF,
											   GPIO_Fast_Speed,
											   GPIO_OType_PP,
											   GPIO_PuPd_DOWN
											  };

static GPIO_InitTypeDef GPIO_InitStruct_ChB = {GPIO_Pin_1,
										   	   GPIO_Mode_IN,
											   GPIO_Fast_Speed,
											   GPIO_OType_PP,
											   GPIO_PuPd_NOPULL
											  };

void ENC_Init(ENCODER* ENCx)
{
	uint8_t GPIO_AF;
	uint16_t GPIO_PinSource = 0x00;
	GPIO_InitStruct_ChA.GPIO_Pin = ENCx->GPIO_Pin_ChA;
	GPIO_InitStruct_ChB.GPIO_Pin = ENCx->GPIO_Pin_ChB;

	if(ENCx->GPIOx_chA == GPIOA)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	}
	else if(ENCx->GPIOx_chA == GPIOB)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	}
	else if(ENCx->GPIOx_chA == GPIOC)
	{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	}

	if(ENCx->GPIOx_chB != ENCx->GPIOx_chA)
	{
		if(ENCx->GPIOx_chB == GPIOA)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		}
		else if(ENCx->GPIOx_chB == GPIOC)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
		}
		else if(ENCx->GPIOx_chB == GPIOC)
		{
			RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
		}
	}

    if(ENCx->TIMx == TIM1)
    {
    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    	GPIO_AF = GPIO_AF_TIM1;
    }
    else if(ENCx->TIMx == TIM2)
    {
    	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    	GPIO_AF = GPIO_AF_TIM2;
	}
	else if(ENCx->TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    	GPIO_AF = GPIO_AF_TIM3;
	}
	else if(ENCx->TIMx == TIM4)
	{
    	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    	GPIO_AF = GPIO_AF_TIM4;
	}
	else if(ENCx->TIMx == TIM5)
	{
    	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
    	GPIO_AF = GPIO_AF_TIM5;
	}
	else if(ENCx->TIMx == TIM9)
	{
    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
    	GPIO_AF = GPIO_AF_TIM9;
	}
	else if(ENCx->TIMx == TIM10)
	{
    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, ENABLE);
    	GPIO_AF = GPIO_AF_TIM10;
	}
	else if(ENCx->TIMx == TIM11)
	{
    	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, ENABLE);
    	GPIO_AF = GPIO_AF_TIM11;
	}

    while(!(ENCx->GPIO_Pin_ChA & 1<<GPIO_PinSource))
    {
    	GPIO_PinSource++;
    }


    GPIO_Init(ENCx->GPIOx_chA,&GPIO_InitStruct_ChA);
    GPIO_PinAFConfig(ENCx->GPIOx_chA, GPIO_PinSource, GPIO_AF);
    GPIO_Init(ENCx->GPIOx_chB,&GPIO_InitStruct_ChB);

    TIM_SetAutoreload(ENCx->TIMx, 0xFFFF);
    TIM_TimeBaseStructInit(&TIM_TimeBaseInitStruct);
    TIM_TimeBaseInit(ENCx->TIMx,&TIM_TimeBaseInitStruct);
    if(ENCx->TIM_Channel_x == TIM_Channel_1)
    {
    	TIM_TIxExternalClockConfig(ENCx->TIMx, TIM_TIxExternalCLK1Source_TI1,
    								TIM_ICPolarity_Rising, 0);
    }
    else if(ENCx->TIM_Channel_x == TIM_Channel_2)
    {
    	TIM_TIxExternalClockConfig(ENCx->TIMx, TIM_TIxExternalCLK1Source_TI2,
    	    								TIM_ICPolarity_Rising, 0);
    }
    TIM_Cmd(ENCx->TIMx,ENABLE);
}

uint16_t ENC_GetEncoderPulses(ENCODER * ENCx)
{
	uint16_t EncoderPulses = TIM_GetCounter(ENCx->TIMx);
	TIM_SetCounter(ENCx->TIMx, 0);
	return EncoderPulses;
}

/*
 * This function should be called in the ISR of the TIMx
 * the TIME_INTERVAL should be defined first
 */
float ENC_GetMotorRPM(ENCODER * ENCx)
{
	uint16_t EncoderPulses = TIM_GetCounter(ENCx->TIMx);
	TIM_SetCounter(ENCx->TIMx, 0);
	float RPM = (EncoderPulses / PPR) * (60/TIME_INTERVAL) * 5.25;
	return RPM;

}

/*
 * This function should be called in the ISR of the TIMx
 * The TIME_INTERVAL should be defined first
 * The value of the speed is given in cm/s
 */
float ENC_GetMotorSpeed(ENCODER * ENCx)
{
	uint16_t EncoderPulses = TIM_GetCounter(ENCx->TIMx);
	TIM_SetCounter(ENCx->TIMx, 0);
	float RPM = (EncoderPulses / PPR) * (60/TIME_INTERVAL) * 5.25;
	float Speed = WHEEL_DIAMETER * PI * RPM/60;
	return Speed;

}



Direction_State ENC_GetMototDirection(ENCODER * ENCx)
{
	Direction_State Motor_dir;
	uint8_t current_chA ,current_chB,previous_chA,previous_chB;
	previous_chA = current_chA = GPIO_ReadInputDataBit(ENCx->GPIOx_chA, ENCx->GPIO_Pin_ChA);
	previous_chB = current_chB = GPIO_ReadInputDataBit(ENCx->GPIOx_chB, ENCx->GPIO_Pin_ChB);
	if(TIM_GetCounter(ENCx->TIMx))
	{
		while((current_chA == previous_chA) && (current_chB == previous_chB))
			{
				current_chA = GPIO_ReadInputDataBit(ENCx->GPIOx_chA, ENCx->GPIO_Pin_ChA);
				current_chB = GPIO_ReadInputDataBit(ENCx->GPIOx_chB, ENCx->GPIO_Pin_ChB);
			}
			if (current_chA != previous_chA)// A has changed
			{
			    if (current_chA != current_chB)
			    {
			       Motor_dir = FORWARD; // A leads B, so the motor is moving in direction 1 (e.g., clockwise)
			    }
			    else
			    {
			    	Motor_dir = REVERSE; // B leads A, so the motor is moving in direction 2 (e.g., counterclockwise)
			    }
			}
			else if (previous_chB != current_chB)// B has changed
			{
			    if (current_chA == current_chB)
			    {
			    	Motor_dir = FORWARD;// A leads B, so the motor is moving in direction 1 (e.g., clockwise)
			    }
			    else
			    {
			    	Motor_dir = REVERSE; // B leads A, so the motor is moving in direction 2 (e.g., counterclockwise)
			    }
			}
	}
	else
	{
		Motor_dir = STOP;

	}

	return Motor_dir;

}
void ENC_DeInit(ENCODER * ENCx)
{
	TIM_DeInit(ENCx->TIMx);

}
