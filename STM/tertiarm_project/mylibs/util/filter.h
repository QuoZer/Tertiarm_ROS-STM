#include <stdint.h>

typedef struct
{
	uint16_t Filter_Order;
	uint16_t Buffer_Index;
	uint8_t* Data_Buffer;
}FIR_Filter;

void SUM_BUFFER(float IN, uint8_t* SUM, FIR_Filter* FILTER_OBJ);
