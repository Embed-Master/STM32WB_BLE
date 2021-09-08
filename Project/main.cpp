#include "SMPS.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "BLE.hpp"
#include "RTC.hpp"
#ifdef STACK_DEBUG
#include "Debug.h"
#endif // STACK_DEBUG
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
	P2P::initUUID(	*(GATT::UUID *)(const GATT::UUID[]){ GATT::UUIDtype::_128bit, { ._128bit = { 0x6E, 0x6F, 0x69, 0x64, 0x6F, 0x52, 0x00, 0x00, 0x6B, 0x72, 0x74, 0x4D, 0x63, 0x76, 0x72, 0x53 } } },	// service
					*(GATT::UUID *)(const GATT::UUID[]){ GATT::UUIDtype::_128bit, { ._128bit = { 0x6E, 0x6F, 0x69, 0x64, 0x6F, 0x52, 0x00, 0x00, 0x6B, 0x72, 0x74, 0x4D, 0x72, 0x61, 0x68, 0x43 } } });	// characteristic
	bool added = P2P::addCharacteristic(P2P::prepareUUID(42), 1, CHAR_PROP_NOTIFY, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, false, [](byte id, P2P::Notification notification, uint length, byte *data)
	{
		static byte val;
		if (notification == P2P::Notification::Write) val = *data;
		else
		{
			P2P::updateValue(id, 1, &val);
			P2P::allowRead();
		}
	});
	added = P2P::addCharacteristic(P2P::prepareUUID(43), 2, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, false, [](byte id, P2P::Notification notification, uint length, byte *data)
	{
		static byte val[2];
		val[0]++;
//		P2P::updateValue(id, 2, val);
//		P2P::allowRead();
	});
#ifdef STACK_DEBUG
	if (!added) printf("Add characteristic failed\n");
	serial.sendLine("Program started");
#endif // STACK_DEBUG
	SMPS::init(SMPS::Voltage::_1V40, SMPS::Current::_80MA, SMPS::Source::HSE);
	RTCm::init();
	BLE::Settings settings;
	sprintf(settings.name, "%s", "Artemida89");// external (visible) name
	sprintf(settings.dis.firmware, "v%2.2f", (float)108 / 100);
	sprintf(settings.dis.hardware, "%s", DISAPP_HARDWARE_REVISION_NUMBER);
	sprintf(settings.dis.manufacturer, "%s", DISAPP_MANUFACTURER_NAME);
	sprintf(settings.dis.model, "%s", DISAPP_MODEL_NUMBER);
	byte *mac = *((uint *)UID64_BASE) != 0xFFFFFFFF ? (byte *)UID64_BASE : (byte *)(const byte[]){ 0, 1, 2, 3, 4, 5 };
	for (byte i = 0; i < 6; i++) settings.dis.serial[i] = mac[i];
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
			serial.sendLine("Stack overflow");
			serial.sendLine(pcTaskName);
#endif // STACK_DEBUG
		}
	}
}