
#ifndef AEB_H_
#define AEB_H_


/* --------------------- Includes ---------------------- */
#include "FreeRTOS.h"
#include "task.h"

#include "semphr.h"
#include "queue.h"
#include "event_groups.h"

#include "SysInit.h"



/*----------------------- MACROS -----------------------*/
#define BREAKING_DISTANCE_CONST       0.3
#define WARNING_DISTANCE_CONST        0.5





typedef enum {

	NOT_OK,
	OK
}AEB_State_t;





void vCar_Task(void * pvParameter);
void vCalculations_Task(void * pvParameter);



#endif
