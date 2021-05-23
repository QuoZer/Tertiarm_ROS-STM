#include "stm32f1xx_hal.h"
#include "filter.h"
#include "button.h"

uint8_t Filters_Buffer[9] = {0};
FIR_Filter Filter_Instance[1] = {0};

void BTN_Init(uint8_t State)
{
	Filter_Instance[0].Filter_Order = 8;
	Filter_Instance[0].Data_Buffer = Filters_Buffer;
	Filter_Instance[0].Buffer_Index = 0;

	//BTN_State = State;
}

void BTN_Read(uint16_t Instance, uint8_t* BTN_State)
{
	*BTN_State = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
}

// function to be called from inside the SysTick interrupt
void BTN_Main(void)
{
	uint8_t Read_State = 0;
	uint8_t FilterSum = 0;
	uint8_t Filtered_State = 0;


	Read_State = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14);
	/* Call The SUM Filter Function */
	SUM_BUFFER(Read_State, &FilterSum, &Filter_Instance[0]);
	if(FilterSum == Filter_Instance[0].Filter_Order+1)
	{
		Filtered_State = 1;
		// return filtered state
		BTN_State = Filtered_State;
	}
	if(FilterSum == 0)
	{
		Filtered_State = 0;
		BTN_State = Filtered_State;
	}
}
