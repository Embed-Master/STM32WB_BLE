#pragma once

#include "TL.hpp"
#include "DIS.hpp"

class Service
{
public:
	enum class EvtStatus : byte
	{
		NotAck,
		Ack
	};
	
private:
	struct ServerList
	{
		EvtStatus (* ptr[BLE_SERVICES_SERVICE_MAX])(TL::Event *evt);
		byte count;
	};
	struct ClientList
	{
		EvtStatus(* ptr[BLE_SERVICES_CLIENT_MAX])(TL::Event *evt);
		byte count;
	};
	
	static ServerList srvList;
	static ClientList cltList;
	
public:
	enum class CharMode : byte
	{
		Notification = (1 << 0),
		Indication   = (1 << 1),
	};
	
	static EvtStatus eventReceived(TL::Event *event);
	static void regServer(EvtStatus (* handler)(TL::Event *));
	static void regClient(EvtStatus (* handler)(TL::Event *));
	static void init(DIS::Settings &settings);
};