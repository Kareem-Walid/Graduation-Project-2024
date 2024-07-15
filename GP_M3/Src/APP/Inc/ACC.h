#ifndef ACC_H_
#define ACC_H_



/* ------ Includes ------ */
#include "FreeRTOS.h"
#include "task.h"

#include "SysInit.h"


#include "AEB.h"


#define SPEED_30   12
#define SPEED_60   13
#define SPEED_90   14
#define STOP_SIGN  15



#define SPEED_MAPPED_TO_30      15
#define SPEED_MAPPED_TO_60      25
#define SPEED_MAPPED_TO_90      35

void vACC_Init(void);


void vACC_Task(void * pvParameter);
void vACC_Sign(void * pvParameter);





#endif
