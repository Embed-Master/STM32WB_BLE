#include "SMPS.h"
#include "CoreSettings.h"
#include "Types.h"

#define _CAL_ADDR		((uint*) (0x1FFF7558UL))		/* SMPS output voltage calibration level corresponding to voltage "_CAL_VOLTAGE_MV" */
#define _CAL_POS		(8UL)							/* SMPS output voltage calibration level bitfield position */
#define _CAL			(0xFUL << _CAL_POS)	/* SMPS output voltage calibration level bitfield mask */
#define _CAL_VOLTAGE_MV	(1500UL)						/* SMPS output voltage calibration value (unit: mV) */
#define _BASE_MV		(1200UL)						/* SMPS output voltage base value (unit: mV) */
#define _STEP_MV		(  50UL)						/* SMPS output voltage step (unit: mV) */

void SMPS::setSource(Source source)
{
	if (source > Source::HSE) return;
	RCC->SMPSCR = source | RCC_SMPSCR_SMPSDIV_0;
}

void SMPS::setVoltage(Voltage voltage)
{
	if (voltage > Voltage::_1V90) return;
	const uint calibration = (((*_CAL_ADDR) & _CAL) >> _CAL_POS); /* SMPS output voltage level calibrated in production */
	PWR->CR5 &= ~PWR_CR5_SMPSVOS;
	if (!calibration) PWR->CR5 |= voltage; // No calibration
	else
	{
		int voltageTrimmed = (int)(voltage + calibration) - Voltage::_1V50;
		if (voltageTrimmed < 0) voltageTrimmed = 0;
		else if (voltageTrimmed > PWR_CR5_SMPSVOS) voltageTrimmed = PWR_CR5_SMPSVOS;
		PWR->CR5 |= voltageTrimmed;
	}
}

void SMPS::setCurrent(Current current)
{
	if (current > Current::_220MA) return;
	PWR->CR5 &= ~PWR_CR5_SMPSSC;
	PWR->CR5 |= current;
}

void SMPS::enable()
{
	PWR->CR5 |= PWR_CR5_SMPSEN;
	uint source = ((RCC->SMPSCR & RCC_SMPSCR_SMPSSEL) >> RCC_SMPSCR_SMPSSEL_Pos) << RCC_SMPSCR_SMPSSWS_Pos;
	while ((RCC->SMPSCR & RCC_SMPSCR_SMPSSWS) != source) ;
}

void SMPS::disable()
{
	PWR->CR5 &= ~PWR_CR5_SMPSEN;
}

void SMPS::init(Voltage voltage, Current current, Source source)
{
	disable();
	setVoltage(voltage);
	setCurrent(current);
	setSource(source);
	enable();
}