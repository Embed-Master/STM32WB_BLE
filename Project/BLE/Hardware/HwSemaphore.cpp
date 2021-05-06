#include "HwSemaphore.h"
#include "CoreSettings.h"

void HwSemaphoreInit()
{
	RCC->AHB3ENR |= RCC_AHB3ENR_HSEMEN;
}