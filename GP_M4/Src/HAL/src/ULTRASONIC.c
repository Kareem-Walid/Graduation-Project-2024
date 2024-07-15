#include <stdint.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"
#include <ULTRASONIC.h>

volatile static uint16_t IC_Val1_T2 , IC_Val2_T2 ,
                IC_Val1_T3 , IC_Val2_T3 ,
				IC_Val1_T4 , IC_Val2_T4 ,
				IC_Val1_T5 , IC_Val2_T5 ;

static uint16_t Global_Difference ;
float Global_Distance ,d2,d3,d4,d5;
volatile static uint8_t  IT_counter_T2 = 0  , IT_counter_T3 = 0 , IT_counter_T4 = 0 , IT_counter_T5 = 0;

void ULTRASONIC_vInit(Ultrasonic_t * US_Num)
{
	GPIO_InitTypeDef   GPIO_InitStruct;
	NVIC_InitTypeDef   NVIC_InitStructure;
	TIM_ICInitTypeDef  TIM_ICInitStructure;
	uint16_t GPIO_PinSource = 0x00;

	/* GPIOA and GPIOB clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	/* TIMx clock Enable */
	if(US_Num ->TIMx == TIM2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	}
	else if(US_Num ->TIMx == TIM3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	}
	else if(US_Num ->TIMx == TIM4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	}
	else if(US_Num ->TIMx == TIM5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	}

	/*----------------------------------------------------------*/

	GPIO_InitStruct.GPIO_Pin = US_Num ->TRIGGER_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_CLK;

	GPIO_Init(US_Num -> GPIOx_Trig , &GPIO_InitStruct);

	/* TIMx pin configuration */
	GPIO_InitStruct.GPIO_Pin   =  US_Num -> ECO_PIN;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Speed = GPIO_Low_Speed;

	GPIO_Init(US_Num -> GPIOx_Echo, &GPIO_InitStruct);

	while(!(US_Num ->ECO_PIN & 1<<GPIO_PinSource))
	{
		GPIO_PinSource++;
	}

	if(US_Num ->TIMx == TIM2)
	{
		GPIO_PinAFConfig(US_Num ->GPIOx_Echo , GPIO_PinSource , GPIO_AF_TIM2);

		/* Enable the TIM2 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if(US_Num ->TIMx == TIM3)
	{
		GPIO_PinAFConfig(US_Num ->GPIOx_Echo, GPIO_PinSource , GPIO_AF_TIM3);

		/* Enable the TIM3 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if(US_Num ->TIMx == TIM4)
	{
		GPIO_PinAFConfig(US_Num ->GPIOx_Echo , GPIO_PinSource , GPIO_AF_TIM4);
		/* Enable the TIM4 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}
	else if(US_Num ->TIMx == TIM5)
	{
		GPIO_PinAFConfig(US_Num ->GPIOx_Echo , GPIO_PinSource , GPIO_AF_TIM5);
		/* Enable the TIM4 global Interrupt */
		NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}

	TIM_ICInitStructure.TIM_Channel =  US_Num -> Channel_Num;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_BothEdge;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIMER_ICPSC_CFG;
	TIM_ICInitStructure.TIM_ICFilter = 0x0;

	TIM_ICInit(US_Num -> TIMx, &TIM_ICInitStructure);
	TIM_PrescalerConfig(US_Num -> TIMx, TIMEER_PSC_CONFIG, TIM_PSCReloadMode_Immediate);
	/* TIM enable counter */
	TIM_Cmd(US_Num -> TIMx, ENABLE);
	switch(US_Num ->Channel_Num)
	{
	case TIM_Channel_1:
		TIM_ITConfig(US_Num -> TIMx ,TIM_IT_CC1,ENABLE);break;
	case TIM_Channel_2:
		TIM_ITConfig(US_Num -> TIMx ,TIM_IT_CC2,ENABLE);break;
	case TIM_Channel_3:
		TIM_ITConfig(US_Num -> TIMx ,TIM_IT_CC3,ENABLE);break;
	case TIM_Channel_4:
		TIM_ITConfig(US_Num -> TIMx ,TIM_IT_CC4,ENABLE);break;
	}
}

void  ULTRASONIC_vTrig(Ultrasonic_t * US_Num)
{
	GPIO_SetBits( US_Num ->GPIOx_Trig , US_Num -> TRIGGER_PIN );
	Ultrasonic_delay(DELAY_30US);				/* Delay 50 micro second */
	GPIO_ResetBits( US_Num ->GPIOx_Trig , US_Num -> TRIGGER_PIN );
}

float ULTRASONIC_u8GetDistance(Ultrasonic_t * US_Num)
{
	if(US_Num -> TIMx ==TIM2)
	{
		if(IC_Val2_T2 > IC_Val1_T2)
		{
			Global_Difference = IC_Val2_T2 - IC_Val1_T2  ;
			d2 = ((Global_Difference * TIK_TIME ) * 0.034)/2 ;
			return d2;
		}
		else if (IC_Val2_T2 < IC_Val1_T2)
		{
			Global_Difference = (0xffff - IC_Val1_T2)+ IC_Val2_T2 ;
			d2 = ((Global_Difference * TIK_TIME ) * 0.034)/2 ;
			return d2;
		}
	}
	else if(US_Num -> TIMx ==TIM3)
	{
		if(IC_Val2_T3 > IC_Val1_T3)
		{
			Global_Difference = IC_Val2_T3 - IC_Val1_T3  ;
			d3 = ((Global_Difference * TIK_TIME ) * 0.034)/2 ;
			return d3;
		}
		else if (IC_Val2_T3 < IC_Val1_T3)
		{
			Global_Difference = (0xffff - IC_Val1_T3)+ IC_Val2_T3 ;
			d3 = ((Global_Difference * TIK_TIME ) * 0.034)/2 ;
			return d3;
		}
	}
	else if(US_Num -> TIMx ==TIM4)
	{
		if(IC_Val2_T4 > IC_Val1_T4)
		{
			Global_Difference = IC_Val2_T4 - IC_Val1_T4  ;
			d4 = ((Global_Difference * TIK_TIME ) * 0.034)/2 ;
			return d4;
		}
		else if (IC_Val2_T4 < IC_Val1_T4)
		{
			Global_Difference = (0xffff - IC_Val1_T4)+ IC_Val2_T4 ;
			d4 = ((Global_Difference * TIK_TIME ) * 0.034)/2 ;
			return d4;
		}
	}
	else if(US_Num -> TIMx ==TIM5)
	{
		if(IC_Val2_T5 > IC_Val1_T5)
		{
			Global_Difference = IC_Val2_T5 - IC_Val1_T5  ;
			d5 = ((Global_Difference * TIK_TIME ) * 0.034)/2 ;
			return d5;
		}
		else if (IC_Val2_T5 < IC_Val1_T5)
		{
			Global_Difference = (0xffff - IC_Val1_T5)+ IC_Val2_T5 ;
			d5 = ((Global_Difference * TIK_TIME ) * 0.034)/2 ;
			return d5;
		}
	}
}

void Ultrasonic_delay (uint16_t Delay_Num)
{
	uint32_t iteration = (Delay_Num * CLOCK_US)/3 ;
	for(iteration ; iteration > 0 ; iteration--)
	{

	}
}

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_CC1) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM2 , TIM_IT_CC1);
		switch( IT_counter_T2)
		{
		case 0 : IC_Val1_T2 = TIM_GetCapture1(TIM2);
		IT_counter_T2 = 1;
		break;
		case 1 : IC_Val2_T2 = TIM_GetCapture1(TIM2);
		IT_counter_T2 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM2, TIM_IT_CC2) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM2 , TIM_IT_CC2);
		switch( IT_counter_T2)
		{
		case 0 : IC_Val1_T2 = TIM_GetCapture2(TIM2);
		IT_counter_T2 = 1;
		break;
		case 1 : IC_Val2_T2 = TIM_GetCapture2(TIM2);
		IT_counter_T2 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM2, TIM_IT_CC3) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM2 , TIM_IT_CC3);
		switch( IT_counter_T2)
		{
		case 0 : IC_Val1_T2 = TIM_GetCapture3(TIM2);
		IT_counter_T2 = 1;
		break;
		case 1 : IC_Val2_T2 = TIM_GetCapture3(TIM2);
		IT_counter_T2 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM2, TIM_IT_CC4) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM2 , TIM_IT_CC4);
		switch( IT_counter_T2)
		{
		case 0 : IC_Val1_T2 = TIM_GetCapture4(TIM2);
		IT_counter_T2 = 1;
		break;
		case 1 : IC_Val2_T2 = TIM_GetCapture4(TIM2);
		IT_counter_T2 = 0;
		break;
		}
	}

}

void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM3 , TIM_IT_CC1);
		switch( IT_counter_T3)
		{
		case 0 : IC_Val1_T3 = TIM_GetCapture1(TIM3);
		IT_counter_T3 = 1;
		break;
		case 1 : IC_Val2_T3 = TIM_GetCapture1(TIM3);
		IT_counter_T3 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM3 , TIM_IT_CC2);
		switch( IT_counter_T3)
		{
		case 0 : IC_Val1_T3 = TIM_GetCapture2(TIM3);
		IT_counter_T3 = 1;
		break;
		case 1 : IC_Val2_T3 = TIM_GetCapture2(TIM3);
		IT_counter_T3 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM3, TIM_IT_CC3) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM3 , TIM_IT_CC3);
		switch( IT_counter_T3)
		{
		case 0 : IC_Val1_T3 = TIM_GetCapture3(TIM3);
		IT_counter_T3 = 1;
		break;
		case 1 : IC_Val2_T3 = TIM_GetCapture3(TIM3);
		IT_counter_T3 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM3, TIM_IT_CC4) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM3 , TIM_IT_CC4);
		switch( IT_counter_T3)
		{
		case 0 : IC_Val1_T3 = TIM_GetCapture4(TIM3);
		IT_counter_T3 = 1;
		break;
		case 1 : IC_Val2_T3 = TIM_GetCapture4(TIM3);
		IT_counter_T3 = 0;
		break;
		}
	}
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4, TIM_IT_CC1) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM4 , TIM_IT_CC1);
		switch( IT_counter_T4)
		{
		case 0 : IC_Val1_T4 = TIM_GetCapture1(TIM4);
		IT_counter_T4 = 1;
		break;
		case 1 : IC_Val2_T4 = TIM_GetCapture1(TIM4);
		IT_counter_T4 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC2) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM4 , TIM_IT_CC2);
		switch( IT_counter_T4)
		{
		case 0 : IC_Val1_T4 = TIM_GetCapture2(TIM4);
		IT_counter_T4 = 1;
		break;
		case 1 : IC_Val2_T4 = TIM_GetCapture2(TIM4);
		IT_counter_T4 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC3) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM4 , TIM_IT_CC3);
		switch( IT_counter_T4)
		{
		case 0 : IC_Val1_T4 = TIM_GetCapture3(TIM4);
		IT_counter_T4 = 1;
		break;
		case 1 : IC_Val2_T4 = TIM_GetCapture3(TIM4);
		IT_counter_T4 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM4, TIM_IT_CC4) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM4 , TIM_IT_CC4);
		switch( IT_counter_T4)
		{
		case 0 : IC_Val1_T4 = TIM_GetCapture4(TIM4);
		IT_counter_T4 = 1;
		break;
		case 1 : IC_Val2_T4 = TIM_GetCapture4(TIM4);
		IT_counter_T4 = 0;
		break;
		}
	}
}

void TIM5_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM5, TIM_IT_CC1) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM5 , TIM_IT_CC1);
		switch( IT_counter_T5)
		{
		case 0 : IC_Val1_T5 = TIM_GetCapture1(TIM5);
		IT_counter_T5 = 1;
		break;
		case 1 : IC_Val2_T5 = TIM_GetCapture1(TIM5);
		IT_counter_T5 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC2) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM5 , TIM_IT_CC2);
		switch( IT_counter_T5)
		{
		case 0 : IC_Val1_T5 = TIM_GetCapture2(TIM5);
		IT_counter_T5 = 1;
		break;
		case 1 : IC_Val2_T5 = TIM_GetCapture2(TIM5);
		IT_counter_T5 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC3) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM5 , TIM_IT_CC3);
		switch( IT_counter_T5)
		{
		case 0 : IC_Val1_T5 = TIM_GetCapture3(TIM5);
		IT_counter_T5 = 1;
		break;
		case 1 : IC_Val2_T5 = TIM_GetCapture3(TIM5);
		IT_counter_T5 = 0;
		break;
		}
	}
	else if(TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)
	{
		// clear binding flag
		TIM_ClearITPendingBit(TIM5 , TIM_IT_CC4);
		switch( IT_counter_T5)
		{
		case 0 : IC_Val1_T5 = TIM_GetCapture4(TIM5);
		IT_counter_T5 = 1;
		break;
		case 1 : IC_Val2_T5 = TIM_GetCapture4(TIM5);
		IT_counter_T5 = 0;
		break;
		}
	}
}
