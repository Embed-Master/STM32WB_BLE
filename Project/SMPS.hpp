#pragma once

#include "CoreSettings.h"

class SMPS
{
public:
	typedef enum
	{
		_1V20 = (0x00000000U),                                                                   /*!< SMPS step down converter supply output voltage 1.20V */
		_1V25 = (                                                            PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.25V */
		_1V30 = (                                        PWR_CR5_SMPSVOS_1                    ), /*!< SMPS step down converter supply output voltage 1.30V */
		_1V35 = (                                        PWR_CR5_SMPSVOS_1 | PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.35V */
		_1V40 = (                    PWR_CR5_SMPSVOS_2                                        ), /*!< SMPS step down converter supply output voltage 1.40V */
		_1V45 = (                    PWR_CR5_SMPSVOS_2 |                     PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.45V */
		_1V50 = (                    PWR_CR5_SMPSVOS_2 | PWR_CR5_SMPSVOS_1                    ), /*!< SMPS step down converter supply output voltage 1.50V */
		_1V55 = (                    PWR_CR5_SMPSVOS_2 | PWR_CR5_SMPSVOS_1 | PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.55V */
		_1V60 = (PWR_CR5_SMPSVOS_3                                                            ), /*!< SMPS step down converter supply output voltage 1.60V */
		_1V65 = (PWR_CR5_SMPSVOS_3 |                                         PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.65V */
		_1V70 = (PWR_CR5_SMPSVOS_3 |                     PWR_CR5_SMPSVOS_1                    ), /*!< SMPS step down converter supply output voltage 1.70V */
		_1V75 = (PWR_CR5_SMPSVOS_3 |                     PWR_CR5_SMPSVOS_1 | PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.75V */
		_1V80 = (PWR_CR5_SMPSVOS_3 | PWR_CR5_SMPSVOS_2                                        ), /*!< SMPS step down converter supply output voltage 1.80V */
		_1V85 = (PWR_CR5_SMPSVOS_3 | PWR_CR5_SMPSVOS_2 |                     PWR_CR5_SMPSVOS_0), /*!< SMPS step down converter supply output voltage 1.85V */
		_1V90 = (PWR_CR5_SMPSVOS_3 | PWR_CR5_SMPSVOS_2 | PWR_CR5_SMPSVOS_1                    ) /*!< SMPS step down converter supply output voltage 1.90V */
	}Voltage;
	typedef enum
	{
		_80MA  = (0x00000000U),												/*!< SMPS step down converter supply startup current 80mA */
		_100MA = (                                      PWR_CR5_SMPSSC_0),	/*!< SMPS step down converter supply startup current 100mA */
		_120MA = (                   PWR_CR5_SMPSSC_1                   ),	/*!< SMPS step down converter supply startup current 120mA */
		_140MA = (                   PWR_CR5_SMPSSC_1 | PWR_CR5_SMPSSC_0),	/*!< SMPS step down converter supply startup current 140mA */
		_160MA = (PWR_CR5_SMPSSC_2                                      ),	/*!< SMPS step down converter supply startup current 160mA */
		_180MA = (PWR_CR5_SMPSSC_2 |                    PWR_CR5_SMPSSC_0),	/*!< SMPS step down converter supply startup current 180mA */
		_200MA = (PWR_CR5_SMPSSC_2 | PWR_CR5_SMPSSC_1                   ),	/*!< SMPS step down converter supply startup current 200mA */
		_220MA = (PWR_CR5_SMPSSC_2 | PWR_CR5_SMPSSC_1 | PWR_CR5_SMPSSC_0)	/*!< SMPS step down converter supply startup current 220mA */
	}Current;
	typedef enum
	{
		HSI,
		MSI,
		HSE
	}Source;
	
	static void setVoltage(Voltage voltage);
	static void setCurrent(Current current);
	static void setSource(Source source);
	static void enable();
	static void disable();
	static void init(Voltage voltage, Current current, Source source);
};