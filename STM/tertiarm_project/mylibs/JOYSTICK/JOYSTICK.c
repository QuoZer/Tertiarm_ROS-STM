

#include "JOYSTICK.h"

static ADC_HandleTypeDef hadc;
static ADC_ChannelConfTypeDef sConfig = {0};
static uint8_t calibrated = 0;
// JoyStick unit 1 Configurations
const Joystick_struct Manual_Joy =
	{
		GPIOB,
		GPIOB,
		GPIO_PIN_0,
		GPIO_PIN_1,
		ADC1,
		ADC_CHANNEL_8,
		ADC_CHANNEL_9
	};

void JoyStick_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	// Configure adc pins
	GPIO_InitStruct.Pin = Manual_Joy.JoyStick_xPIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(Manual_Joy.JoyStick_xGPIO, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = Manual_Joy.JoyStick_yPIN;
	GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
	HAL_GPIO_Init(Manual_Joy.JoyStick_yGPIO, &GPIO_InitStruct);
	// Configure ADC
	hadc.Instance = Manual_Joy.ADC_Instance;
	hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc.Init.ContinuousConvMode = DISABLE;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.NbrOfConversion = 1;
	HAL_ADC_Init(&hadc);
	sConfig.Channel = Manual_Joy.ADCx_CH;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLETIME_28CYCLES_5;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);

	if(calibrated == 0)
	{
		HAL_ADCEx_Calibration_Start(&hadc);
		calibrated = 1;
	}
}


void JoyStick_Read(uint16_t* JoyStick_XY)
{
	uint32_t AD_RES;

	// Select channel
	sConfig.Channel = Manual_Joy.ADCx_CH;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	// Start ADC Conversion
	HAL_ADC_Start(&hadc);
	// Poll for 1ms
	HAL_ADC_PollForConversion(&hadc, 1);
	// Read The ADC Conversion Result Write It To JoyStick X
	AD_RES = HAL_ADC_GetValue(&hadc);
	JoyStick_XY[0] = AD_RES;

	sConfig.Channel = Manual_Joy.ADCy_CH;
	HAL_ADC_ConfigChannel(&hadc, &sConfig);
	HAL_ADC_Start(&hadc);
	HAL_ADC_PollForConversion(&hadc, 1);
	AD_RES = HAL_ADC_GetValue(&hadc);
	JoyStick_XY[1] = AD_RES;
}
