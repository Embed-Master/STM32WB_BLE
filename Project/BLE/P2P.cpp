#include "P2P.hpp"
#include "stdio.h"
#include "utilities.h"
#include "string.h"
#include "legacy.h"

P2P::Context P2P::context;
ushort P2P::connection;
P2P::Callback P2P::callback[P2P_PARAMETER_CNT];
byte P2P::callbackCnt;
GATT::UUID P2P::serviceUUID;
GATT::UUID P2P::charUUID;

void P2P::connectionSet(ushort con)
{
	connection = con;
}

GATT::UUID P2P::prepareUUID(byte shift)
{
	GATT::UUID uuid = charUUID;
	uuid.id._128bit[6] += shift;
	return uuid;
}

Service::EvtStatus P2P::event(TL::Event * evt)
{
	TL::BleEvt *bleEvt = (TL::BleEvt *)evt->payload;
	GATT::AttributeModifiedEvent::Response *rsp = (GATT::AttributeModifiedEvent::Response *)bleEvt->payload;
	if (bleEvt->code == EVT_BLUE_GATT_ATTRIBUTE_MODIFIED)
	{
		for (byte i = 0; i < callbackCnt; i++)
		{
			if (rsp->handle == context.characteristic[i] + 1 && (callback[i].properties & CHAR_PROP_WRITE))
			{
				callback[i].ptr(i, Notification::Write, rsp->length, rsp->data);
#ifdef STACK_DEBUG
				printf("P2P Write Parameter %d received, len = %d\n", i, rsp->length);
#endif // STACK_DEBUG
				return Service::EvtStatus::Ack;
			}
			else if (rsp->handle == context.characteristic[i] + 2 && (callback[i].properties & CHAR_PROP_NOTIFY))
			{
				callback[i].ptr(i, rsp->data[0] & (byte)Service::CharMode::Notification ? Notification::NotificationEnabled : Notification::NotificationDisabled, 0, nullptr);
#ifdef STACK_DEBUG
				printf("P2P Notification Parameter %d ", i);
				if (rsp->data[0] & (byte)Service::CharMode::Notification) printf("Enabled\n");
				else printf("Disabled\n");
#endif // STACK_DEBUG
				return Service::EvtStatus::Ack;				
			}
		}
	}
	else if (bleEvt->code == EVT_BLUE_GATT_READ_PERMIT_REQ)
	{
		for (byte i = 0; i < callbackCnt; i++)
		{
			if (rsp->handle == context.characteristic[i] + 1 && (callback[i].properties & CHAR_PROP_READ) == CHAR_PROP_READ)
			{
				callback[i].ptr(i, Notification::Read, 0, nullptr);
#ifdef STACK_DEBUG
				printf("P2P Read Parameter %d received\n", i);
#endif // STACK_DEBUG
				return Service::EvtStatus::Ack;
			}
		}
	}
	return Service::EvtStatus::NotAck;
}

bool P2P::addCharacteristic(GATT::UUID uuid, byte length, byte properties, byte permissions, byte events, bool variable, void (ptr)(byte, Notification, uint, byte *))
{
	if (callbackCnt < P2P_PARAMETER_CNT && ptr)
	{
		callback[callbackCnt].uuid = uuid;
		callback[callbackCnt].length = length;
		callback[callbackCnt].properties = properties;
		callback[callbackCnt].permissions = permissions;
		callback[callbackCnt].events = events;
		callback[callbackCnt].variable = variable;
		callback[callbackCnt++].ptr = ptr;
		return true;
	}
	return false;
}

void P2P::allowRead()
{
	GATT::allowRead(connection);
}

bool P2P::updateValue(byte id, uint length, byte *data)
{
	if (id > callbackCnt || id < 0 || length > callback[id].length) return false;
	GATT::updateCharValue(context.service, context.characteristic[id], 0, length, data);
	return true;
}

void P2P::init()
{
	if (!callbackCnt) return;
	HCI::Status result;
	Service::regServer(event);
	byte length = 0;
	for (byte i = 0; i < callbackCnt; i++) length += callback[i].properties & CHAR_PROP_NOTIFY ? 3 : 2;
#ifndef STACK_DEBUG
	result = GATT::addService(uuid, GATT::ServiceType::Primary, length + 1, context.service);
#else
	if ((result = GATT::addService(serviceUUID, GATT::ServiceType::Primary, length + 1, context.service)) == HCI::Status::Success)	printf("P2P Service is added Successfully; Handle: 0x%04X\n", context.service);
	else printf("FAILED to add P2P Service; Status: 0x%02X\n", (byte)result);
#endif // !STACK_DEBUG
	if (result == HCI::Status::Success)	for (byte i = 0; i < callbackCnt; i++)
	{
#ifndef STACK_DEBUG
		GATT::addCharacteristic(context.service, callback[i].uuid, 10, context.characteristic[i], callback[i].properties, callback[i].permissions, callback[i].events, 10, true);
#else
		if ((result = GATT::addCharacteristic(	context.service, callback[i].uuid, callback[i].length, context.characteristic[i],
												callback[i].properties, callback[i].permissions, callback[i].events, 10, true)) == HCI::Status::Success)
			printf("Parameter %d Added Successfully; Handle: 0x%04X\n", i, context.characteristic[i]);
		else printf("FAILED to add Parameter %d; Status: 0x%02X\n", i, (byte)result);
#endif // !STACK_DEBUG
	}
}