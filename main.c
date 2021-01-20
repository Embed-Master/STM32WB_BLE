#include "Serial.h"
#include "SMPS.h"

void delay(uint del)
{
	while (--del) ;
}

int main(void)
{
	serialInit();
	SMPSinit(SMPS_VOLTAGE_1V40, SMPS_CURRENT_80MA, SMPS_SOURCE_HSE);
	while (1)
	{
		
	}
}
