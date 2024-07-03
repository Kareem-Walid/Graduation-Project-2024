/*
 * Initialize_file.h
 *
 *  Created on: Jun 9, 2024
 *      Author: Mahmoud Elbardaweel
 */

#ifndef INITIALIZE_FILE_M3_H_
#define INITIALIZE_FILE_M3_H_

#include "stm32f10x.h"
#include "Motor.h"
#include "SERVO.h"
#include "BUZZER.h"

/* ----------------- MACROS ----------------- */
#define  AEB_LED_PORT       	GPIOA
#define  LEFT_SIGNAL_LED_PORT  	GPIOA
#define  RIGHT_SIGNAL_LED_PORT  GPIOA
#define  LK_SIGNAL_LED_PORT     GPIOA

#define  AEB_LED_GPIO_Pin  		GPIO_Pin_8
#define  LEFT_LED_GPIO_Pin  	GPIO_Pin_10
#define  RIGHT_LED_GPIO_Pin  	GPIO_Pin_9
#define  LK_LED_GPIO_Pin     	GPIO_Pin_12


typedef struct
{
	USART_TypeDef*  USARTx;		 //This parameter can be one of GPIO_Pin_x where x can be (1..5).
	GPIO_TypeDef* 	GPIOX;		 //This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 		GPIO_PIN_TX; //This parameter can be one of GPIO_Pin_x where x can be (0..15).
	uint16_t 		GPIO_PIN_RX; //This parameter can be one of GPIO_Pin_x where x can be (0..15).

}Bluetooth;

typedef struct
{
	SPI_TypeDef*  SPIx;				//This parameter can be one of SPIx  where x can be (1,2 or 3).
	GPIO_TypeDef* GPIOx_MISO;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_MISO;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_MOSI;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_MOSI;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_SCK;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_SCK;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
	GPIO_TypeDef* GPIOx_NSS;		//This parameter can be one of GPIOx where x can be (A, B and C).
	uint16_t 	  GPIO_Pin_NSS;  	//This parameter can be one of GPIO_Pin_x where x can be (0..15).
}SPI_dev;


extern Motor Rmotor;
extern Motor Lmotor;
extern SERVO SEV;
extern Bluetooth BT1 ;
extern SPI_dev BlackPill;
extern SPI_dev Raspberry;
extern SPI_InitTypeDef SPI_InitStructure;
extern GPIO_InitTypeDef  GPIO_SPI_Struct;


void Bluetooth_Init(Bluetooth* BTx);
void SPIDev_Init(SPI_dev* BP);
void Car_Init(void);

#endif /* INITIALIZE_FILE_M3_H_ */
