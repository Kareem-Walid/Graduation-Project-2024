/*
 *  File name : Motor.c
 *	Layer 	  : HAL
 *  Created on: Feb 16, 2024
 *  Author	  : Mohamed Demrdash
 *  Brief	  : This is driver for Dc motor with pid control based on specific board "STM32F103C8"
 */

#include "Motor.h"


static TIM_OCInitTypeDef TIM_OCInitStruct =
{		TIM_OCMode_PWM1,
		TIM_OutputState_Enable,
		TIM_OutputNState_Disable,
		MOTOR_STOP,
		TIM_OCPolarity_High
};


static GPIO_InitTypeDef GPIO_InitStruct_pwm =
{		GPIO_Pin_0,
		GPIO_Speed_50MHz,
		GPIO_Mode_AF_PP,
};

static GPIO_InitTypeDef GPIO_InitStruct_in =
{		GPIO_Pin_0,
		GPIO_Speed_50MHz,
		GPIO_Mode_Out_PP,
};



void Motor_Init(Motor* motor)
{

	//Enable the GPIO for  PWM
	if(motor->GPIOx_pwm == GPIOA)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	}
	else if(motor->GPIOx_pwm == GPIOB)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	}
	else if(motor->GPIOx_pwm == GPIOC)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	}

	//Enable the GPIO for Input1
	if(motor->GPIOx_in1 != motor->GPIOx_pwm)
	{
		if(motor->GPIOx_in1 == GPIOA)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		}
		else if(motor->GPIOx_in1 == GPIOC)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		}
		else if(motor->GPIOx_in1 == GPIOC)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		}
	}

	//Enable the GPIO for Input2
	if((motor->GPIOx_in2 != motor->GPIOx_pwm) && (motor->GPIOx_in2 != motor->GPIOx_in1))
	{
		if(motor->GPIOx_in2 == GPIOA)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		}
		else if(motor->GPIOx_in2 == GPIOC)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		}
		else if(motor->GPIOx_in2 == GPIOC)
		{
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
		}
	}

	////Enable the Timer for PWM
	if(motor->TIMx == TIM1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	}
	else if(motor->TIMx == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	else if(motor->TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if(motor->TIMx == TIM4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}

	//Initialize the pins of the PWM , in1 and in2
	GPIO_InitStruct_pwm.GPIO_Pin = motor->GPIO_Pin_pwm;
	GPIO_Init(motor->GPIOx_pwm,&GPIO_InitStruct_pwm);

	GPIO_InitStruct_in.GPIO_Pin = motor->GPIO_Pin_in1;
	GPIO_Init(motor->GPIOx_in1,&GPIO_InitStruct_in);
	GPIO_ResetBits(motor->GPIOx_in1, motor->GPIO_Pin_in1);

	GPIO_InitStruct_in.GPIO_Pin = motor->GPIO_Pin_in2;
	GPIO_Init(motor->GPIOx_in2,&GPIO_InitStruct_in);
	GPIO_ResetBits(motor->GPIOx_in2, motor->GPIO_Pin_in2);


	//Initialize the Timer of the PWM
	if(motor->TIM_Channel_x == TIM_Channel_1)
	{
		TIM_OC1Init(motor->TIMx,&TIM_OCInitStruct);
		TIM_SetCompare1(motor->TIMx,0);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_2)
	{
		TIM_OC2Init(motor->TIMx,&TIM_OCInitStruct);
		TIM_SetCompare2(motor->TIMx,0);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_3)
	{
		TIM_OC3Init(motor->TIMx,&TIM_OCInitStruct);
		TIM_SetCompare3(motor->TIMx,0);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_4)
	{
		TIM_OC4Init(motor->TIMx,&TIM_OCInitStruct);
		TIM_SetCompare4(motor->TIMx,0);
	}

	TIM_PrescalerConfig(motor->TIMx, TIMER_PSC_VALUE,TIM_PSCReloadMode_Immediate);
	TIM_SetAutoreload(motor->TIMx, MAX_TIMER_VALUE);
	TIM_CounterModeConfig(motor->TIMx,TIM_CounterMode_Up);
	TIM_InternalClockConfig(motor->TIMx);

	/* TIMx enable counter */
	TIM_Cmd(motor->TIMx,ENABLE);
	TIM_CCxCmd(motor->TIMx,motor->TIM_Channel_x,TIM_CCx_Enable);
}


void Motor_SetSpeed(Motor* motor,float speed)
{
	uint16_t mapped_vlaue = (speed/MAX_SPEED) * MAX_TIMER_VALUE;
	if(motor->TIM_Channel_x == TIM_Channel_1)
	{
		TIM_SetCompare1(motor->TIMx,mapped_vlaue);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_2)
	{
		TIM_SetCompare2(motor->TIMx,mapped_vlaue);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_3)
	{
		TIM_SetCompare3(motor->TIMx,mapped_vlaue);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_4)
	{
		TIM_SetCompare4(motor->TIMx,mapped_vlaue);
	}
}

void Motor_SetRPM(Motor* motor,float RPM)
{
	uint16_t mapped_vlaue = (RPM/MAX_RPM) * MAX_TIMER_VALUE;
	if(motor->TIM_Channel_x == TIM_Channel_1)
	{
		TIM_SetCompare1(motor->TIMx,mapped_vlaue);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_2)
	{
		TIM_SetCompare2(motor->TIMx,mapped_vlaue);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_1)
	{
		TIM_SetCompare3(motor->TIMx,mapped_vlaue);
	}
	else if(motor->TIM_Channel_x == TIM_Channel_1)
	{
		TIM_SetCompare4(motor->TIMx,mapped_vlaue);
	}

}

void Motor_PIDSetSpeed(Motor* motor,float actual_speed,float desired_speed)
{
	float error = desired_speed - actual_speed;
	if((error > 0 && motor->error[0] < 0) || (error < 0 && motor->error[0] > 0))
	{
		motor->error[1] = 0;
	}
	motor->error[1] += error ;
	if(motor->error[1]  < 100)
	{
		motor->error[1] = 100;
	}
	else if(motor->error[1]  > -100)
	{
		motor->error[1] = -100;
	}
	float correction_value = KP * error + KD * (error - motor->error[0]) + KI * motor->error[1];
	int16_t mapped_value = (correction_value/100) * MAX_TIMER_VALUE;
	if(mapped_value > MAX_TIMER_VALUE)
	{
		mapped_value = MAX_TIMER_VALUE;
	}
	else if(mapped_value < 0)
	{
		mapped_value = 0;
	}
	if(motor->TIM_Channel_x == TIM_Channel_1)
	{
		TIM_SetCompare1(motor->TIMx, mapped_value );
	}
	else if(motor->TIM_Channel_x == TIM_Channel_2)
	{
		TIM_SetCompare2(motor->TIMx, mapped_value );
	}
	else if(motor->TIM_Channel_x == TIM_Channel_3)
	{
		TIM_SetCompare3(motor->TIMx, mapped_value );
	}
	else if(motor->TIM_Channel_x == TIM_Channel_4)
	{
		TIM_SetCompare4(motor->TIMx, mapped_value );
	}
	motor->error[0] =  error;
}

void Motor_SetCarDir(Motor* Rmotor,Motor* Lmotor,MOTOR_DIR direction)
{
	switch(direction)
	{
	case FORWARD:
		GPIO_ResetBits(Rmotor->GPIOx_in2, Rmotor->GPIO_Pin_in2);
		GPIO_ResetBits(Lmotor->GPIOx_in2, Lmotor->GPIO_Pin_in2);
		while(GPIO_ReadOutputDataBit(Rmotor->GPIOx_in2, Rmotor->GPIO_Pin_in2) ||
				GPIO_ReadOutputDataBit(Lmotor->GPIOx_in2, Lmotor->GPIO_Pin_in2)   );
		GPIO_SetBits(Rmotor->GPIOx_in1, Rmotor->GPIO_Pin_in1);
		GPIO_SetBits(Lmotor->GPIOx_in1, Lmotor->GPIO_Pin_in1);
		break;
	case REVERSE:
		GPIO_ResetBits(Rmotor->GPIOx_in1, Rmotor->GPIO_Pin_in1);
		GPIO_ResetBits(Lmotor->GPIOx_in1, Lmotor->GPIO_Pin_in1);
		while(GPIO_ReadOutputDataBit(Rmotor->GPIOx_in1, Rmotor->GPIO_Pin_in1) ||
				GPIO_ReadOutputDataBit(Lmotor->GPIOx_in1, Lmotor->GPIO_Pin_in1)   );
		GPIO_SetBits(Rmotor->GPIOx_in2, Rmotor->GPIO_Pin_in2);
		GPIO_SetBits(Lmotor->GPIOx_in2, Lmotor->GPIO_Pin_in2);
		break;
	case STOP:
		GPIO_ResetBits(Rmotor->GPIOx_in1, Rmotor->GPIO_Pin_in1);
		GPIO_ResetBits(Lmotor->GPIOx_in1, Lmotor->GPIO_Pin_in1);
		GPIO_ResetBits(Rmotor->GPIOx_in2, Rmotor->GPIO_Pin_in2);
		GPIO_ResetBits(Lmotor->GPIOx_in2, Lmotor->GPIO_Pin_in2);
		break;
	case TURN_LEFT:
		GPIO_ResetBits(Rmotor->GPIOx_in2, Rmotor->GPIO_Pin_in2);
		GPIO_ResetBits(Lmotor->GPIOx_in1, Lmotor->GPIO_Pin_in1);
		while(GPIO_ReadOutputDataBit(Rmotor->GPIOx_in2, Rmotor->GPIO_Pin_in2) ||
				GPIO_ReadOutputDataBit(Lmotor->GPIOx_in1, Lmotor->GPIO_Pin_in1)   ) ;
		GPIO_SetBits(Rmotor->GPIOx_in1, Rmotor->GPIO_Pin_in1);
		GPIO_SetBits(Lmotor->GPIOx_in2, Lmotor->GPIO_Pin_in2);
		break;
	case TURN_RIGHT:
		GPIO_ResetBits(Rmotor->GPIOx_in1, Rmotor->GPIO_Pin_in1);
		GPIO_ResetBits(Lmotor->GPIOx_in2, Lmotor->GPIO_Pin_in2);
		while(GPIO_ReadOutputDataBit(Rmotor->GPIOx_in1, Rmotor->GPIO_Pin_in1) ||
				GPIO_ReadOutputDataBit(Lmotor->GPIOx_in2, Lmotor->GPIO_Pin_in2)   );
		GPIO_SetBits(Rmotor->GPIOx_in2, Rmotor->GPIO_Pin_in2);
		GPIO_SetBits(Lmotor->GPIOx_in1, Lmotor->GPIO_Pin_in1);
		break;
	}

}
