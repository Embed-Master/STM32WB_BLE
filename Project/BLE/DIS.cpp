#include "DIS.hpp"
#include "utilities.h"
#include "uuid.h"
#include "GATT.hpp"
#include "stdio.h"
#include "string.h"
#include "StackConfig.hpp"

DIS::Context DIS::context;

void DIS::init(Settings &settings)
{
	GATT::UUID uuid = { GATT::UUIDtype::_16bit, {._16bit = DEVICE_INFORMATION_SERVICE_UUID}};
	HCI::Status result;

	if ((result = GATT::addService(uuid, GATT::ServiceType::Primary, 13, context.service)) == HCI::Status::Success)
	{
#ifdef STACK_DEBUG
		printf("Device information service (DIS) is added successfully; Handle: %04X\n", context.service);
#endif // STACK_DEBUG
		char software[8];
		sprintf(software, "v%2.2f", STACK_VERSION);
		uuid.id._16bit = MANUFACTURER_NAME_UUID;
#ifndef STACK_DEBUG
		result = GATT::addCharacteristic(context.service, uuid, strlen(settings.manufacturer),	context.manufacturer,	CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true);
		uuid.id._16bit = MODEL_NUMBER_UUID;
		result = GATT::addCharacteristic(context.service, uuid, strlen(settings.model),			context.model,			CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true);
		uuid.id._16bit = SERIAL_NUMBER_UUID;
		result = GATT::addCharacteristic(context.service, uuid, 6,								context.serial,			CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true);
		uuid.id._16bit = HARDWARE_REVISION_UUID;
		result = GATT::addCharacteristic(context.service, uuid, strlen(settings.hardware),		context.hardware,		CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true);
		uuid.id._16bit = SOFTWARE_REVISION_UUID;
		result = GATT::addCharacteristic(context.service, uuid, strlen(software),				context.software,		CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true);
		uuid.id._16bit = FIRMWARE_REVISION_UUID;
		result = GATT::addCharacteristic(context.service, uuid, strlen(settings.firmware),		context.firmware,		CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true);
#else
		if ((result = GATT::addCharacteristic(context.service, uuid, strlen(settings.manufacturer), context.manufacturer, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true)) == HCI::Status::Success)
			printf("Manufacturer name characteristic added successfully; Handle: %04X\n", context.manufacturer);
		else printf("FAILED to add Manufacturer name characteristic; Status: %02X\n", (byte)result);
		uuid.id._16bit = MODEL_NUMBER_UUID;
		if ((result = GATT::addCharacteristic(context.service, uuid, strlen(settings.model), context.model, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true)) == HCI::Status::Success)
			printf("Model number string characteristic added successfully; Handle: %04X\n", context.model);
		else printf("FAILED to add Model number string characteristic; Status: %02X\n", (byte)result);
		uuid.id._16bit = SERIAL_NUMBER_UUID;
		if ((result = GATT::addCharacteristic(context.service, uuid, 6, context.serial, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true)) == HCI::Status::Success)
			printf("Serial number string characteristic added successfully; Handle: %04X\n", context.serial);
		else printf("FAILED to add Serial number string characteristic; Status: %02X\n", (byte)result);
		uuid.id._16bit = HARDWARE_REVISION_UUID;
		if ((result = GATT::addCharacteristic(context.service, uuid, strlen(settings.hardware), context.hardware, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true)) == HCI::Status::Success)
			printf("Hardware revision string characteristic added successfully; Handle: %04X\n", context.hardware);
		else printf("FAILED to add Hardware revision string characteristic; Status: %02X\n", (byte)result);
		uuid.id._16bit = SOFTWARE_REVISION_UUID;
		if ((result = GATT::addCharacteristic(context.service, uuid, strlen(software), context.software, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true)) == HCI::Status::Success)
			printf("Stack revision string characteristic added successfully; Handle: %04X\n", context.software);
		else printf("FAILED to add Stack revision string characteristic; Status: %02X\n", (byte)result);
		uuid.id._16bit = FIRMWARE_REVISION_UUID;
		if ((result = GATT::addCharacteristic(context.service, uuid, strlen(settings.firmware), context.firmware, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true)) == HCI::Status::Success)
			printf("Firmware revision string characteristic added successfully; Handle: %04X\n", context.firmware);
		else printf("FAILED to add Firmware revision string characteristic; Status: %02X\n", (byte)result);
#endif // !STACK_DEBUG
		if (result == HCI::Status::Success)
		{
			GATT::updateCharValue(context.service, context.manufacturer,	0, strlen(settings.manufacturer),	(byte *)settings.manufacturer);
			GATT::updateCharValue(context.service, context.model,			0, strlen(settings.model),			(byte *)settings.model);
			GATT::updateCharValue(context.service, context.serial,			0, 6,										settings.serial);
			GATT::updateCharValue(context.service, context.hardware,		0, strlen(settings.hardware),		(byte *)settings.hardware);
			GATT::updateCharValue(context.service, context.software,		0, strlen(software),				(byte *)software);
			GATT::updateCharValue(context.service, context.firmware,		0, strlen(settings.firmware),		(byte *)settings.firmware);
		}
	}
#ifdef STACK_DEBUG
	else printf("FAILED to add Device information service (DIS); Status: %02X\n", (byte)result);
#endif // STACK_DEBUG
}