#include "SMPS.h"
#include "CoreSettings.h"
#include "Types.h"

void SMPSsetSource(SMPSsource source)
{
	if (source > SMPS_SOURCE_HSE) return;
	RCC->SMPSCR = source | RCC_SMPSCR_SMPSDIV_0;
}

void SMPSsetVoltage(SMPSvoltage voltage)
{
	if (voltage > SMPS_VOLTAGE_1V90) return;
	const uint calibration = (((*SMPS_VOLTAGE_CAL_ADDR) & SMPS_VOLTAGE_CAL) >> SMPS_VOLTAGE_CAL_POS); /* SMPS output voltage level calibrated in production */
	PWR->CR5 &= ~PWR_CR5_SMPSVOS;
	if (!calibration) PWR->CR5 |= voltage; // No calibration
	else
	{
		int voltageTrimmed = (int)(voltage + calibration) - SMPS_VOLTAGE_1V50;
		if (voltageTrimmed < 0) voltageTrimmed = 0;
		else if (voltageTrimmed > PWR_CR5_SMPSVOS) voltageTrimmed = PWR_CR5_SMPSVOS;
		PWR->CR5 |= voltageTrimmed;
	}
}

void SMPSsetCurrent(SMPScurrent current)
{
	if (current > SMPS_CURRENT_220MA) return;
	PWR->CR5 &= ~PWR_CR5_SMPSSC;
	PWR->CR5 |= current;
}

void SPMSenable()
{
	PWR->CR5 |= PWR_CR5_SMPSEN;
	uint source = ((RCC->SMPSCR & RCC_SMPSCR_SMPSSEL) >> RCC_SMPSCR_SMPSSEL_Pos) << RCC_SMPSCR_SMPSSWS_Pos;
	while ((RCC->SMPSCR & RCC_SMPSCR_SMPSSWS) != source) ;
}

void SMPSdisable()
{
	PWR->CR5 &= ~PWR_CR5_SMPSEN;
}

void SMPSinit(SMPSvoltage voltage, SMPScurrent current, SMPSsource source)
{
	SMPSdisable();
	SMPSsetVoltage(voltage);
	SMPSsetCurrent(current);
	SMPSsetSource(source);
	SPMSenable();
}