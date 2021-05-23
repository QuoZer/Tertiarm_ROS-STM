#include <filter.h>



void SUM_BUFFER(float IN, uint8_t* SUM, FIR_Filter* FILTER_OBJ){
	int32_t temp_sum = 0;
	uint16_t i = 0;

	// Push The New Input To The History Buffer
	FILTER_OBJ->Data_Buffer[FILTER_OBJ->Buffer_Index] = IN;
	FILTER_OBJ->Buffer_Index++;

	if(FILTER_OBJ->Buffer_Index == FILTER_OBJ->Filter_Order+1)
	{ FILTER_OBJ->Buffer_Index = 0; }

	// Calculate The Accumulated Sum For The Buffer Data
	for(i = 0; i < FILTER_OBJ->Filter_Order+1; i++)
	{
		temp_sum += FILTER_OBJ->Data_Buffer[i];
	}
	*SUM = (float)temp_sum;
	}
