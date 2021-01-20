#pragma once

#include "CoreSettings.h"

#define SMPS_VOLTAGE_CAL_ADDR		((uint*) (0x1FFF7558UL))		/* SMPS output voltage calibration level corresponding to voltage "SMPS_VOLTAGE_CAL_VOLTAGE_MV" */
#define SMPS_VOLTAGE_CAL_POS		(8UL)							/* SMPS output voltage calibration level bitfield position */
#define SMPS_VOLTAGE_CAL			(0xFUL << SMPS_VOLTAGE_CAL_POS)	/* SMPS output voltage calibration level bitfield mask */
#define SMPS_VOLTAGE_CAL_VOLTAGE_MV	(1500UL)						/* SMPS output voltage calibration value (unit: mV) */
#define SMPS_VOLTAGE_BASE_MV		(1200UL)						/* SMPS output voltage base value (unit: mV) */
#define SMPS_VOLTAGE_STEP_MV		(  50UL)						/* SMPS output voltage step (unit: mV) */

typedef enum
{
	SMPS_VOLTAGE_1V20 = (0x00000000U),                                                                   /*!< SMPS step down converter supply output voltage 1.20V */
	SMPS_VOLTAGE_1V25 = (                                                            PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.25V */
	SMPS_VOLTAGE_1V30 = (                                        PWR_CR5_SMPSVOS_1                    ), /*!< SMPS step down converter supply output voltage 1.30V */
	SMPS_VOLTAGE_1V35 = (                                        PWR_CR5_SMPSVOS_1 | PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.35V */
	SMPS_VOLTAGE_1V40 = (                    PWR_CR5_SMPSVOS_2                                        ), /*!< SMPS step down converter supply output voltage 1.40V */
	SMPS_VOLTAGE_1V45 = (                    PWR_CR5_SMPSVOS_2 |                     PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.45V */
	SMPS_VOLTAGE_1V50 = (                    PWR_CR5_SMPSVOS_2 | PWR_CR5_SMPSVOS_1                    ), /*!< SMPS step down converter supply output voltage 1.50V */
	SMPS_VOLTAGE_1V55 = (                    PWR_CR5_SMPSVOS_2 | PWR_CR5_SMPSVOS_1 | PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.55V */
	SMPS_VOLTAGE_1V60 = (PWR_CR5_SMPSVOS_3                                                            ), /*!< SMPS step down converter supply output voltage 1.60V */
	SMPS_VOLTAGE_1V65 = (PWR_CR5_SMPSVOS_3 |                                         PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.65V */
	SMPS_VOLTAGE_1V70 = (PWR_CR5_SMPSVOS_3 |                     PWR_CR5_SMPSVOS_1                    ), /*!< SMPS step down converter supply output voltage 1.70V */
	SMPS_VOLTAGE_1V75 = (PWR_CR5_SMPSVOS_3 |                     PWR_CR5_SMPSVOS_1 | PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.75V */
	SMPS_VOLTAGE_1V80 = (PWR_CR5_SMPSVOS_3 | PWR_CR5_SMPSVOS_2                                        ), /*!< SMPS step down converter supply output voltage 1.80V */
	SMPS_VOLTAGE_1V85 = (PWR_CR5_SMPSVOS_3 | PWR_CR5_SMPSVOS_2 |                     PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.85V */
	SMPS_VOLTAGE_1V90 = (PWR_CR5_SMPSVOS_3 | PWR_CR5_SMPSVOS_2 | PWR_CR5_SMPSVOS_1                    ) /*!< SMPS step down converter supply output voltage 1.90V */
}SMPSvoltage;

typedef enum
{
	SMPS_CURRENT_80MA  = (0x00000000U),												/*!< SMPS step down converter supply startup current 80mA */
	SMPS_CURRENT_100MA = (                                      PWR_CR5_SMPSSC_0),	/*!< SMPS step down converter supply startup current 100mA */
	SMPS_CURRENT_120MA = (                   PWR_CR5_SMPSSC_1                   ),	/*!< SMPS step down converter supply startup current 120mA */
	SMPS_CURRENT_140MA = (                   PWR_CR5_SMPSSC_1 | PWR_CR5_SMPSSC_0),	/*!< SMPS step down converter supply startup current 140mA */
	SMPS_CURRENT_160MA = (PWR_CR5_SMPSSC_2                                      ),	/*!< SMPS step down converter supply startup current 160mA */
	SMPS_CURRENT_180MA = (PWR_CR5_SMPSSC_2 |                    PWR_CR5_SMPSSC_0),	/*!< SMPS step down converter supply startup current 180mA */
	SMPS_CURRENT_200MA = (PWR_CR5_SMPSSC_2 | PWR_CR5_SMPSSC_1                   ),	/*!< SMPS step down converter supply startup current 200mA */
	SMPS_CURRENT_220MA = (PWR_CR5_SMPSSC_2 | PWR_CR5_SMPSSC_1 | PWR_CR5_SMPSSC_0)	/*!< SMPS step down converter supply startup current 220mA */
}SMPScurrent;

typedef enum
{
	SMPS_SOURCE_HSI,
	SMPS_SOURCE_MSI,
	SMPS_SOURCE_HSE
}SMPSsource;

void SMPSsetVoltage(SMPSvoltage voltage);
void SMPSsetCurrent(SMPScurrent current);
void SMPSsetSource(SMPSsource source);
void SPMSenable();
void SMPSdisable();
void SMPSinit(SMPSvoltage voltage, SMPScurrent current, SMPSsource source);