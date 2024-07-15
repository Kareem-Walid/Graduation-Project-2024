
/*---------- Includes ------------- */
#include "FreeRTOS.h"
#include "task.h"


/* ----- System Component --------- */
#include "LKAS.h"
#include "AEB.h"
#include "ACC.h"
#include "BlindSpot.h"
/* ------------------------------- */




int main(void)
{

	/* ----- Initiate System ----- */
   	 SysInit();

	/* ------- Initiate AEB ------ */
     vAEB_Init();

	/* ------ Initiate ACC --------*/
     vACC_Init();

	/* -- Initiate Lane Keeping -- */
	 Error_type_t_LKASInit();

	/*----- Initiate Blind Spot -- */
	 BS_ReturnTypeBS_Init();

	/* ----- Start Schaduler ----- */
	vTaskStartScheduler();
	while(1);

}
