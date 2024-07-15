/*
 *  File name : SERVO.c
 *	Layer 	  : HAL
 *  Created on: Feb 28, 2024
 *  Author	  : Abdelrahman Nour
 *  Brief	  : This is driver for Servo motor based on specific board "STM32F103C8"
 */

#include "SERVO.h"





SERVO_info gs_SERVO_info;


void SERVO_Init(SERVO* SEV )
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	TIM_OCInitTypeDef TIM_OCInitStruct =
	{		TIM_OCMode_PWM1,
			TIM_OutputState_Enable,
			TIM_OutputNState_Enable,
			0,
			TIM_OCPolarity_High
	};
	/*--------[ Configure The Servo PWM GPIO Pin ]-------*/
	if(SEV->SERVO_GPIO == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(SEV->SERVO_GPIO == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(SEV->SERVO_GPIO == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}

	GPIO_InitStruct.GPIO_Pin = SEV->SERVO_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(SEV->SERVO_GPIO, &GPIO_InitStruct);

	/*--------[ Calculate & Save The Servo Pulse Information ]-------*/

	gs_SERVO_info.Period_Min = (uint16_t) (ARR_Value * (MinPulse/20.0));
	gs_SERVO_info.Period_Max = (uint16_t) (ARR_Value * (MaxPulse/20.0));


	/*--------[ Configure The Servo PWM Timer Channel ]-------*/

	/*--[Check The Timer & Enable Its Clock]--*/
	if(SEV->TIMx == TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	}
	else if(SEV->TIMx == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	else if(SEV->TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if(SEV->TIMx == TIM4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}

	/* Changes the mapping of the specified pin */
	if(SEV->TIM_Channel_x == TIM_Channel_1)
	{
		TIM_OC1Init(SEV->TIMx,&TIM_OCInitStruct);
		TIM_SetCompare1(SEV->TIMx,gs_SERVO_info.Period_Min);
	}
	else if(SEV->TIM_Channel_x == TIM_Channel_2)
	{
		TIM_OC2Init(SEV->TIMx,&TIM_OCInitStruct);
		TIM_SetCompare2(SEV->TIMx,gs_SERVO_info.Period_Min);
	}
	else if(SEV->TIM_Channel_x == TIM_Channel_3)
	{
		TIM_OC3Init(SEV->TIMx,&TIM_OCInitStruct);
		TIM_SetCompare3(SEV->TIMx,gs_SERVO_info.Period_Min);
	}
	else if(SEV->TIM_Channel_x == TIM_Channel_4)
	{
		TIM_OC4Init(SEV->TIMx,&TIM_OCInitStruct);
		TIM_SetCompare4(SEV->TIMx,gs_SERVO_info.Period_Min);
	}

	TIM_PrescalerConfig(SEV->TIMx, TIMER_PSC_VALUE,TIM_PSCReloadMode_Immediate);
	TIM_SetAutoreload(SEV->TIMx, ARR_Value);
	TIM_CounterModeConfig(SEV->TIMx,TIM_CounterMode_Up);
	TIM_InternalClockConfig(SEV->TIMx);

	/* TIMx enable counter */
	TIM_Cmd(SEV->TIMx,ENABLE);
	TIM_CCxCmd(SEV->TIMx,SEV->TIM_Channel_x,TIM_CCx_Enable);
}

/* Moves A Specific SEV To A Specific Degree That Can Be Float Number */
void SERVO_MoveTo(SERVO* SEV ,float af_Angle)
{
	uint16_t au16_Pulse = 0;

	au16_Pulse = ((af_Angle*(gs_SERVO_info.Period_Max - gs_SERVO_info.Period_Min))/180.0)
							+ gs_SERVO_info.Period_Min;

	if(SEV->TIM_Channel_x == TIM_Channel_1)
	{
		TIM_SetCompare1(SEV->TIMx,au16_Pulse);
	}
	else if(SEV->TIM_Channel_x == TIM_Channel_2)
	{
		TIM_SetCompare2(SEV->TIMx,au16_Pulse);
	}
	else if(SEV->TIM_Channel_x == TIM_Channel_3)
	{
		TIM_SetCompare3(SEV->TIMx,au16_Pulse);
	}
	else if(SEV->TIM_Channel_x == TIM_Channel_4)
	{
		TIM_SetCompare4(SEV->TIMx,au16_Pulse);
	}
}

/* Moves A Specific SEV With A Raw Pulse Width Value */
void SERVO_RawMove(SERVO* SEV , uint16_t au16_Pulse)
{
	if(au16_Pulse <= gs_SERVO_info.Period_Max && au16_Pulse >= gs_SERVO_info.Period_Min)
	{
		if(SEV->TIM_Channel_x == TIM_Channel_1)
		{
			TIM_SetCompare1(SEV->TIMx,au16_Pulse);
		}
		else if(SEV->TIM_Channel_x == TIM_Channel_2)
		{
			TIM_SetCompare2(SEV->TIMx,au16_Pulse);
		}
		else if(SEV->TIM_Channel_x == TIM_Channel_3)
		{
			TIM_SetCompare3(SEV->TIMx,au16_Pulse);
		}
		else if(SEV->TIM_Channel_x == TIM_Channel_4)
		{
			TIM_SetCompare4(SEV->TIMx,au16_Pulse);
		}
	}
}

/* Gets The Maximum Pulse Width Value For A Specific SEV */
uint16_t SERVO_Get_MaxPulse(SERVO* SEV )
{
	return (gs_SERVO_info.Period_Max);
}


/* Gets The Minimum Pulse Width Value For A Specific SEV */
uint16_t SERVO_Get_MinPulse(SERVO* SEV )
{
	return (gs_SERVO_info.Period_Min);
}




