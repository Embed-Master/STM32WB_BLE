#include "SMPS.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "BLE.hpp"
#include "RTC.hpp"
#include "stdio.h"
#include "P2P.hpp"

/******************************************************************************
 * Device Information Service (DIS)
 ******************************************************************************/
#define DISAPP_MANUFACTURER_NAME			"Motorica"
#define DISAPP_MODEL_NUMBER					"FEST-H"
#define DISAPP_HARDWARE_REVISION_NUMBER		"v1.0_r3.1"

/* Hardware Characteristics Service */
/*
	4-2-2-2-6
	Srvc-Mtrk-0000-Rodion
	Char-Mtrk-0000-Rodion
	SrvcMtrkRodion - 537276634D74726B526F64696F6E
	CharMtrkRodion - 436861724D74726B526F64696F6E
	53727663-4D74-726B-0000-526F64696F6E
	43686172-4D74-726B-0000-526F64696F6E
 */

int main()
{
	SMPS::init(SMPS::Voltage::_1V40, SMPS::Current::_80MA, SMPS::Source::HSE);
	RTCm::init();
	BLE::Settings settings;
	sprintf(settings.name, "%s", "Artemida89");// external (visible) name
	sprintf(settings.dis.firmware, "v%2.2f", (float)108 / 100);
	sprintf(settings.dis.hardware, "%s", DISAPP_HARDWARE_REVISION_NUMBER);
	sprintf(settings.dis.manufacturer, "%s", DISAPP_MANUFACTURER_NAME);
	sprintf(settings.dis.model, "%s", DISAPP_MODEL_NUMBER);
	for (byte i = 0; i < 6; i++) settings.dis.serial[i] = ((byte *)UID64_BASE)[i];
	BLE::init(settings);
	vTaskStartScheduler();
	while (true) ;
}
extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
	static bool once = true;
	while (true)
	{
		if (once)
		{
			once = false;
#ifdef STACK_DEBUG
			printf("Stack overflow\n");
			printf("%s\n", pcTaskName);
#endif // STACK_DEBUG
		}
	}
}