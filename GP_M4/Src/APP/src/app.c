/*****************************************************Include Section**********************************************/
#include "stm32f4xx.h"

#include "FreeRTOS.h"
#include "task.h"

#include "semphr.h"
#include "queue.h"
#include "event_groups.h"

#include "Initialize_file_M4.h"

#include "app.h"

/**************************************** Global Variables Section**************************************************/
uint16_t gFront_Distance;
uint16_t gRight_Distance;
uint16_t gLeft_Distance;

uint16_t Right_ENC_Speed;
uint16_t Left_ENC_Speed;



/*******************************************************************************************************************/
/*************************************Static Functions' Declaration*************************************************/
static NSys_ReturnType_e 	vAppTaskCreate();
/*******************************************************************************************************************/
/*************************************Scheduling Functions' Declaration*********************************************/
void vTaskGetDistance		(void* arg);
void vTaskGetSpeed			(void* arg);

/********************************************Atomic Functions*******************************************************/
NSys_ReturnType_e vSysInit()
{
	NSys_ReturnType_e rt = Sys_NO_ERROR;

	rt = vAppTaskCreate();
	Car_Init();
	return rt;
}


static NSys_ReturnType_e vAppTaskCreate()
{
	NSys_ReturnType_e rt_type = Sys_NO_ERROR;

	BaseType_t vTaskGetDistance_Handler;
	BaseType_t vTaskGetSpeed_Handler;

	/*Create the tasks then check if it is actually created or not.*/
	vTaskGetDistance_Handler =  xTaskCreate(vTaskGetDistance,"vTaskGetDistance", 100, NULL, vTaskGetDistance_PRIORITY ,NULL);
	if(vTaskGetDistance_Handler != pdPASS)
	{
		rt_type = ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	}


	vTaskGetSpeed_Handler =  xTaskCreate(vTaskGetSpeed,"vTaskGetSpeed", 100, NULL, vTaskGetSpeed_PRIORITY ,NULL);
	if(vTaskGetSpeed_Handler != pdPASS)
	{
		rt_type = ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY;
	}

	return rt_type;
}

/******************************************************************************************/
/**************************************Scheduling Tasks************************************/


uint16_t Loc_Front_val , Loc_Right_val, Loc_Left_val;
void vTaskGetDistance(void* arg)
{

	uint8_t counter = 0;
	while(1)
	{
		Loc_Front_val = 0;
		Loc_Right_val = 0;
		Loc_Left_val = 0;

		for(counter =0; counter<3; counter++)
		{

			ULTRASONIC_vTrig(&Front_US);
			ULTRASONIC_vTrig(&Right_US);
			ULTRASONIC_vTrig(&Left_US);

			vTaskDelay(15);

			Loc_Front_val += (uint16_t)ULTRASONIC_u8GetDistance(&Front_US);
			Loc_Right_val += (uint16_t)ULTRASONIC_u8GetDistance(&Right_US);
			Loc_Left_val  += (uint16_t)ULTRASONIC_u8GetDistance(&Left_US);

		}

		/* Get AVG */
		Loc_Front_val = ( Loc_Front_val / 3);
		Loc_Right_val = ( Loc_Right_val / 3);
		Loc_Left_val =  ( Loc_Left_val  / 3);



		/* test ADD ID */
		gFront_Distance = (Loc_Front_val | 0x1000);
		gRight_Distance = (Loc_Right_val | 0x2000);
		gLeft_Distance  = (Loc_Left_val  | 0x3000);

		vTaskDelay(250);

	}
}


void vTaskGetSpeed(void* arg)
{

	while(1)
	{

		Right_ENC_Speed = (uint8_t)ENC_GetMotorSpeed(&Right_ENC);
		Left_ENC_Speed  = (uint8_t)ENC_GetMotorSpeed(&Left_ENC);

		Right_ENC_Speed = ( Right_ENC_Speed | 0x4000);
		Left_ENC_Speed  = ( Left_ENC_Speed| 0x5000);
		vTaskDelay(50);

	}
}




void SPI1_IRQHandler(void)
{

	uint8_t Loc_ID = 0;
	Loc_ID = SPI_I2S_ReceiveData(SPI1);
	switch(Loc_ID)
	{
	case FRONT_US_ID:
		SPI_I2S_SendData(SPI1, gFront_Distance);
		break;
	case RIGHT_US_ID :
		SPI_I2S_SendData(SPI1, gRight_Distance);
		break;
	case LEFT_US_ID:
		SPI_I2S_SendData(SPI1, gLeft_Distance);
		break;
	case RIGHT_ENC_ID:
		SPI_I2S_SendData(SPI1, Right_ENC_Speed);
		break;
	case LEFT_ENC_ID :
		SPI_I2S_SendData(SPI1, Left_ENC_Speed);
		break;
	}

}


