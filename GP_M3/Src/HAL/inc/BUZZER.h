
#ifndef MOTOR_H_
#define MOTOR_H_

void BUZZER_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void BUZZER_on(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void BUZZER_off(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


#endif /* MOTOR_H_ */
