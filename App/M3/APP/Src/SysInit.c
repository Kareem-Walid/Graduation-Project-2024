/*
 * SysInit.c
 * Author: Abeer Sobhy
 */

/****************************************Include Section**********************************************/
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
#include "stm32f10x_spi.h"

#include "BUZZER.h"
#include "SERVO.h"

#include "SysInit.h"


/* ------ ACC & AEB -------- */
extern TaskHandle_t vACC_Task_Handler;
extern TaskHandle_t vSign_Task_Handler;
extern TaskHandle_t vAEB_Task_Handler;


uint8_t gCurrent_Speed;
uint8_t gCar_Direction;

extern uint16_t gFront_Distance;




uint16_t gDesired_Speed;
uint8_t gReceived_Sign;
uint16_t gSpeed_Up;



/* ------------------------------------ */

uint16_t gCurrent_Angle = 0;

/*****************************************************************************************************/
/*****************************************MACROs Section**********************************************/
#define TSR_ID 		1
#define LKAS_ID 	0

/*****************************************************************************************************/
/****************************************Global Variables Section*************************************/
SemaphoreHandle_t binarySemaphoreHandler;
SemaphoreHandle_t Offset_binarySemaphoreHandler;

SemaphoreHandle_t Current_Angle_Semaphore_Handler;
extern SemaphoreHandle_t Current_Speed_Semaphore_Handler;

SemaphoreHandle_t Desired_Speed_Semaphore_Handler;
SemaphoreHandle_t Desired_Distance_Semaphore_Handler;


QueueHandle_t     LCDQueue;
/* Declare a variable to hold the created event group. */
EventGroupHandle_t xCreatedEventGroup;

volatile int8_t UARTCenterOffset = 0;

/*****************************************************************************************************/
/***************************************Extern Global variables Section********************************/
extern TaskHandle_t pxLKASCreated;

/*****************************************************************************************************/
/**************************************Static Functions declaration************************************/
static NSysInit_e vSysInit_CreateSemaphore();
static NSysInit_e vSysInit_CreateQueues();
static NSysInit_e vSysInit_CreateTasks();
static NSysInit_e SysInit_CreateEventGroups();

void vSendMessageViaUSART(void* arg);
void vReadDataFromUART(void* arg);


/******************************************************************************************************/

/****************************************Functions DEF Section******************************************/
/*
 * SysInit is used to initialize all the ECUAL Components.
 * All ECUAL Initialization functions of this project must be called within this function.
 * It must be called before any initialize function of this project & before the starting of the scheduler
 */
int i;

NSysInit_e SysInit(void)
{
	NSysInit_e rt = SysInit_NO_ERROR;

	Car_Init();
	gCurrent_Speed = 0;
	gCar_Direction = FORWARD;
	SERVO_MoveTo(&SEV,CENTER_ANGLE);

	BUZZER_off(AEB_LED_PORT, AEB_LED_GPIO_Pin);
	BUZZER_off(RIGHT_SIGNAL_LED_PORT, LEFT_LED_GPIO_Pin);
	BUZZER_off(LEFT_SIGNAL_LED_PORT, RIGHT_LED_GPIO_Pin);
	BUZZER_off(LK_SIGNAL_LED_PORT, LK_LED_GPIO_Pin);

	/*********************************************Objects Creation**************************************/
	rt = vSysInit_CreateSemaphore();
	rt = vSysInit_CreateTasks();
	rt = vSysInit_CreateQueues();
	rt = SysInit_CreateEventGroups();

	return rt;
}

/**************************************One Shot Tasks Definition.************************************/
static NSysInit_e vSysInit_CreateSemaphore()
{
	NSysInit_e rt = SysInit_NO_ERROR;
	BaseType_t xSemaphoreGiveState = pdFAIL;

	binarySemaphoreHandler = xSemaphoreCreateBinary(); /*Create binary semaphore for the function of receiving data*/
	if(binarySemaphoreHandler == NULL) /*The semaphore could not be created*/
	{
		rt = SysInit_ERROR_COULD_NOT_CREATE_BINARY_SEMAPHORE;
	}

	xSemaphoreGiveState = xSemaphoreGive(binarySemaphoreHandler); /*Semaphore is initially given.*/
	if(xSemaphoreGiveState == pdFAIL) /*The semaphore can not be given.*/
	{
		rt = SysInit_ERROR_COULD_NOT_GIVE_SEMAPHORE;
	}

	Offset_binarySemaphoreHandler = xSemaphoreCreateBinary(); /*Create binary semaphore for the function of receiving data*/
	if(Offset_binarySemaphoreHandler == NULL) /*The semaphore could not be created*/
	{
		rt = SysInit_ERROR_COULD_NOT_CREATE_BINARY_SEMAPHORE;
	}

	xSemaphoreGiveState = xSemaphoreGive(Offset_binarySemaphoreHandler); /*Semaphore is initially given.*/
	if(xSemaphoreGiveState == pdFAIL) /*The semaphore can not be given.*/
	{
		rt = SysInit_ERROR_COULD_NOT_GIVE_SEMAPHORE;
	}

	/* -------------------------- APP Semaphore ------------------------- */

	Current_Angle_Semaphore_Handler = xSemaphoreCreateBinary();
	xSemaphoreGive(Current_Angle_Semaphore_Handler);

	Current_Speed_Semaphore_Handler = xSemaphoreCreateBinary();
	xSemaphoreGive(Current_Speed_Semaphore_Handler);

	Desired_Speed_Semaphore_Handler = xSemaphoreCreateBinary();
	xSemaphoreGive(Desired_Speed_Semaphore_Handler);

	Desired_Distance_Semaphore_Handler = xSemaphoreCreateBinary();
	xSemaphoreGive(Desired_Distance_Semaphore_Handler);



	/* ------------------------------------------------------------------- */


	return rt;
}
static NSysInit_e vSysInit_CreateQueues()
{
	NSysInit_e rt = SysInit_NO_ERROR;

	LCDQueue = xQueueCreate(MAX_LCD_MESSAGES, LEN_LCD_MESSAGE); /*Create LCD Queue.*/
	if(LCDQueue == NULL) /*The Queue could not be created*/
	{
		rt = SysInit_xQueueCreate_ERROR;
	}
	return rt;
}
static NSysInit_e vSysInit_CreateTasks()
{
	NSysInit_e rt = SysInit_NO_ERROR;
	BaseType_t xTaskCreate_vSendMessageViaUSART_Handler;
	BaseType_t xTaskCreate_vReadDataFromUART;

	/*Create the tasks then check if it is actually created or not.*/
	//	xTaskCreate_vSendMessageViaUSART_Handler =  xTaskCreate(vSendMessageViaUSART,"vSendMessageViaUSART", 50, NULL, vSendMessageViaUSART_PRIORITY,NULL); /*Create LCD Task, with priority 1, 50 byte.*/
	//	if(xTaskCreate_vSendMessageViaUSART_Handler != pdPASS) /*The task could not be created*/
	//	{
	//		rt = SysInit_ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	//	}
	//	xTaskCreate_vReadDataFromUART =  xTaskCreate(vReadDataFromUART,"vReadDataFromUART", 100, NULL, vReadDataFromUART_PRIORITY,NULL); /*Create UART Task, with priority 2, 100 byte.*/
	//	if(xTaskCreate_vReadDataFromUART != pdPASS) /*The task could not be created*/
	//	{
	//		rt = SysInit_ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	//	}
	return rt;
}


static NSysInit_e SysInit_CreateEventGroups()
{
	NSysInit_e rt = SysInit_NO_ERROR;

	/* Attempt to create the event group. */
	xCreatedEventGroup = xEventGroupCreate();
	/* Was the event group created successfully? */
	if( xCreatedEventGroup == NULL )
	{
		/* The event group was not created because there was insufficient
	FreeRTOS heap available. */
		rt = SysInit_ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	}
	else
	{
		/* The event group was created. */
	}
	return rt;
}

/*****************************************************************************************/
/* These Functions must be treated as a critical section
 * Can be called from any task to collect the sensors'data
 ******************************************************************************************/

void vReadDataFromM4(uint16_t ID, uint16_t* data)
{
	SPI_I2S_SendData(SPI2 , ID);
	*data = SPI_I2S_ReceiveData(SPI2);
}

/*************************************************************************************************/
/**************************************** Scheduling Tasks*****************************************/

//void vSendMessageViaUSART(void* arg)
//{
//	BaseType_t xQueueReceiveState; /*LCD Queue receiving state */
//	uint16_t receivedMes = 0; /*16*8 Byte for the received message.*/
//	volatile UBaseType_t uxHighWaterMark;
//
//	while(1)
//	{
//		/*Read the First Message From the Queue.*/
//		xQueueReceiveState = xQueueReceive(LCDQueue, &receivedMes, 50);
//		if(xQueueReceiveState == pdPASS) /*Message is received successfully.*/
//		{
//			USART_SendData(USART3, receivedMes);
//			printf("Message is successfully received\n");
//		}
//		else
//		{
//			printf("Message is not received\n");
//		}
//		uxHighWaterMark = uxTaskGetStackHighWaterMark( NULL );
//		vTaskDelay(100);
//	}
//}


/*************************************************************************************************/






uint16_t RasPI_ReceivedData = 0;
uint8_t ACC_State = OFF;
uint8_t RightSignalFlag = 0;
uint8_t LeftSignalFlag = 0;


void USART3_IRQHandler(void)
{
	// uint8_t ID = 0;
	EventBits_t uxBits;
	// static uint8_t ACC_State = OFF;
	// static uint8_t RightSignalFlag = 0;
	// static uint8_t LeftSignalFlag = 0;
	static uint8_t LKSignalFlag = 0;
	BaseType_t xSemaphoreTakeState = pdFAIL;


	RasPI_ReceivedData = USART_ReceiveData(USART3);


	if(RasPI_ReceivedData >=1 && RasPI_ReceivedData <= 11)
	{
		switch (RasPI_ReceivedData)
		{

		/* --------- Control Directions ------*/
		case CAR_FORWARD:  //1
			gCar_Direction = FORWARD;
			break;

		case CAR_RIGHT:   //2
			if(gCurrent_Angle < MAX_ANGLE)
			{
				// xSemaphoreTake(Current_Angle_Semaphore_Handler, portMAX_DELAY);
				gCurrent_Angle += 15;
				//xSemaphoreGive(Current_Angle_Semaphore_Handler);
				SERVO_MoveTo(&SEV, gCurrent_Angle);
			}
			break;

		case CAR_BACKWORD:  //3
			gCar_Direction = REVERSE;
			vTaskResume(vAEB_Task_Handler);
			vTaskSuspend(vACC_Task_Handler);
			vTaskSuspend(vSign_Task_Handler);
			break;

		case CAR_LEFT:  //4
			if(gCurrent_Angle > MIN_ANGLE)
			{
				//xSemaphoreTake(Current_Angle_Semaphore_Handler, portMAX_DELAY);
				gCurrent_Angle -= 15;
				//xSemaphoreGive(Current_Angle_Semaphore_Handler);
				SERVO_MoveTo(&SEV, gCurrent_Angle);
			}
			break;

			/*---------- Control Speed ----------*/
		case SPEED_INC:  //5
			if(gCurrent_Speed < MAX_SPEED_ && gCar_Direction != STOP)
			{
			xSemaphoreTake(Current_Speed_Semaphore_Handler, portMAX_DELAY);
			gCurrent_Speed += ( gCurrent_Speed == 0 )? 15 : 10;
			// gSpeed_Up = gCurrent_Speed;
			xSemaphoreGive(Current_Speed_Semaphore_Handler);
			}
			break;

		case SPEED_DEC: //6
			if (gCurrent_Speed >= MIN_SPEED && gCar_Direction != STOP)
			{
				xSemaphoreTake(Current_Speed_Semaphore_Handler, portMAX_DELAY);
				gCurrent_Speed -= ( gCurrent_Speed == 15 )? 15 : 10;
				// gSpeed_Up = gCurrent_Speed;
				xSemaphoreGive(Current_Speed_Semaphore_Handler);
			}
			break;

		case CAR_STOP:  //7
			gCar_Direction = STOP;
			gCurrent_Speed = 0;
			vTaskResume(vAEB_Task_Handler);
			vTaskSuspend(vACC_Task_Handler);
			vTaskSuspend(vSign_Task_Handler);
			break;

			/*------------- ACC ---------------*/

		case ACC_ON_OFF : //8
			ACC_State = !ACC_State;
			if(ACC_State == ON)
			{
				gDesired_Speed = gCurrent_Speed;
				vTaskSuspend(vAEB_Task_Handler);
				vTaskResume(vACC_Task_Handler);


			}else if (ACC_State == OFF)
			{
				vTaskResume(vAEB_Task_Handler);
				vTaskSuspend(vACC_Task_Handler);
				vTaskSuspend(vSign_Task_Handler);
			}
			break;

			/* ---------------- LK --------------------*/

		case LK_ON_OFF: //9
			if(LKSignalFlag == 0) /*LK is ON.*/
			{
				xTaskResumeFromISR(pxLKASCreated);
				LKSignalFlag = 1;
			}
			else if(LKSignalFlag == 1)  /*LK is OFF.*/
			{
				vTaskSuspend(pxLKASCreated);
				LKSignalFlag = 0;
			}
			break;


		case RIGHT_TURN_SIGNAL:   // A
			if(RightSignalFlag == 0)
			{
				RightSignalFlag = 1;
				uxBits = xEventGroupSetBits(xCreatedEventGroup, BIT_0);/* The bit being set. */
				if((uxBits & BIT_0) == 0)
				{
					printf("BIT 0 IS NOT SET");
				}
				else
				{}
			}
			else if(RightSignalFlag == 1) /*Right Turn Signal OFF*/
			{
				uxBits = xEventGroupClearBits(xCreatedEventGroup, BIT_0 );/* The bits being cleared. */
				RightSignalFlag = 0;
			}
			break;


		case LEFT_TURN_SIGNAL:   // B
			if((LeftSignalFlag == 0))
			{
				LeftSignalFlag = 1;
				uxBits = xEventGroupSetBits(xCreatedEventGroup, BIT_2);/* The bit being set. */
				if((uxBits & BIT_2) == 0)
				{
					printf("BIT 2 IS NOT SET");
				}
				else
				{}
			}
			else if(LeftSignalFlag == 1)  /*Left Turn Signal OFF.*/
			{
				uxBits = xEventGroupClearBits(xCreatedEventGroup, BIT_2);/* The bits being cleared. */
				LeftSignalFlag = 0;
			}
			break;
		}
	}else if(RasPI_ReceivedData >=12 && RasPI_ReceivedData <= 15)
	{
		vTaskResume(vSign_Task_Handler);
		gReceived_Sign = (int8_t)RasPI_ReceivedData;

	}else if (RasPI_ReceivedData >=16 && RasPI_ReceivedData < 255)
	{
		xSemaphoreTakeState = xSemaphoreTake(Offset_binarySemaphoreHandler, portMAX_DELAY); /*Take The Semaphore.*/
		if(xSemaphoreTakeState == pdPASS)
		{
			UARTCenterOffset = (int8_t)RasPI_ReceivedData - 119;
		}
		else{}
		xSemaphoreGive(Offset_binarySemaphoreHandler);
	}else{

	}
}





