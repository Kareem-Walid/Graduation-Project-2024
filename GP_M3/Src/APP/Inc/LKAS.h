#ifndef LKAS_LKAS_H_
#define LKAS_LKAS_H_


#define vTaskLKAS_PRIORITY 							  2
#define vTaskLDW_PRIORITY         		              3


typedef enum
{
	TURN_SIGNAL_OFF,
	TURNSIGNAL_ON,
	OTHERWISE,
}NturnSignalState_e;

typedef enum
{
	EVENTGROUP_CREATION_ERROR,
	QUEUE_CREATION_ERROR,
	TASK_CREATION_ERROR,
	LKAS_NO_ERROR,
}NError_type_e;



NError_type_e Error_type_t_LKASInit(void);


#endif /* LKAS_LKAS_H_ */
