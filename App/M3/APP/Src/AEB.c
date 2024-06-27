
/*---------------------------------- Includes Section ------------------------------------ */
#include "AEB.h"

#include <math.h>

TaskHandle_t vAEB_Task_Handler;


uint16_t gENCs_Speed;
uint16_t gCar_Direction;
uint16_t gCurrent_Speed;

uint16_t gFront_Distance;

uint16_t gBreaking_Distance;
uint16_t gWarning_Distance;

SemaphoreHandle_t Front_Distance_Semaphore_Handler;
SemaphoreHandle_t Current_Speed_Semaphore_Handler;
SemaphoreHandle_t Motors_Semaphore_Handler;

extern EventBits_t ACC_Bits;

void vCar_Task(void * pvParameter);
void vCalculations_Task(void * pvParameter);


void vAEB_Init(void)
{

	xTaskCreate(vAEB_Task, "AEB", 128,( void * )NULL, 3,&vAEB_Task_Handler);
	xTaskCreate(vCar_Task, "AEB", 128,( void * )NULL, 1, NULL);
	xTaskCreate(vCalculations_Task, "AEB", 128,( void * )NULL, 1, NULL);


	/* Create semaphores */
	Front_Distance_Semaphore_Handler = xSemaphoreCreateBinary();
	xSemaphoreGive(Front_Distance_Semaphore_Handler);

	Current_Speed_Semaphore_Handler = xSemaphoreCreateBinary();
	xSemaphoreGive(Current_Speed_Semaphore_Handler);

	Motors_Semaphore_Handler = xSemaphoreCreateBinary();
	xSemaphoreGive(Motors_Semaphore_Handler);


}


float K  = 0;
uint16_t Max_Speed;
uint16_t Loc_Object_Distance = 0;

void vAEB_Task(void * pvParameter)
{


	for(;;)
	{

		if(gFront_Distance > gWarning_Distance && gCurrent_Speed !=0 )
		{
			BUZZER_off(AEB_LED_PORT, AEB_LED_GPIO_Pin);

			 Max_Speed = gCurrent_Speed ;
			 K = ( (float)gCurrent_Speed / (gWarning_Distance - gBreaking_Distance));
			 K = roundf( K * 100) / 100 ;

		}else if(gFront_Distance <= gWarning_Distance && gFront_Distance > gBreaking_Distance)
		{
			Loc_Object_Distance = gFront_Distance;
			/* Turn-on led */
			BUZZER_on(AEB_LED_PORT, AEB_LED_GPIO_Pin);

			/* ---------- slow down mechanism ------- */
			 gCurrent_Speed = K * (gFront_Distance - gBreaking_Distance);
			/* -------------------------------------------- */

		}else if(gFront_Distance < gBreaking_Distance )
		{

			BUZZER_on(AEB_LED_PORT, AEB_LED_GPIO_Pin);
			xSemaphoreTake(Motors_Semaphore_Handler, portMAX_DELAY);
			gCar_Direction = STOP;
			gCurrent_Speed = 0;
			xSemaphoreGive(Motors_Semaphore_Handler);

		}else if(gFront_Distance > Loc_Object_Distance && gCurrent_Speed ==0 ){

			BUZZER_off(AEB_LED_PORT, AEB_LED_GPIO_Pin);

		}else{

		}

		// Periodicity of the Task
		vTaskDelay(100);

	}
}





void vCar_Task(void * pvParameter)
{

	while(1)
	{
		/* Direction of the Motors */
		xSemaphoreTake(Motors_Semaphore_Handler, portMAX_DELAY);

		switch(gCar_Direction)
		{
		case FORWARD:
			Motor_SetCarDir(&Rmotor,&Lmotor,FORWARD);
			break;

		case REVERSE:
			Motor_SetCarDir(&Rmotor, &Lmotor,REVERSE);
			break;

		case STOP:
			Motor_SetCarDir(&Rmotor,&Lmotor,STOP);
			break;
		}
		xSemaphoreGive(Motors_Semaphore_Handler);

		/* --------- Speed of the motors --------*/


		xSemaphoreTake(Current_Speed_Semaphore_Handler, portMAX_DELAY);
		Motor_SetSpeed(&Rmotor,gCurrent_Speed);
		Motor_SetSpeed(&Lmotor,gCurrent_Speed);
		xSemaphoreGive(Current_Speed_Semaphore_Handler);



		vTaskDelay(100);
	}
}


void vCalculations_Task(void * pvParameter)
{

	uint16_t US1_ID , R_ENC_ID, L_ENC_ID;
	uint16_t US1_Temp_Data , R_ENC_tData , L_ENC_tData;


	uint16_t Loc_Right_ENC_Speed = 0;
	uint16_t Loc_Left_ENC_Speed = 0;

	while(1)
	{
		/*------ Get data of Front US ------*/
		xSemaphoreTake(Front_Distance_Semaphore_Handler, portMAX_DELAY);
		vReadDataFromM4(FRONT_US_ID,&US1_Temp_Data);
		US1_ID = ((US1_Temp_Data & 0xF000) >> 12);
		while(US1_ID != FRONT_US_ID )
		{
			vReadDataFromM4(FRONT_US_ID,&US1_Temp_Data);
			US1_ID = (US1_Temp_Data & 0xF000) >> 12;
		}

		gFront_Distance = (US1_Temp_Data & 0x0FFF);
		xSemaphoreGive(Front_Distance_Semaphore_Handler);


		/*----------- Get data of Right and Left ENC ------- */
		xSemaphoreTake(Current_Speed_Semaphore_Handler, portMAX_DELAY);
		vReadDataFromM4(RIGHT_ENC_ID,&R_ENC_tData);
		R_ENC_ID = ((R_ENC_tData & 0xF000) >> 12);
		while(R_ENC_ID != RIGHT_ENC_ID )
		{
			vReadDataFromM4(RIGHT_ENC_ID,&R_ENC_tData);
			R_ENC_ID = ((R_ENC_tData & 0xF000) >> 12);
		}
		Loc_Right_ENC_Speed = (R_ENC_tData  & 0x0FFF);


		vReadDataFromM4(LEFT_ENC_ID,&L_ENC_tData);
		L_ENC_ID = ((L_ENC_tData & 0xF000) >> 12);
		while(L_ENC_ID != LEFT_ENC_ID )
		{
			vReadDataFromM4(LEFT_ENC_ID,&L_ENC_tData);
			L_ENC_ID = ((L_ENC_tData & 0xF000) >> 12);
		}
		Loc_Left_ENC_Speed = (L_ENC_tData  & 0x0FFF);

		gENCs_Speed = ((Loc_Right_ENC_Speed + Loc_Left_ENC_Speed) / 2 );
		xSemaphoreGive(Current_Speed_Semaphore_Handler);

		// Calculate Breaking and Warning Distance
		gBreaking_Distance = (BREAKING_DISTANCE_CONST * gENCs_Speed);
		gWarning_Distance =  (WARNING_DISTANCE_CONST  * gENCs_Speed);

		vTaskDelay(100);
	}
}

