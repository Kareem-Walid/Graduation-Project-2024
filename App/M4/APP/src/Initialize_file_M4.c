
/*------------------------------------ Includes ------------------------- */
#include "Initialize_file_M4.h"
#include "stm32f4xx.h"
/* ---------------------------------------------------------------------- */

ENCODER Left_ENC =
{
		.GPIOx_chA   	= GPIOA,
		.GPIO_Pin_ChA 	= GPIO_Pin_8,
		.GPIOx_chB		= GPIOB,
		.GPIO_Pin_ChB	= GPIO_Pin_15,
		.TIMx			= TIM1,
		.TIM_Channel_x	= TIM_Channel_1
};

ENCODER Right_ENC =
{
		.GPIOx_chA   	= GPIOB,
		.GPIO_Pin_ChA 	= GPIO_Pin_6,
		.GPIOx_chB		= GPIOB,
		.GPIO_Pin_ChB	= GPIO_Pin_7,
		.TIMx			= TIM4,
		.TIM_Channel_x	= TIM_Channel_1
};

Ultrasonic_t Left_US =
{
		.GPIOx_Trig  = GPIOA,
		.GPIOx_Echo  = GPIOA,
		.TRIGGER_PIN = GPIO_Pin_12,
		.ECO_PIN     = GPIO_Pin_15,
		.Channel_Num = TIM_Channel_1,
		.TIMx        = TIM2
};
Ultrasonic_t Right_US =
{
		.GPIOx_Trig  = GPIOB,
		.GPIOx_Echo  = GPIOB,
		.TRIGGER_PIN = GPIO_Pin_5,
		.ECO_PIN     = GPIO_Pin_4,
		.Channel_Num = TIM_Channel_1,
		.TIMx        = TIM3
};

Ultrasonic_t Front_US =
{
		.GPIOx_Trig  = GPIOA,
		.GPIOx_Echo  = GPIOA,
		.TRIGGER_PIN = GPIO_Pin_1,
		.ECO_PIN     = GPIO_Pin_0,
		.Channel_Num = TIM_Channel_1,
		.TIMx        = TIM5
};


SPI_dev BP1 =
{
		.SPIx = SPI1,
		.GPIO_Pin_MISO = GPIO_Pin_6,
		.GPIO_Pin_MOSI = GPIO_Pin_7,
		.GPIOx_SCK     = GPIOA,
		.GPIOx_NSS     = GPIOA,
		.GPIO_Pin_NSS  = GPIO_Pin_4,
		.GPIO_Pin_SCK  = GPIO_Pin_5,
		.GPIOx_MISO    = GPIOA,
		.GPIOx_MOSI    = GPIOA,
};


SPI_InitTypeDef SPI_InitStructure =
{
		.SPI_Direction = SPI_Direction_2Lines_FullDuplex,
		.SPI_Mode	   = SPI_Mode_Slave,
		.SPI_DataSize  = SPI_DataSize_16b,
		.SPI_CPOL      = SPI_CPOL_High,
		.SPI_CPHA      = SPI_CPHA_2Edge,
		.SPI_NSS       = SPI_NSS_Soft,
		.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2,
		.SPI_FirstBit  = SPI_FirstBit_MSB
};

GPIO_InitTypeDef  GPIO_SPI_Struct =
{
		.GPIO_Mode = GPIO_Mode_AF,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd = GPIO_PuPd_NOPULL,
		.GPIO_Speed = GPIO_Low_Speed
};


void SPI_Dev_Init(SPI_dev* BP)
{
	uint16_t GPIO_PinSource = 0x00;

	if(BP->SPIx == SPI1)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

		while(!( BP -> GPIO_Pin_MISO & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MISO , GPIO_PinSource, GPIO_AF_SPI1);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MOSI & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MOSI , GPIO_PinSource, GPIO_AF_SPI1);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_SCK & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_SCK  , GPIO_PinSource, GPIO_AF_SPI1);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_NSS & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_NSS  , GPIO_PinSource, GPIO_AF_SPI1);
	}
	else if(BP->SPIx == SPI2)
	{
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);
		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MISO & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MISO , GPIO_PinSource, GPIO_AF_SPI2);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MOSI & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MOSI , GPIO_PinSource, GPIO_AF_SPI2);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_SCK & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_SCK  , GPIO_PinSource, GPIO_AF_SPI2);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_NSS & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_NSS  , GPIO_PinSource, GPIO_AF_SPI2);
	}
	else if(BP->SPIx == SPI3)
	{
		GPIO_PinSource=0;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3,ENABLE);
		while(!( BP -> GPIO_Pin_MISO & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MISO , GPIO_PinSource, GPIO_AF_SPI3);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MOSI & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MOSI , GPIO_PinSource, GPIO_AF_SPI3);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_SCK & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_SCK  , GPIO_PinSource, GPIO_AF_SPI3);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_NSS & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_NSS  , GPIO_PinSource, GPIO_AF_SPI3);
	}
	else if(BP->SPIx == SPI4)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MISO & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MISO , GPIO_PinSource, GPIO_AF_SPI4);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MOSI & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MOSI , GPIO_PinSource, GPIO_AF_SPI4);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_SCK & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_SCK  , GPIO_PinSource, GPIO_AF_SPI4);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_NSS & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_NSS  , GPIO_PinSource, GPIO_AF_SPI4);
	}
	else if(BP->SPIx == SPI5)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5, ENABLE);
		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MISO & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MISO , GPIO_PinSource, GPIO_AF_SPI5);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MOSI & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MOSI , GPIO_PinSource, GPIO_AF_SPI5);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_SCK & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_SCK  , GPIO_PinSource, GPIO_AF_SPI5);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_NSS & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_NSS  , GPIO_PinSource, GPIO_AF_SPI5);
	}
	else if(BP->SPIx == SPI6)
	{
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI6, ENABLE);
		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MISO & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MISO , GPIO_PinSource, GPIO_AF_SPI6);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_MOSI & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_MOSI , GPIO_PinSource, GPIO_AF_SPI6);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_SCK & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_SCK  , GPIO_PinSource, GPIO_AF_SPI6);

		GPIO_PinSource=0;
		while(!( BP -> GPIO_Pin_NSS & 1<<GPIO_PinSource))
		{
			GPIO_PinSource++;
		}
		GPIO_PinAFConfig(BP -> GPIOx_NSS  , GPIO_PinSource, GPIO_AF_SPI6);
	}

	GPIO_SPI_Struct.GPIO_Pin = (BP -> GPIO_Pin_MISO) ;
	GPIO_Init(BP -> GPIOx_MISO, &GPIO_SPI_Struct);

	GPIO_SPI_Struct.GPIO_Pin = (BP -> GPIO_Pin_MOSI) ;
	GPIO_Init(BP -> GPIOx_MOSI, &GPIO_SPI_Struct);

	GPIO_SPI_Struct.GPIO_Pin = (BP -> GPIO_Pin_SCK) ;
	GPIO_Init(BP -> GPIOx_SCK, &GPIO_SPI_Struct);

	if(SPI_InitStructure.SPI_Mode == SPI_Mode_Slave)
	{
		GPIO_SPI_Struct.GPIO_Pin = (BP -> GPIO_Pin_NSS);
		GPIO_SPI_Struct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_Init(BP ->GPIOx_NSS , &GPIO_SPI_Struct);
	}

	SPI_Init(BP ->SPIx, &SPI_InitStructure);
	SPI_Cmd(BP ->SPIx, ENABLE);

	NVIC_InitTypeDef NVIC_InitStructure;

	SPI_I2S_ITConfig(SPI1, SPI_I2S_IT_RXNE, ENABLE);

	//Enable and set SPI1 interrupt to the highest priority
	NVIC_InitStructure.NVIC_IRQChannel = SPI1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}

void Car_Init(void)
{
	ENC_Init(&Left_ENC);
	ENC_Init(&Right_ENC);

	ULTRASONIC_vInit(&Front_US);
	ULTRASONIC_vInit(&Right_US);
	ULTRASONIC_vInit(&Left_US);


	SPI_Dev_Init(&BP1);
	RCC_DeInit();

}
