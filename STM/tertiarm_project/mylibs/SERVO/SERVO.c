
#include "SERVO.h"
#include "SERVO_cfg.h"
#include "DWT_Delay.h"

typedef struct
{
	uint16_t  Period_Min;
	uint16_t  Period_Max;
}SERVO_info;

static SERVO_info gs_SERVO_info[SERVO_NUM] = {0};


void SERVO_Init(uint16_t SERVO_Instance)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_HandleTypeDef htim;
	uint32_t PSC_Value = 0;
	uint32_t ARR_Value = 0;
	DWT_Delay_Init();

	// Configure The Servo PWM GPIO Pin
	GPIO_InitStruct.Pin = SERVO_CfgParam[SERVO_Instance].SERVO_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(SERVO_CfgParam[SERVO_Instance].SERVO_GPIO, &GPIO_InitStruct);

	//Calculate The PSC & ARR Values To Maximize PWM Resolution
	// F_pwm = 50Hz
	PSC_Value = (uint32_t) (SERVO_CfgParam[SERVO_Instance].TIM_CLK / 3276800.0);
	ARR_Value = (uint32_t) ((SERVO_CfgParam[SERVO_Instance].TIM_CLK / (50.0*(PSC_Value+1.0)))-1.0);


	// Enable corresponding clock
	if(SERVO_CfgParam[SERVO_Instance].TIM_Instance == TIM1)
	{
		__HAL_RCC_TIM1_CLK_ENABLE();
	}
	else if(SERVO_CfgParam[SERVO_Instance].TIM_Instance == TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();
	}
	else if(SERVO_CfgParam[SERVO_Instance].TIM_Instance == TIM3)
	{
		__HAL_RCC_TIM3_CLK_ENABLE();
	}
	else if(SERVO_CfgParam[SERVO_Instance].TIM_Instance == TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();
	}

	htim.Instance = SERVO_CfgParam[SERVO_Instance].TIM_Instance;
	htim.Init.Prescaler = PSC_Value;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = ARR_Value;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_Base_Init(&htim);
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig);
	HAL_TIM_PWM_Init(&htim);
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim, &sMasterConfig);
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, SERVO_CfgParam[SERVO_Instance].PWM_TIM_CH);

	// Calculate pulse values and store them in a structure
	gs_SERVO_info[SERVO_Instance].Period_Min = (uint16_t) (ARR_Value * (SERVO_CfgParam[SERVO_Instance].MinPulse/20.0));
	gs_SERVO_info[SERVO_Instance].Period_Max = (uint16_t) (ARR_Value * (SERVO_CfgParam[SERVO_Instance].MaxPulse/20.0));

	// Start PWM
	HAL_TIM_PWM_Start(&htim, SERVO_CfgParam[SERVO_Instance].PWM_TIM_CH);
}

// Moves a servo using degree value
void SERVO_MoveTo(uint16_t SERVO_Instance, float af_Angle)
{
	uint16_t Pulse = 0;

	Pulse = ((af_Angle*(gs_SERVO_info[SERVO_Instance].Period_Max - gs_SERVO_info[SERVO_Instance].Period_Min))/180.0)
			+ gs_SERVO_info[SERVO_Instance].Period_Min;

	*(SERVO_CfgParam[SERVO_Instance].TIM_CCRx) = Pulse;
}

// Moves a servo using actual pulse value
void SERVO_RawMove(uint16_t SERVO_Instance, uint16_t Pulse)
{
	if(Pulse <= gs_SERVO_info[SERVO_Instance].Period_Max && Pulse >= gs_SERVO_info[SERVO_Instance].Period_Min)
	{
		*(SERVO_CfgParam[SERVO_Instance].TIM_CCRx) = Pulse;
	}
}

// Gets The Maximum Pulse Width Value
uint16_t SERVO_Get_MaxPulse(uint16_t SERVO_Instance)
{
	return (gs_SERVO_info[SERVO_Instance].Period_Max);
}


// Gets The Minimum Pulse Width Value
uint16_t SERVO_Get_MinPulse(uint16_t SERVO_Instance)
{
	return (gs_SERVO_info[SERVO_Instance].Period_Min);
}

// Moves servo back and forth
void SERVO_Sweep(uint16_t SERVO_Instance)
{
	uint8_t Angle = 0;

	SERVO_MoveTo(SERVO_Instance, 0);

	DWT_Delay_ms(250);
	while(Angle < 180)
	{
		SERVO_MoveTo(SERVO_Instance, Angle++);
		DWT_Delay_ms(10);
	}
	DWT_Delay_ms(250);
	while(Angle > 0)
	{
		SERVO_MoveTo(SERVO_Instance, Angle--);
		DWT_Delay_ms(10);
	}
}
