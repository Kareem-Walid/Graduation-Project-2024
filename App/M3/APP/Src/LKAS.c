/*
 * LKAS.c
 * Author: Abeer Sobhy
 */

/***********************************************Includes Section****************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "STD_TYPES.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"
#include "event_groups.h"

#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"

#include "SERVO.h"

#include "SysInit.h"
#include "LKAS.h"

/********************************************************************************************************************/
/********************************************************MACROs Section**********************************************/

/********************************************************************************************************************/
/*******************************************************Global Variables Section*************************************/
TaskHandle_t pxLKASCreated;

//uint16_t gCurrent_Angle;

/********************************************************************************************************************/
/***************************************Extern Global variables Section**********************************************/
extern SemaphoreHandle_t 	Offset_binarySemaphoreHandler;
extern int16_t	 			CenterOffset;
extern QueueHandle_t     	LCDQueue;
extern EventGroupHandle_t xCreatedEventGroup;

/********************************************************************************************************************/
/**************************************Static Functions declaration**************************************************/
static void vEXTI_Init(void);
static NError_type_e NError_type_e_LKAS_CreateTasks(void);
/**************************************Scheduling Tasks Declaration**************************************************/
void vTaskLDW				(void*arg);
void vTaskLKAS				(void*arg);
/********************************************************************************************************************/
/****************************************Atomic Functions'DEF Section************************************************/
NError_type_e Error_type_t_LKASInit(void)
{
	NError_type_e rt_type = LKAS_NO_ERROR;

	/*Create The LKAS Tasks.*/
	rt_type = NError_type_e_LKAS_CreateTasks();


	return rt_type;
}



static NError_type_e NError_type_e_LKAS_CreateTasks(void)
{
	NError_type_e rt_type = LKAS_NO_ERROR;

	BaseType_t xTaskCreate_vTaskLKAS;
	BaseType_t xTaskCreate_vTaskLDW;


	/*Create the tasks then check if it is actually created or not.*/
	xTaskCreate_vTaskLKAS =  xTaskCreate(vTaskLKAS,"vTaskLKAS", 100, NULL, vTaskLKAS_PRIORITY,&pxLKASCreated);
	if(xTaskCreate_vTaskLKAS != pdPASS)
	{
		rt_type = TASK_CREATION_ERROR;
	}

	xTaskCreate_vTaskLDW = xTaskCreate(vTaskLDW,"vTaskLDW", 100, NULL, vTaskLDW_PRIORITY, NULL);
	if(xTaskCreate_vTaskLDW != pdPASS)
	{
		rt_type = TASK_CREATION_ERROR;
	}

	/*LKAS Task is initially Suspended.*/
	vTaskSuspend(pxLKASCreated);

	return rt_type;
}

/***********************************************************************/
/**********************Scheduling Tasks*********************************/
void vTaskLDW(void* arg)
{
	uint16_t WarningMes = 'W';
	BaseType_t xQueueSendState = errQUEUE_FULL;
	EventBits_t uxBits;
	BaseType_t xSemaphoreTakeState = pdFAIL;

	while(1)
	{
		uxBits = xEventGroupGetBits(xCreatedEventGroup);/* Wait a maximum of 100ms for either bit to be set. */
		xSemaphoreTakeState = xSemaphoreTake(Offset_binarySemaphoreHandler, portMAX_DELAY); /*Take The Semaphore.*/
		if(xSemaphoreTakeState == pdPASS)
		{
			if((CenterOffset > 0) && ((uxBits & BIT_0) == 0)) /*The Car drifts to right while right turn signal is OFF.*/
			{
				BUZZER_on(LK_SIGNAL_LED_PORT, LK_LED_GPIO_Pin);
//				xQueueSendState = xQueueSendToBack(LCDQueue, &WarningMes, portMAX_DELAY); /*Send the message to the LCD Queue*/
//				if(xQueueSendState == pdPASS)
//				{
//					printf("Message is sent to the LCD Queue\n");
//				}
//				else
//				{
//					printf("Message is not sent to the LCD Queue\n");
//				}
			}
			else if((CenterOffset < 0) && ((uxBits & BIT_2) == 0)) /*The Car drifts to left while left turn signal is OFF.*/
			{
				BUZZER_on(LK_SIGNAL_LED_PORT, LK_LED_GPIO_Pin);
//				xQueueSendState = xQueueSendToBack(LCDQueue, &WarningMes, portMAX_DELAY); /*Send the message to the LCD Queue*/
//				if(xQueueSendState == pdPASS)
//				{
//					printf("Message is sent to the LCD Queue\n");
//				}
//				else
//				{
//					printf("Message is not sent to the LCD Queue\n");
//				}
			}
			else
			{
				BUZZER_off(LK_SIGNAL_LED_PORT, LK_LED_GPIO_Pin);
				printf("Save");
			}
		}
		else{}
		xSemaphoreGive(Offset_binarySemaphoreHandler);
		vTaskDelay(100);
	}
}



void vTaskLKAS(void*arg)
{
	EventBits_t uxBits;
	BaseType_t xSemaphoreTakeState = pdFAIL;

	while(1)
	{
		uxBits = xEventGroupGetBits(xCreatedEventGroup);/* Wait a maximum of 100ms for either bit to be set. */
		xSemaphoreTakeState = xSemaphoreTake(Offset_binarySemaphoreHandler, portMAX_DELAY); /*Take The Semaphore.*/
		if(xSemaphoreTakeState == pdPASS)
		{
			if((CenterOffset > 0) && ((uxBits & BIT_0) == 0)) /*The Car drifts to right while right turn signal is OFF.*/
			{

			}
			else if((CenterOffset < 0) && ((uxBits & BIT_2) == 0)) /*The Car drifts to left while left turn signal is OFF.*/
			{

			}
			else
			{
				/*Move forward.*/
				printf("Move Forward");
//				SERVO_MoveTo(&SEV ,(float)af_Angle);
			}
		}
		else{}
		xSemaphoreGive(Offset_binarySemaphoreHandler);
		vTaskDelay(100);
	}
}
