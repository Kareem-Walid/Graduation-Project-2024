#ifndef BLINDSPOT_BLINDSPOT_H_
#define BLINDSPOT_BLINDSPOT_H_

/****************************MACROs Section******************************************/
#define MIN_DISTANCE 					10

#define vLeftAreaHandler_PRIORITY   	3
#define vRightAreaHandler_PRIORITY  	4
#define TurnSignalWarningTwo_PRIORITY 	5


/************************************************************************************/
/****************************ENUMs Section*******************************************/
typedef enum
{
	xQueueCreate_ERROR,
	ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY,
	BS_NO_ERROR,
	BS_ERROR_COULD_NOT_CREATE_BINARY_SEMAPHORE,
	BS_ERROR_COULD_NOT_GIVE_SEMAPHORE,

}NBS_ReturnType_e;

/************************************************************************************/
/*****************************Functions Declaration**********************************/
NBS_ReturnType_e 	BS_ReturnTypeBS_Init		(void);
/************************************************************************************/

#endif /* BLINDSPOT_BLINDSPOT_H_ */
