


#include "ACC.h"

TaskHandle_t vACC_Task_Handler;
TaskHandle_t vSign_Task_Handler;

extern SemaphoreHandle_t Motors_Semaphore_Handler;

extern uint16_t gDesired_Speed;
extern uint16_t gCurrent_Speed;
extern uint16_t gCar_Direction;

extern uint16_t gFront_Distance;


extern uint8_t gReceived_Sign;


extern uint16_t gBreaking_Distance;
extern uint16_t gWarning_Distance;

/* --------------- Event Group --------------- */



void vACC_Init(void)
{

	// xTaskCreate(vCruise_Task, "Cruise Mode ", 128,( void * )NULL, 1, &Cruise_Task_Handler);
	// xTaskCreate(vFollow_Task, "Follow Mode ", 128,( void * )NULL, 1, &Follow_Task_Handler);

	xTaskCreate(vACC_Task, "acc main ", 128,( void * )NULL, 1, &vACC_Task_Handler);
	xTaskCreate(vACC_Sign, "sign", 128,( void * )NULL, 1, &vSign_Task_Handler);


	/* Suspend both tasks untill user turn on the acc mode */
	vTaskSuspend(vACC_Task_Handler);
	vTaskSuspend(vSign_Task_Handler);

	/* -- Event Group ------ */
	ACC_EventGroup = xEventGroupCreate();
}




uint16_t Loc_Front_Car_Distance = 0;

void vACC_Task(void * pvParameter)
{

	while(1)
	{


		if(gFront_Distance > gWarning_Distance && gFront_Distance > Loc_Front_Car_Distance )
		{
			xSemaphoreTake(Motors_Semaphore_Handler, portMAX_DELAY);
			gCar_Direction = FORWARD;
			gCurrent_Speed = gDesired_Speed;
			xSemaphoreGive(Motors_Semaphore_Handler);

		}else if(gFront_Distance < gWarning_Distance && gFront_Distance > gBreaking_Distance)
		{
			Loc_Front_Car_Distance = gFront_Distance;
			/* ---------- TODO: slow down mechanism ------- */

			/*----------------------------------*/

		}else if(gFront_Distance <= gBreaking_Distance)
		{
			xSemaphoreTake(Motors_Semaphore_Handler, portMAX_DELAY);
			gCar_Direction = STOP;
			gCurrent_Speed = 0;
			xSemaphoreGive(Motors_Semaphore_Handler);
		}else
		{

		}
		vTaskDelay(100);

	}
}

void vACC_Sign(void * pvParameter)
{


	while(1)
	{
		switch(gReceived_Sign)
		{

		case SPEED_30:
			gDesired_Speed = SPEED_MAPPED_TO_30;
			break ;

		case SPEED_60:
			gDesired_Speed = SPEED_MAPPED_TO_60;
			break ;

		case SPEED_90:
			gDesired_Speed = SPEED_MAPPED_TO_90;
			break ;

		case STOP_SIGN:
			gDesired_Speed = 0;
			gCar_Direction = STOP;
			break ;
		}

		vTaskDelay(100);
	}
}







//void vFollow_Task(void * pvParameter)
//{
//
//
//	for(;;)
//	{
//		if(gDesired_Distance <= gFront_Distance)
//		{
//			xSemaphoreTake(Motors_Semaphore_Handler, portMAX_DELAY);
//			gCar_Direction = FORWARD;
//			gCurrent_Speed = gDesired_Speed;
//			xSemaphoreGive(Motors_Semaphore_Handler);
//
//		}else{
//
//			// Stop Car
//			xSemaphoreTake(Motors_Semaphore_Handler, portMAX_DELAY);
//			gCar_Direction = STOP;
//			gCurrent_Speed = 0;
//			xSemaphoreGive(Motors_Semaphore_Handler);
//
//		}
//
//
//
//		// Periodicity of the Task
//		vTaskDelay(100);
//
//	}
//}





//void vCruise_Task(void * pvParameter)
//{
//
//	for(;;)
//	{
//
//		/* ------ if the user increase speed --- */
//		if( gDesired_Speed < gCurrent_Speed )
//		{
//			gCurrent_Speed = gDesired_Speed;
//		}
//		//		}else if (gDesired_Speed > gSign_Limit_Speed )
//		//		{
//		//			 // gCurrent_Speed = gSign_Limit_Speed ;
//		//			gCurrent_Speed = 0;
//		//
//		//		}else{
//		//			/* Stay as you are :) */
//		//		}
//
//		// Periodicity of the Task
//
//
//
//	}
//}



