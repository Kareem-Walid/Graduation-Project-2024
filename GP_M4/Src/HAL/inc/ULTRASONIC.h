
#ifndef HAL_ULTRASONIC_INT_H_
#define HAL_ULTRASONIC_INT_H_

#define GPIO_CLK 				GPIO_Low_Speed	//GPIO_Low_Speed   GPIO_Medium_Speed	GPIO_Fast_Speed  GPIO_High_Speed
#define CLOCK_US 				16.0
#define TIMER_ICPSC_CFG			TIM_ICPSC_DIV1	// TIM_ICPSC_DIV1	TIM_ICPSC_DIV2	TIM_ICPSC_DIV4	TIM_ICPSC_DIV8
#define TIMEER_PSC_CONFIG		10
#define TIK_TIME				((TIMEER_PSC_CONFIG + 1) / CLOCK_US)
#define DELAY_30US				30

typedef struct
{
	GPIO_TypeDef* GPIOx_Trig ;
	GPIO_TypeDef* GPIOx_Echo ;
	uint16_t TRIGGER_PIN ;
	uint16_t ECO_PIN;		// This parameter should be one of this pins GPIO_Pin_1  GPIO_Pin_2  GPIO_Pin_3  GPIO_Pin_5
	uint8_t	Channel_Num	;	//TIM_Channel_1 or TIM_Channel_2 or TIM_Channel_3 or TIM_Channel_4
	TIM_TypeDef* TIMx;

}Ultrasonic_t;

void  ULTRASONIC_vInit(Ultrasonic_t * US_Num);
void  ULTRASONIC_vTrig(Ultrasonic_t * US_Num);
float ULTRASONIC_u8GetDistance(Ultrasonic_t * US_Num);

void Ultrasonic_delay (uint16_t Delay_Num);

#endif /* HAL_ULTRASONIC_INT_H_ */
