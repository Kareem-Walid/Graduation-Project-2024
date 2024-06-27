#ifndef APP_APP_H_
#define APP_APP_H_

#define vTaskGetDistance_PRIORITY 		3
#define vTaskGetSpeed_PRIORITY    		2
#define vTaskSendData_PRIORITY			1



/*----------- IDs ------------ */
#define FRONT_US_ID          1U
#define RIGHT_US_ID          2U
#define LEFT_US_ID           3U
#define RIGHT_ENC_ID         4U
#define LEFT_ENC_ID          5U

/* --------------------------- */

typedef enum
{
	xQueueCreate_ERROR,
	ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY,
	Sys_NO_ERROR,
	Sys_ERROR_COULD_NOT_CREATE_BINARY_SEMAPHORE,
	Sys_ERROR_COULD_NOT_GIVE_SEMAPHORE,

}NSys_ReturnType_e;


NSys_ReturnType_e vSysInit(void);

#endif /* APP_APP_H_ */
