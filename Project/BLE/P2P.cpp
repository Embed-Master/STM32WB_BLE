#include "P2P.hpp"
#include "stdio.h"
#include "utilities.h"
#include "string.h"
#include "legacy.h"

P2P *P2P::service[P2P_MAX_SERVICE_CNT];
byte P2P::serviceCnt;
ushort P2P::connection;

Service::EvtStatus P2P::event(TL::Event * evt)
{
	TL::BleEvt *bleEvt = (TL::BleEvt *)evt->payload;
	GATT::AttributeModifiedEvent::Response *rsp = (GATT::AttributeModifiedEvent::Response *)bleEvt->payload;
	if (bleEvt->code == EVT_BLUE_GATT_ATTRIBUTE_MODIFIED)
	{
		for (byte s = 0; s < serviceCnt; s++)
		{
			for (byte c = 0; c < service[s]->context.charCnt; c++)
			{
				if (rsp->handle == service[s]->context.characteristic[c] + 1 && (service[s]->config[c].properties & CHAR_PROP_WRITE))
				{
					service[s]->config[c].callback(c, Request::Write, rsp->length, rsp->data);
#ifdef STACK_DEBUG
					printf("P2P Service %d Write Parameter %d received, len = %d\n", s, c, rsp->length);
#endif // STACK_DEBUG
					return Service::EvtStatus::Ack;
				}
				else if (rsp->handle == service[s]->context.characteristic[c] + 2 && (service[s]->config[c].properties & CHAR_PROP_NOTIFY))
				{
					service[s]->config[c].callback(c, rsp->data[0] & (byte)Service::CharMode::Notification ? Request::NotificationEnabled : Request::NotificationDisabled, 0, nullptr);
#ifdef STACK_DEBUG
					printf("P2P Service %d Notification Parameter %d ", s, c);
					if (rsp->data[0] & (byte)Service::CharMode::Notification) printf("Enabled\n");
					else printf("Disabled\n");
#endif // STACK_DEBUG
					return Service::EvtStatus::Ack;
				}
			}	
		}
	}
	else if (bleEvt->code == EVT_BLUE_GATT_READ_PERMIT_REQ)
	{
		for (byte s = 0; s < serviceCnt; s++)
		{
			for (byte c = 0; c < service[s]->context.charCnt; c++)
			{
				if (rsp->handle == service[s]->context.characteristic[c] + 1 && (service[s]->config[c].properties & CHAR_PROP_READ))
				{
					service[s]->config[c].callback(c, Request::Read, 0, nullptr);
#ifdef STACK_DEBUG
					printf("P2P Service %d Read Parameter %d received\n", s, c);
#endif // STACK_DEBUG
					return Service::EvtStatus::Ack;
				}
			}	
		}
	}
	return Service::EvtStatus::NotAck;
}

void P2P::allowRead()
{
	GATT::allowRead(connection);
}

bool P2P::updateValue(byte id, ushort length, byte *data)
{
	if (id > context.charCnt || length > config[id].length) return false;
	ushort remain = length;
	while (remain)
	{
		byte size = remain >= 255 ? 255 : remain;
		GATT::updateCharValue(context.service, context.characteristic[id], length - remain, size, data + length - remain);
		remain -= size;
	}
	return true;
}

void P2P::init()
{
	if (!serviceCnt) return;
	HCI::Status result;
	Service::regServer(event);
	for (byte s = 0; s < serviceCnt; s++)
	{
		byte length = 0;
		GATT::UUID uuid = { GATT::UUIDtype::_128bit, { ._128bit = { BLE_P2P_CHARACTERISTIC_BASE_UUID } } };
		uuid.id._128bit[7] = service[s]->context.uuid.id._128bit[6];
		for (byte c = 0; c < service[s]->context.charCnt; c++) length += service[s]->config[c].properties & CHAR_PROP_NOTIFY ? 3 : 2;	
#ifndef STACK_DEBUG
		result = GATT::addService(service[s]->context.uuid, GATT::ServiceType::Primary, length + 1, service[s]->context.service);
#else
		if ((result = GATT::addService(service[s]->context.uuid, GATT::ServiceType::Primary, length + 1, service[s]->context.service)) == HCI::Status::Success)	printf("P2P Service is added Successfully; Handle: 0x%04X\n", service[s]->context.service);
		else printf("FAILED to add P2P Service; Status: 0x%02X\n", (byte)result);
#endif // !STACK_DEBUG
		if (result == HCI::Status::Success)
		{
			for (byte c = 0; c < service[s]->context.charCnt; c++)
			{
#ifndef STACK_DEBUG
				GATT::addCharacteristic(service[s]->context.service, uuid, service[s]->config[c].length, service[s]->context.characteristic[c], service[s]->config[c].properties, service[s]->config[c].permissions, service[s]->config[c].events, 10, service[s]->config[c].variable);
#else
				if ((result = GATT::addCharacteristic(service[s]->context.service, uuid, service[s]->config[c].length, service[s]->context.characteristic[c], service[s]->config[c].properties, service[s]->config[c].permissions, service[s]->config[c].events, 10, service[s]->config[c].variable)) == HCI::Status::Success)
					printf("Parameter %d Added Successfully; Handle: 0x%04X\n", c, service[s]->context.characteristic[c]);
				else printf("FAILED to add Parameter %d; Status: 0x%02X\n", c, (byte)result);
#endif // !STACK_DEBUG
				uuid.id._128bit[6]++;
			}
			if (result == HCI::Status::Success) for (byte c = 0; c < service[s]->context.charCnt; c++) if (service[s]->config[c].properties & CHAR_PROP_READ) service[s]->config[c].callback(c, Request::Read, 0, nullptr);
		}
	}
}

P2P::P2P(GATT::UUID &&uuid, const CharConfig conf[])
{
	context.charCnt = 0;
	const CharConfig *ptr = conf;
	uint cnt = 0;
	while (ptr++->properties) cnt++;
	context.characteristic = new ushort[cnt];
	config = (CharConfig *)(new byte[sizeof(CharConfig) * cnt]);
	if (!context.characteristic || !config)
	{
#ifdef STACK_DEBUG
		printf("P2P Service memory allocation failed\n");
#endif // !STACK_DEBUG
		return;
	}
#ifdef STACK_DEBUG
	else printf("P2P Service memory allocation successful\n");
#endif // !STACK_DEBUG
	ptr = conf;
	for (byte i = 0; i < cnt; i++) config[i] = *ptr++;
	service[serviceCnt++] = this;
	context.uuid = uuid;
	context.charCnt = cnt;
}