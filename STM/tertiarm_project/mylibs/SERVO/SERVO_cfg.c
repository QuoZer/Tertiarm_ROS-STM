/*			SERVO Objects			*/
#include "SERVO.h"
#include "SERVO_cfg.h"


const SERVO_CfgType SERVO_CfgParam[SERVO_NUM] =
{
	// Servo Motor 1 Configurations
	{
		GPIOB,
		GPIO_PIN_9,
		TIM4,
		&TIM4->CCR4,
		TIM_CHANNEL_4,
		72000000,
		0.6,
		2.5
	},
	{
		GPIOB,
		GPIO_PIN_8,
		TIM4,
		&TIM4->CCR3,
		TIM_CHANNEL_3,
		72000000,
		0.8,
		2.2
	},
	{
		GPIOB,
		GPIO_PIN_7,
		TIM4,
		&TIM4->CCR2,
		TIM_CHANNEL_2,
		72000000,
		0.8,
		2.2
	},
	{
		GPIOB,
		GPIO_PIN_6,
		TIM4,
		&TIM4->CCR1,
		TIM_CHANNEL_1,
		72000000,
		0.55,
		2.5
	},
	{
		GPIOA,
		GPIO_PIN_11,
		TIM1,
		&TIM1->CCR4,
		TIM_CHANNEL_4,
		72000000,
		0.55,
		2.5
	}

};
