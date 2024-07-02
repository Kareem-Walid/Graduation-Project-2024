/*
 * BlindSpot.c
 * Author: Abeer Sobhy
 */

/***********************************************Includes Section*************************************/
#include <stdio.h>
#include <stdlib.h>

#include "STD_TYPES.h"

#include "FreeRTOS.h"

#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"

#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"

#include "BUZZER.h"

#include "BlindSpot.h"
#include "SysInit.h"
/*****************************************************************************************************/
/*****************************************MACROs Section***********************************************/

/******************************************************************************************************/
/****************************************Global Variables Section**************************************/
SemaphoreHandle_t RightDisSemaphoreHandler;
SemaphoreHandle_t LeftDisSemaphoreHandler;

uint16_t RightDis = 0;
uint16_t LeftDis = 0;

/******************************************************************************************************/
/***************************************Extern Global variables Section********************************/
extern SemaphoreHandle_t binarySemaphoreHandler;
extern QueueHandle_t     LCDQueue;
extern EventGroupHandle_t xCreatedEventGroup;

/***************************************Tasks Declaration**********************************************/
void vRightAreaHandler(void* arg);
void vLeftAreaHandler(void* arg);
void TurnSignalWarningTwo(void* arg);
/******************************************************************************************************/
/**************************************Static Functions declaration************************************/
static NBS_ReturnType_e NBS_ReturnType_e_CreateBlindSpotTasks(void);
static NBS_ReturnType_e NBS_ReturnType_e_CreateBlindSpotSemaphores(void);

/******************************************************************************************************/

/****************************************One Shot Functions DEF Section********************************/
NBS_ReturnType_e BS_ReturnTypeBS_Init(void)
{
	NBS_ReturnType_e rt_type = BS_NO_ERROR;
	/***************************************************Queues Creation***********************************************/

	/****************************************************Tasks Creation***********************************************/
	rt_type = NBS_ReturnType_e_CreateBlindSpotTasks();
	/****************************************************Semaphore Creation*******************************************/
	rt_type = NBS_ReturnType_e_CreateBlindSpotSemaphores();
	return rt_type;
}

static NBS_ReturnType_e NBS_ReturnType_e_CreateBlindSpotTasks(void)
{
	NBS_ReturnType_e rt_type = BS_NO_ERROR;
	BaseType_t xTaskCreate_vRightAreaHandler_Handler;
	BaseType_t xTaskCreate_vLeftAreaHandler_Handler;
	BaseType_t xTaskCreate_TurnSignalWarningTwo_Handler;

	/*Create the tasks then check if it is actually created or not.*/
	xTaskCreate_vRightAreaHandler_Handler =  xTaskCreate(vRightAreaHandler,"vRightAreaHandler", 100, NULL, vRightAreaHandler_PRIORITY,NULL);
	if(xTaskCreate_vRightAreaHandler_Handler != pdPASS)
	{
		rt_type = ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	}
	xTaskCreate_vLeftAreaHandler_Handler = xTaskCreate(vLeftAreaHandler,"vLeftAreaHandler", 100, NULL, vLeftAreaHandler_PRIORITY,NULL);
	if(xTaskCreate_vLeftAreaHandler_Handler != pdPASS)
	{
		rt_type = ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	}
	xTaskCreate_TurnSignalWarningTwo_Handler =  xTaskCreate(TurnSignalWarningTwo,"TurnSignalWarningTwo", 100, NULL, TurnSignalWarningTwo_PRIORITY,NULL);
	if(xTaskCreate_TurnSignalWarningTwo_Handler != pdPASS)
	{
		rt_type = ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	}

	return rt_type;
}
static NBS_ReturnType_e NBS_ReturnType_e_CreateBlindSpotSemaphores()
{
	NBS_ReturnType_e rt = BS_NO_ERROR;
	BaseType_t xSemaphoreGiveState = pdFAIL;

	/*Create RightDis Semaphore*/
	RightDisSemaphoreHandler = xSemaphoreCreateBinary(); /*Create binary semaphore for right distance variable data.*/
	if(RightDisSemaphoreHandler == NULL) /*The semaphore could not be created*/
	{
		rt = BS_ERROR_COULD_NOT_CREATE_BINARY_SEMAPHORE;
	}
	xSemaphoreGiveState = xSemaphoreGive(RightDisSemaphoreHandler); /*Semaphore is initially given.*/
	if(xSemaphoreGiveState == pdFAIL) /*The semaphore can not be given.*/
	{
		rt = BS_ERROR_COULD_NOT_GIVE_SEMAPHORE;
	}

	/*Create LeftDis Semaphore*/
	LeftDisSemaphoreHandler = xSemaphoreCreateBinary(); /*Create binary semaphore for right distance variable data.*/
	if(LeftDisSemaphoreHandler == NULL) /*The semaphore could not be created*/
	{
		rt = BS_ERROR_COULD_NOT_CREATE_BINARY_SEMAPHORE;
	}
	xSemaphoreGiveState = xSemaphoreGive(LeftDisSemaphoreHandler); /*Semaphore is initially given.*/
	if(xSemaphoreGiveState == pdFAIL) /*The semaphore can not be given.*/
	{
		rt = BS_ERROR_COULD_NOT_GIVE_SEMAPHORE;
	}
	return rt;
}
/******************************************************************************************************/
/*******************************************freeRTOS Tasks*********************************************/


void vRightAreaHandler(void* arg)
{

	BaseType_t xSemaphoreTakeState = pdFAIL;
	BaseType_t xQueueSendState = errQUEUE_FULL;
	uint16_t warningMes = 'R';
	UBaseType_t uxHighWaterMark;
	uint8_t ID1 = 0;
	uint16_t data1 = 0;

	while(1)
	{
		xSemaphoreTakeState = xSemaphoreTake(binarySemaphoreHandler, portMAX_DELAY); /*Take The Semaphore.*/
		if(xSemaphoreTakeState == pdPASS)
		{
			vReadDataFromM4(RIGHT_ULTRASONIC_ID, &data1);
			ID1 = ((data1 & 0xF000) >> 12);
			while(ID1 != RIGHT_ULTRASONIC_ID)
			{
				vReadDataFromM4(RIGHT_ULTRASONIC_ID,&data1);
				ID1 = (data1 & 0xF000) >> 12;
			}
			xSemaphoreGive(binarySemaphoreHandler);
			xSemaphoreTakeState = xSemaphoreTake(RightDisSemaphoreHandler, portMAX_DELAY); /*Take The Semaphore.*/
			if(xSemaphoreTakeState == pdPASS) /*Semaphore is taken.*/
			{
				RightDis = (data1 & 0x0FFF);
				if((RightDis <= MIN_DISTANCE) && (RightDis > 4))
				{
			//		xQueueSendState = xQueueSendToBack(LCDQueue, &warningMes, portMAX_DELAY); /*Send the message to the LCD Queue*/
					BUZZER_on(RIGHT_SIGNAL_LED_PORT, RIGHT_LED_GPIO_Pin);
	/*				if(xQueueSendState == pdPASS)
					{
						printf("Message is sent to the Queue\n");
					}
					else
					{
						printf("Message is not sent to the Queue\n");
					}*/
				}
				else
				{
					BUZZER_off(RIGHT_SIGNAL_LED_PORT, RIGHT_LED_GPIO_Pin);
					printf("Right Distance is Safe\n");
				}
				xSemaphoreGive(RightDisSemaphoreHandler);
			}
			else
			{
				printf("Right Distance Semaphore Can not be taken");
			}
		}
		else /*The Semaphore can not be taken.*/
		{
			printf("The Semaphore is not available\n");
		}
		uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		vTaskDelay(100);
	}
}




void vLeftAreaHandler(void* arg)
{

	BaseType_t xSemaphoreTakeState = pdFAIL;
	BaseType_t xQueueSendState = errQUEUE_FULL;
	uint16_t warningMes = 'L';
	volatile UBaseType_t uxHighWaterMark;
	uint16_t data2 = 0;
	uint8_t ID1 = 0;
	while(1)
	{
		xSemaphoreTakeState = xSemaphoreTake(binarySemaphoreHandler, portMAX_DELAY);
		if(xSemaphoreTakeState == pdPASS)
		{
			vReadDataFromM4(LEFT_ULTRASONIC_ID, &data2);
			ID1 = ((data2 & 0xF000) >> 12);
			while(ID1 != LEFT_ULTRASONIC_ID)
			{
				vReadDataFromM4(LEFT_ULTRASONIC_ID,&data2);
				ID1 = (data2 & 0xF000) >> 12;
			}

			xSemaphoreGive(binarySemaphoreHandler);
			xSemaphoreTakeState = xSemaphoreTake(LeftDisSemaphoreHandler, portMAX_DELAY); /*Take The Semaphore.*/
			if(xSemaphoreTakeState == pdPASS) /*Semaphore is taken.*/
			{
				LeftDis = (data2 & 0x0FFF);
				if(LeftDis <= MIN_DISTANCE)
				{
					BUZZER_on(LEFT_SIGNAL_LED_PORT, LEFT_LED_GPIO_Pin);
		/*			xQueueSendState = xQueueSendToBack(LCDQueue, &warningMes, portMAX_DELAY);

					if(xQueueSendState == pdPASS)
					{
						printf("Message is sent to the Queue\n");
					}
					else
					{
						printf("Message is not sent to the Queue\n");
					}*/
				}
				else
				{
					BUZZER_off(LEFT_SIGNAL_LED_PORT, LEFT_LED_GPIO_Pin);
					printf("Left Distance is Safe\n");
				}
				xSemaphoreGive(LeftDisSemaphoreHandler);
			}
		}
		else
		{
			printf("The Semaphore is not available\n");
		}
		uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
		vTaskDelay(100);
	}
}
/*******************************************************************************************************/

void TurnSignalWarningTwo(void* arg)
{
	uint8_t flag1 = 0;
	uint8_t flag2 = 0;
	EventBits_t uxBits;
	BaseType_t xSemaphoreTakeState = pdFAIL;

	while(1)
	{
		uxBits = xEventGroupGetBits(xCreatedEventGroup);
		/*Take The Semaphores.*/
		if(flag2 == 0)
		{
			xSemaphoreTakeState = xSemaphoreTake(RightDisSemaphoreHandler, portMAX_DELAY); /*Take The Semaphore.*/
			if(xSemaphoreTakeState == pdPASS) /*Semaphore is taken.*/
			{
				if(((uxBits & BIT_0) != 0) && (RightDis <= MIN_DISTANCE)) /*(The driver drifts to right while it is a car in the right BS area).*/
				{
					flag1 = 1;
					BUZZER_on(GPIOB, GPIO_Pin_9);
				}
				else
				{
					flag1 = 0;
					BUZZER_off(GPIOB, GPIO_Pin_9);
				}

				xSemaphoreGive(RightDisSemaphoreHandler);
			}
			else
			{
				printf("Right Turn signal semaphore can not be taken");
			}
		}
		if(flag1 == 0)
		{
			xSemaphoreTakeState = xSemaphoreTake(LeftDisSemaphoreHandler, portMAX_DELAY); /*Take The Semaphore.*/
			if(xSemaphoreTakeState == pdPASS) /*Semaphore is taken.*/
			{
				if(((uxBits & BIT_2) != 0 ) && (LeftDis <= MIN_DISTANCE) ) /*Left Turn Signal is ON -The driver drifts to left, LeftDis <= MIN_DISTANCE.*/
				{
					/*xEventGroupWaitBits() returned because just BIT_2 was set (Left Turn Signal ON). */
					flag2 = 1;
					BUZZER_on(GPIOB, GPIO_Pin_9);
				}
				else
				{
					flag2 = 0;
					BUZZER_off(GPIOB, GPIO_Pin_9);
				}
				xSemaphoreGive(LeftDisSemaphoreHandler);
			}
			else
			{
				printf("Left Turn signal semaphore can not be taken");
			}
		}
		vTaskDelay(100);
	}
}


void vApplicationStackOverflowHook(TaskHandle_t xTask , char *pcTaskName)
{
	(void)pcTaskName;
	(void)xTask;
}
