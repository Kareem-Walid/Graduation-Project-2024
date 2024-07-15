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

extern uint16_t gCurrent_Angle;


signed char value = 0 ,value_old ,error = 0, delta_angle = 0;

/********************************************************************************************************************/
/***************************************Extern Global variables Section**********************************************/
extern SemaphoreHandle_t 	Offset_binarySemaphoreHandler;
extern int8_t	 			UARTCenterOffset;
extern QueueHandle_t     	LCDQueue;
extern EventGroupHandle_t xCreatedEventGroup;

/********************************************************************************************************************/
/**************************************Static Functions declaration**************************************************/
static NError_type_e NError_type_e_LKAS_CreateTasks(void);
/**************************************Scheduling Tasks Declaration**************************************************/
void vTaskLDW				(void*arg);
void vTaskLKAS				(void*arg);
void vServoError			(void* arg);

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
	BaseType_t xTaskCreate_vServoError;

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
			if((UARTCenterOffset > 0) && ((uxBits & BIT_0) == 0)) /*The Car drifts to right while right turn signal is OFF.*/
			{
				BUZZER_on(LK_SIGNAL_LED_PORT, LK_LED_GPIO_Pin);
			}
			else if((UARTCenterOffset < 0) && ((uxBits & BIT_2) == 0)) /*The Car drifts to left while left turn signal is OFF.*/
			{
				BUZZER_on(LK_SIGNAL_LED_PORT, LK_LED_GPIO_Pin);
			}
			else
			{
				BUZZER_off(LK_SIGNAL_LED_PORT, LK_LED_GPIO_Pin);
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
			if(UARTCenterOffset > 0)
			{
				gCurrent_Angle = CENTER_ANGLE - 6 * (UARTCenterOffset) ;
				if((gCurrent_Angle > 0) && (gCurrent_Angle < 180))
				{
					SERVO_MoveTo(&SEV ,gCurrent_Angle);
				}

			}else if(UARTCenterOffset < 0)
			{
				gCurrent_Angle = CENTER_ANGLE - 6 * (UARTCenterOffset) ;
				if((gCurrent_Angle > 0) && (gCurrent_Angle < 180))
				{
					SERVO_MoveTo(&SEV ,gCurrent_Angle);
				}
			}
			else
			{
				SERVO_MoveTo(&SEV ,CENTER_ANGLE);
			}
		}
		else{}
		xSemaphoreGive(Offset_binarySemaphoreHandler);
		vTaskDelay(100);
	}
}






//void vServoError(void* arg)
//{
//
//	while(1)
//	{
//		error = UARTCenterOffset - value_old;
//		if((error > -5) && (error  < 5))
//		{
//			delta_angle = 50 - 6 * (UARTCenterOffset);
//			if((delta_angle > 0) && (delta_angle < 180))
//			{
//				SERVO_MoveTo(&SEV ,delta_angle);
//			}
//			value_old = UARTCenterOffset;
//
//		}
//		else if((error < -5))
//		{
//			if(UARTCenterOffset  < -13)
//			{
//				delta_angle += 10;
//				if((delta_angle > 0) && (delta_angle < 180))
//				{
//					SERVO_MoveTo(&SEV ,delta_angle);
//				}
//			}
//			else
//			{
//				delta_angle -= 10;
//				if((delta_angle > 0) && (delta_angle < 180))
//				{
//					SERVO_MoveTo(&SEV ,delta_angle);
//				}
//			}
//
//		}
//		else if((error  > 5))
//		{
//			if(UARTCenterOffset  < -13)
//			{
//				delta_angle -= 10;
//				if((delta_angle > 0) && (delta_angle < 180))
//				{
//					SERVO_MoveTo(&SEV ,delta_angle);
//				}
//			}
//			else
//			{
//				delta_angle += 10;
//				if((delta_angle > 0) && (delta_angle < 180))
//				{
//					SERVO_MoveTo(&SEV ,delta_angle);
//				}
//			}
//			vTaskDelay(50);
//		}
//	}
//}
