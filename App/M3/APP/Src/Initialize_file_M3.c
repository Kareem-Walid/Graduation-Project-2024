/*
 * Initialize_file.c
 *
 *  Created on: Jun 9, 2024
 *     Author: Mahmoud Elbardaweel
 */


#include "stm32f10x.h"
#include "Initialize_file_M3.h"

Motor Rmotor =
{
		.GPIOx_pwm    	= GPIOB,
		.GPIO_Pin_pwm 	= GPIO_Pin_7,
		.GPIOx_in1 	  	= GPIOA,
		.GPIO_Pin_in1 	= GPIO_Pin_0,
		.GPIOx_in2    	= GPIOA,
		.GPIO_Pin_in2 	= GPIO_Pin_1,
		.TIMx 		  	= TIM4,
		.TIM_Channel_x	=TIM_Channel_2
};

Motor Lmotor =
{
		.GPIOx_pwm    	= GPIOB,
		.GPIO_Pin_pwm 	= GPIO_Pin_6,
		.GPIOx_in1 	  	= GPIOA,
		.GPIO_Pin_in1 	= GPIO_Pin_2,
		.GPIOx_in2    	= GPIOA,
		.GPIO_Pin_in2 	= GPIO_Pin_3,
		.TIMx 		  	= TIM4,
		.TIM_Channel_x	=TIM_Channel_1
};

SERVO SEV =
{
		.SERVO_GPIO 	= GPIOB ,
		.SERVO_PIN  	= GPIO_Pin_0,
		.TIMx			= TIM3,
		.TIM_Channel_x	= TIM_Channel_3
};

Bluetooth BT1 =
{
		.USARTx			= USART1,
		.GPIOX  		= GPIOA ,
		.GPIO_PIN_TX	= GPIO_Pin_9,
		.GPIO_PIN_RX	= GPIO_Pin_10
};

Bluetooth BT2 =
{
		.USARTx			= USART3,
		.GPIOX  		= GPIOB ,
		.GPIO_PIN_TX	= GPIO_Pin_10,
		.GPIO_PIN_RX	= GPIO_Pin_11
};


SPI_dev BlackPill =
{
		.SPIx = SPI2,
		.GPIOx_NSS      = GPIOB,
		.GPIO_Pin_NSS   = GPIO_Pin_12,
		.GPIOx_SCK      = GPIOB,
		.GPIO_Pin_SCK   = GPIO_Pin_13,
		.GPIOx_MISO     = GPIOB,
		.GPIO_Pin_MISO  = GPIO_Pin_14,
		.GPIOx_MOSI 	= GPIOB,
		.GPIO_Pin_MOSI  = GPIO_Pin_15
};

/* For Rasperry pi */
SPI_dev Raspberry =
{
		.SPIx 			= SPI1,
		.GPIOx_NSS      = GPIOA,
		.GPIO_Pin_NSS   = GPIO_Pin_4,
		.GPIOx_SCK      = GPIOA,
		.GPIO_Pin_SCK   = GPIO_Pin_5,
		.GPIOx_MISO     = GPIOA,
		.GPIO_Pin_MISO  = GPIO_Pin_6,
		.GPIOx_MOSI 	= GPIOA,
		.GPIO_Pin_MOSI  = GPIO_Pin_7
};

SPI_InitTypeDef SPI_InitStructure =
{
		.SPI_Direction = SPI_Direction_2Lines_FullDuplex,
		.SPI_Mode	   = SPI_Mode_Master,
		.SPI_DataSize  = SPI_DataSize_16b,
		.SPI_CPOL      = SPI_CPOL_High,
		.SPI_CPHA      = SPI_CPHA_2Edge,
		.SPI_NSS       = SPI_NSS_Hard,
		.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2,
		.SPI_FirstBit  = SPI_FirstBit_MSB
};


GPIO_InitTypeDef  GPIO_SPI_Struct =
{
		.GPIO_Mode = GPIO_Mode_AF_PP,
		.GPIO_Speed = GPIO_Speed_2MHz
};







void Bluetooth_Init(Bluetooth* BTx)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef  GPIO_UART_Struct;
	if(BTx -> USARTx == USART1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	}
	else if(BTx -> USARTx == USART2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	}
	else if(BTx -> USARTx == USART3)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
	}
	else if(BTx -> USARTx == UART4)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);
	}
	else if(BTx -> USARTx == UART5)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	}

	GPIO_UART_Struct.GPIO_Pin = (BTx -> GPIO_PIN_TX);
	GPIO_UART_Struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_UART_Struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BTx -> GPIOX, &GPIO_UART_Struct);

	GPIO_UART_Struct.GPIO_Pin = (BTx -> GPIO_PIN_RX);
	GPIO_UART_Struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_UART_Struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(BTx -> GPIOX, &GPIO_UART_Struct);

	if(BTx -> USARTx == USART3)
	{

		NVIC_InitTypeDef NVIC_InitStructure;

		// USART_InitStruct.USART_WordLength = USART_WordLength_8b;
		USART_ITConfig(BTx -> USARTx , USART_IT_RXNE , ENABLE);
		NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);
	}

	USART_StructInit(&USART_InitStruct);
	USART_Init(BTx->USARTx,&USART_InitStruct);
	USART_Cmd(BTx->USARTx, ENABLE);
}


void SPIDev_Init(SPI_dev* BP)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	if(BP->SPIx == SPI1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		NVIC_EnableIRQ(SPI1_IRQn);
		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	}
	else if(BP->SPIx == SPI2)
	{

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
		//		SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
	}


	GPIO_SPI_Struct. GPIO_Pin = (BP -> GPIO_Pin_MISO) ;
	GPIO_Init(BP->GPIOx_MISO, &GPIO_SPI_Struct);

	GPIO_SPI_Struct. GPIO_Pin = (BP -> GPIO_Pin_MOSI) ;
	GPIO_Init(BP->GPIOx_MOSI, &GPIO_SPI_Struct);

	GPIO_SPI_Struct. GPIO_Pin = (BP -> GPIO_Pin_SCK) ;
	GPIO_Init(BP->GPIOx_SCK, &GPIO_SPI_Struct);


	if(SPI_InitStructure.SPI_Mode == SPI_Mode_Slave)
	{
		GPIO_SPI_Struct.GPIO_Mode =  GPIO_Mode_IN_FLOATING;
		GPIO_SPI_Struct. GPIO_Pin = (BP -> GPIO_Pin_NSS) ;
		GPIO_Init(BP->GPIOx_NSS, &GPIO_SPI_Struct);
	}

	SPI_Init(BP->SPIx, &SPI_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);
	SPI_Cmd(BP->SPIx, ENABLE);
	SPI_SSOutputCmd(BP->SPIx,ENABLE);
}


void Car_Init(void)
{
	Motor_Init(&Rmotor);
	Motor_Init(&Lmotor);

	SERVO_Init(&SEV);

	Bluetooth_Init(&BT2);

	SPIDev_Init(&BlackPill);

	// BS Buzzer
	BUZZER_Init(GPIOB , GPIO_Pin_9);

	BUZZER_Init(GPIOA , GPIO_Pin_9);
	BUZZER_Init(GPIOA , GPIO_Pin_10);
	BUZZER_Init(LK_SIGNAL_LED_PORT, LK_LED_GPIO_Pin);   // LK
	// AEB LED
	BUZZER_Init(AEB_LED_PORT , AEB_LED_GPIO_Pin);


}


