#include "stm32f1xx_hal.h"

uint8_t BTN_State;

void BTN_Init(uint8_t State);

void BTN_Main(void);

void BTN_Read(uint16_t Instance, uint8_t* BTN_State);
