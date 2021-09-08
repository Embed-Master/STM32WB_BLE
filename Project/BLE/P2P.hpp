#pragma once

#include "TL.hpp"
#include "Service.hpp"
#include "StackConfig.hpp"
#include "GATT.hpp"

class P2P
{
public:
	enum class Notification : byte
	{
		NotificationEnabled,
		NotificationDisabled,
		Read,
		Write
	};
	
private:
	struct Context
	{
		ushort service;
		ushort characteristic[P2P_PARAMETER_CNT];
	};
	struct Callback
	{
		void (*ptr)(byte id, Notification notification, uint length, byte *data);
		GATT::UUID uuid;
		byte length;
		byte properties;
		byte permissions;
		byte events;
		bool variable;
	};
	
	static Context context;
	static ushort connection;
	static Callback callback[P2P_PARAMETER_CNT];
	static byte callbackCnt;
	static GATT::UUID serviceUUID;
	static GATT::UUID charUUID;
	
public:
	static void connectionSet(ushort con); // kostil
	static inline void initUUID(GATT::UUID &uuidS, GATT::UUID &uuidC) { serviceUUID = uuidS; charUUID = uuidC;}// That method should be called before BLE initialization
	static GATT::UUID prepareUUID(byte shift);
	/*
	 *	addCharacteristic() - register characteristics for P2P service and callback for them
	 *	This method should be called before BLE initialization
	 *	All characteristics must be registered before BLE initialization
	 *	*/
	static bool addCharacteristic(GATT::UUID uuid, byte length, byte properties, byte permissions, byte events, bool variable, void (ptr)(byte, Notification, uint, byte *));
	static Service::EvtStatus event(TL::Event * evt);
	static bool updateValue(byte id, uint length, byte *data);
	static void allowRead();
	static void init();
};