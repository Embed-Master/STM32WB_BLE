#include "Service.hpp"
#include "utilities.h"
#include "BLE.hpp"
#include "BS.hpp"
#include "P2P.hpp"
#include "legacy.h"

Service::ServerList Service::srvList;
Service::ClientList Service::cltList;

Service::EvtStatus Service::eventReceived(TL::Event *evt)
{
	EvtStatus status = EvtStatus::NotAck;
	if (evt->code == EVT_VENDOR)
	{
		if (((((TL::BleEvt *)evt->payload)->code) & SVCCTL_EGID_EVT_MASK) == SVCCTL_GATT_EVT_TYPE)
		{
			for (byte index = 0; index < srvList.count; index++)
			{
				status = srvList.ptr[index](evt);
				if (status != EvtStatus::NotAck) break;
			}
			for (byte index = 0; index < cltList.count; index++)
			{
				status = cltList.ptr[index](evt);
				if (status != EvtStatus::NotAck) break;
			}
		}
	}
	if (status == EvtStatus::NotAck) BLE::appNotification(evt);
	return status;
}

void Service::regServer(EvtStatus (* handler)(TL::Event *))
{
	if (srvList.count < BLE_CFG_SVCCTL_MAX) srvList.ptr[srvList.count++] = handler;
}

void Service::regClient(EvtStatus (* handler)(TL::Event *))
{
	if (cltList.count < BLE_CFG_CLT_MAX) cltList.ptr[cltList.count++] = handler;
}

void Service::init(DIS::Settings &settings)
{
	srvList.count = 0;
	cltList.count = 0;
	DIS::init(settings);
	BS::init();
	P2P::init();
}