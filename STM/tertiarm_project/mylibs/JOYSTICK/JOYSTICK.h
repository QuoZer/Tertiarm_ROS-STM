

#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#define HAL_ADC_MODULE_ENABLED

#include "stm32f1xx_hal.h"


typedef struct
{
	GPIO_TypeDef * JoyStick_xGPIO;
	GPIO_TypeDef * JoyStick_yGPIO;
	uint16_t       JoyStick_xPIN;
	uint16_t       JoyStick_yPIN;
	ADC_TypeDef*   ADC_Instance;
	uint32_t       ADCx_CH;
	uint32_t       ADCy_CH;
}Joystick_struct;


void JoyStick_Init();
void JoyStick_Read(uint16_t* JoyStick_XY);

#endif /* JOYSTICK_H_ */
