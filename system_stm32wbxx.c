#include "stm32wbxx.h"

uint32_t SystemCoreClock  = 32000000UL; /*CPU1: M4 on MSI clock after startup (4MHz)*/

void SystemInit(void)
{
	/* FPU settings ------------------------------------------------------------*/
	#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	SCB->CPACR |= ((3UL << (10UL*2UL))|(3UL << (11UL*2UL)));  /* set CP10 and CP11 Full Access */
	#endif
  
	RCC->CR |= RCC_CR_HSEON;
	while (!(RCC->CR & RCC_CR_HSERDY)) ;
	
	FLASH->ACR |= FLASH_ACR_LATENCY_0;
	
	RCC->CFGR = RCC_CFGR_PPRE2F | RCC_CFGR_PPRE1F | RCC_CFGR_HPREF | RCC_CFGR_SW_1;
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1) ;
	
//	RCC->CR &= ~RCC_CR_MSION;
}