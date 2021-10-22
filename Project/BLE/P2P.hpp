#pragma once

#include "TL.hpp"
#include "Service.hpp"
#include "StackConfig.hpp"
#include "GATT.hpp"

class P2P
{
	friend class BLE;
	friend class Service;
public:
	enum class Request : byte
	{
		NotificationEnabled,
		NotificationDisabled,
		Read,
		Write
	};
	struct CharConfig
	{
		void (*callback)(byte, Request, uint, byte *);
		ushort length;
		byte properties;
		byte permissions;
		byte events;
		bool variable;
	};
	
private:
	struct Context
	{
		GATT::UUID uuid;
		ushort service;
		ushort *characteristic;
		byte charCnt;
	};
	
	static P2P *service[P2P_MAX_SERVICE_CNT];
	static byte serviceCnt;
	static ushort connection;
	Context context;
	CharConfig *config;
	
	static inline void connectionSet(ushort con) { connection = con; }  // kostil
	static Service::EvtStatus event(TL::Event * evt);
	static void init();
	
public:
	bool updateValue(byte id, ushort length, byte *data);
	static void allowRead();
	P2P(GATT::UUID uuid, CharConfig conf[]);
};