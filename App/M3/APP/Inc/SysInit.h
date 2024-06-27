
#ifndef SYSINIT_SYSINIT_H_
#define SYSINIT_SYSINIT_H_


#include "Initialize_file_M3.h"


#define vSendMessageViaUSART_PRIORITY 			2
#define vReadDataFromUART_PRIORITY				1

#define MAX_LCD_MESSAGES 		5
#define LEN_LCD_MESSAGE 		(sizeof(int))

#define MAX_SEMPHR_COUNT   		1
#define INIT_SEMPHR_COUNT  		0




/*SPI Data.*/
#define FRONT_US_ID             1U
#define RIGHT_ULTRASONIC_ID 	2U
#define LEFT_ULTRASONIC_ID 		3U
#define RIGHT_ENC_ID            4U
#define LEFT_ENC_ID             5U




/*--------------- ACC MACROS ------------------*/

#define OFF 0
#define ON   1
/* ------------------------------------------- */


/* ----------------- APP MACROS ------------------- */

#define CAR_FORWARD           '1'
#define CAR_RIGHT             '2'
#define CAR_BACKWORD          '3'
#define CAR_LEFT              '4'
#define SPEED_INC             '5'
#define SPEED_DEC             '6'
#define CAR_STOP              '7'
#define ACC_ON_OFF            '8'
//#define ACC_MODE              '9'
#define LK_ON_OFF             '9'
#define RIGHT_TURN_SIGNAL     'A'
#define LEFT_TURN_SIGNAL      'B'

#define Test_Sign             'F'



/* ------------------------------------------------ */



#define BIT_0 					( 1 << 0 )
#define BIT_1 					( 1 << 1 )
#define BIT_2 					( 1 << 2 )
#define BIT_3 					( 1 << 3 )


// #define MAX_SPEED       55
#define MIN_SPEED       0

#define MAX_ANGLE       140
#define MIN_ANGLE       10


typedef enum
{
	SysInit_xQueueCreate_ERROR,
	SysInit_ERROR_COULD_NOT_ALLOCATE_REQUIRED_MEMORY,
	SysInit_ERROR_COULD_NOT_CREATE_BINARY_SEMAPHORE,
	SysInit_ERROR_COULD_NOT_GIVE_SEMAPHORE,
	SysInit_NO_ERROR,
}NSysInit_e;


NSysInit_e SysInit(void);

void vReadDataFromM4(uint16_t ID, uint16_t* data);
void vWriteDataToUART(uint16_t data);



#endif /* SYSINIT_SYSINIT_H_ */
