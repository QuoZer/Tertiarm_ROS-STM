
#ifndef SERVO_H_
#define SERVO_H_

#define HAL_TIM_MODULE_ENABLED

#include "../../Drivers/STM32F1xx_HAL_Driver/Inc/stm32f1xx_hal.h"

//
#define SERVO_NUM  5

typedef struct
{
	GPIO_TypeDef * SERVO_GPIO;
	uint16_t       SERVO_PIN;
	TIM_TypeDef*   TIM_Instance;
	uint32_t*      TIM_CCRx;
	uint32_t       PWM_TIM_CH;
	uint32_t       TIM_CLK;
	float          MinPulse;
	float          MaxPulse;
}SERVO_CfgType;


// Prototypes
void SERVO_Init(uint16_t SERVO_Instance);
void SERVO_MoveTo(uint16_t SERVO_Instance, float af_Angle);
void SERVO_RawMove(uint16_t SERVO_Instance, uint16_t Pulse);
uint16_t SERVO_Get_MaxPulse(uint16_t SERVO_Instance);
uint16_t SERVO_Get_MinPulse(uint16_t SERVO_Instance);
void SERVO_Sweep(uint16_t SERVO_Instance);


#endif /* SERVO_H_ */
