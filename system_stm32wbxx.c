#include "stm32wbxx.h"

#if !defined  (HSE_VALUE)
  #define HSE_VALUE    (32000000UL) /*!< Value of the External oscillator in Hz */
#endif /* HSE_VALUE */

#if !defined  (MSI_VALUE)
   #define MSI_VALUE    (4000000UL) /*!< Value of the Internal oscillator in Hz*/
#endif /* MSI_VALUE */

#if !defined  (HSI_VALUE)
  #define HSI_VALUE    (16000000UL) /*!< Value of the Internal oscillator in Hz*/
#endif /* HSI_VALUE */

#if !defined  (LSI_VALUE) 
 #define LSI_VALUE  (32000UL)       /*!< Value of LSI in Hz*/
#endif /* LSI_VALUE */ 

#if !defined  (LSE_VALUE)
  #define LSE_VALUE    (32768UL)    /*!< Value of LSE in Hz*/
#endif /* LSE_VALUE */

uint32_t SystemCoreClock  = 4000000UL ; /*CPU1: M4 on MSI clock after startup (4MHz)*/

const uint32_t AHBPrescTable[16UL] = {1UL, 3UL, 5UL, 1UL, 1UL, 6UL, 10UL, 32UL, 2UL, 4UL, 8UL, 16UL, 64UL, 128UL, 256UL, 512UL};

const uint32_t APBPrescTable[8UL]  = {0UL, 0UL, 0UL, 0UL, 1UL, 2UL, 3UL, 4UL};

const uint32_t MSIRangeTable[16UL] = {100000UL, 200000UL, 400000UL, 800000UL, 1000000UL, 2000000UL, \
                                      4000000UL, 8000000UL, 16000000UL, 24000000UL, 32000000UL, 48000000UL, 0UL, 0UL, 0UL, 0UL}; /* 0UL values are incorrect cases */

#if defined(STM32WB55xx) || defined(STM32WB5Mxx) || defined(STM32WB35xx)
  const uint32_t SmpsPrescalerTable[4UL][6UL]={{1UL,3UL,2UL,2UL,1UL,2UL}, \
                                        {2UL,6UL,4UL,3UL,2UL,4UL}, \
                                        {4UL,12UL,8UL,6UL,4UL,8UL}, \
                                        {4UL,12UL,8UL,6UL,4UL,8UL}};
#endif

void SystemInit(void)
{
	/* FPU settings ------------------------------------------------------------*/
	#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
	SCB->CPACR |= ((3UL << (10UL*2UL))|(3UL << (11UL*2UL)));  /* set CP10 and CP11 Full Access */
	#endif
  
	/* Reset the RCC clock configuration to the default reset state ------------*/
	/* Set MSION bit */
	RCC->CR |= RCC_CR_MSION;

	#if defined(STM32WB55xx) || defined(STM32WB5Mxx)
	/* Reset PLLSAI1CFGR register */
	RCC->PLLSAI1CFGR = 0x22041000U;
	#endif
}