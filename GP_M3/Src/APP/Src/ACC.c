
#include "ACC.h"

TaskHandle_t vACC_Task_Handler;
TaskHandle_t vSign_Task_Handler;


extern SemaphoreHandle_t Motors_Semaphore_Handler;

extern uint16_t gDesired_Speed;
extern uint8_t  gCar_Direction;

extern uint16_t gFront_Distance;

extern uint8_t gCurrent_Speed;
extern uint8_t gReceived_Sign;

extern uint16_t gBreaking_Distance;
extern uint16_t gWarning_Distance;




void vACC_Init(void)
{

	xTaskCreate(vACC_Task, "acc main ", 128,( void * )NULL, 1, &vACC_Task_Handler);
	xTaskCreate(vACC_Sign, "sign", 128,( void * )NULL, 1, &vSign_Task_Handler);


	/* Suspend both tasks untill user turn on the acc mode */
	vTaskSuspend(vACC_Task_Handler);
	vTaskSuspend(vSign_Task_Handler);

}




void vACC_Task(void * pvParameter)
{
	float K;
	uint16_t Loc_Front_Car_Distance = 0;
	while(1)
	{

		if(gFront_Distance > gWarning_Distance && gFront_Distance > Loc_Front_Car_Distance )
		{
			xSemaphoreTake(Motors_Semaphore_Handler, portMAX_DELAY);
			gCar_Direction = FORWARD;
			gCurrent_Speed = gDesired_Speed;
			xSemaphoreGive(Motors_Semaphore_Handler);

			/* ----- Calculate Slow down Parameters ---- */
			K = ( (float)gCurrent_Speed / ( gWarning_Distance - gBreaking_Distance) );
			K = roundf( K * 100) / 100 ;

		}else if(gFront_Distance < gWarning_Distance && gFront_Distance > gBreaking_Distance)
		{
			Loc_Front_Car_Distance = gFront_Distance;

			/* ---------- TODO: slow down mechanism ------- */
			gCurrent_Speed = K * (gFront_Distance - gBreaking_Distance);
			if(gCurrent_Speed < 10)
			{
				gCurrent_Speed = 0;
				gCar_Direction = STOP;
			}
			/*---------------------------------------------*/

		}else if(gFront_Distance <= gBreaking_Distance)
		{
			xSemaphoreTake(Motors_Semaphore_Handler, portMAX_DELAY);
			gCar_Direction = STOP;
			gCurrent_Speed = 0;
			xSemaphoreGive(Motors_Semaphore_Handler);
		}else{}
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






