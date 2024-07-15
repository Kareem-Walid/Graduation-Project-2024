
#ifndef SERVO_H_
#define SERVO_H_


#include "stm32f10x.h"





// The Number OF Servo Motors To Be Used In The Project
#define SERVO_NUM    1

#define MinPulse			1.0
#define MaxPulse			2.0
#define ARR_Value  			((uint16_t)0xFFFF)
#define TIMER_PSC_VALUE		((uint16_t)0x0002)

typedef struct
{
	GPIO_TypeDef * SERVO_GPIO;
	uint16_t       SERVO_PIN;
	TIM_TypeDef*   TIMx;
	uint16_t       TIM_Channel_x;
}SERVO;


typedef struct
{
	uint16_t  Period_Min;
	uint16_t  Period_Max;
}SERVO_info;


/*-----[ Prototypes For All Functions ]-----*/

void SERVO_Init(SERVO* SEV );
void SERVO_MoveTo(SERVO* SEV , float af_Angle);
void SERVO_RawMove(SERVO* SEV , uint16_t au16_Pulse);
uint16_t SERVO_Get_MaxPulse(SERVO* SEV );
uint16_t SERVO_Get_MinPulse(SERVO* SEV );



#endif /* SERVO_H_ */
