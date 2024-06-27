#ifndef INITIALIZE_FILE_M4_H_
#define INITIALIZE_FILE_M4_H_

#include "stm32f4xx.h"
#include "Encoder.h"
#include "ULTRASONIC.h"


typedef struct
{
	SPI_TypeDef*  SPIx;				//This parameter can be one of SPIx  where x can be (1..6).
	GPIO_TypeDef* GPIOx_MISO;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_MISO;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_MOSI;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_MOSI;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_SCK;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_SCK;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_NSS;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_NSS;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
}SPI_dev;



extern ENCODER Left_ENC;
extern ENCODER Right_ENC;
extern Ultrasonic_t Left_US;
extern Ultrasonic_t Right_US;
extern Ultrasonic_t Front_US;
extern SPI_dev BP1 ;
extern SPI_InitTypeDef SPI_InitStructure;
extern GPIO_InitTypeDef  GPIO_SPI_Struct;

void SPI_Dev_Init(SPI_dev* BP);
void Car_Init(void);

#endif /* INITIALIZE_FILE_M4_H_ */
