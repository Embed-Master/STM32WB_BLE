#include "BS.hpp"
#include "uuid.h"
#include "GATT.hpp"
#include "stdio.h"
#include "string.h"

BS::Context BS::context;

void BS::setValue(float voltage)
{
	char str[8];
	sprintf(str, "%2.2fv", voltage);
	GATT::updateCharValue(context.service, context.level, 0, strlen(str), (byte *)str);
}

void BS::init()
{
	GATT::UUID uuid = { GATT::UUIDtype::_16bit, {._16bit = BATTERY_SERVICE_UUID}};
	HCI::Status result;

	if ((result = GATT::addService(uuid, GATT::ServiceType::Primary, 3, context.service)) == HCI::Status::Success)
	{
#ifdef STACK_DEBUG
		printf("Battery service (BS) is added successfully; Handle: 0x%04X\n", context.service);
#endif // STACK_DEBUG
		uuid.id._16bit = BATTERY_LEVEL_CHAR_UUID;
		if ((result = GATT::addCharacteristic(context.service, uuid, 6, context.level, CHAR_PROP_READ, ATTR_PERMISSION_NONE, GATT_DONT_NOTIFY_EVENTS, 10, true)) == HCI::Status::Success)
		{
#ifdef STACK_DEBUG
			printf("Battery level characteristic added successfully; Handle: 0x%04X\n", context.level);
#endif // STACK_DEBUG
			setValue(3.3f);
		}
#ifdef STACK_DEBUG
		else printf("FAILED to add Battery level characteristic; Status: 0x%02X\n", (byte)result);
#endif // STACK_DEBUG
	}
#ifdef STACK_DEBUG
	else printf("FAILED to add Battery service (BS); Status: 0x%02X\n", (byte)result);
#endif // STACK_DEBUG
}