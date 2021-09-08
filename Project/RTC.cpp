#include "RTC.hpp"
#include "CoreSettings.h"

void RTCm::init()
{
	if (RTC->ISR & RTC_ISR_INITS) return;
	PWR->CR1 |= PWR_CR1_DBP;
	RCC->BDCR = RCC_BDCR_BDRST;
	__NOP();
	__NOP();
	RCC->BDCR = RCC_BDCR_LSEON;
	while (!(RCC->BDCR & RCC_BDCR_LSERDY)) ;
	RCC->BDCR = RCC_BDCR_LSEON | RCC_BDCR_RTCSEL_0 | RCC_BDCR_RTCEN;
}