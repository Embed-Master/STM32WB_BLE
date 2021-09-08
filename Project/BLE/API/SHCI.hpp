#pragma once

#include "TL.hpp"

class SHCI
{
	static const byte OGF = 0x3F; // OpCode Group Field
	static const ushort OCF_BASE = 0x50; // OpCode Command Field
	static TL::CmdPacket packet;
	static List::Node evtQueue;
	static List::Node asynchEventQueue;
	static TaskHandle_t eventHandlerHandle;
	static void (*callback)(TaskHandle_t);
		
#ifdef STACK_DEBUG
	static void commandTrace(TL::CmdPacket *cmd);
	static void eventTrace(TL::EvtPacket *evt);
	static void responseTrace(TL::EvtPacket *evt);
#endif // STACK_DEBUG
	static void eventHandler(void *args);
	static void eventCallback();
	static void cmdResponse();
		
public:
	enum class Opcode : ushort
	{
		RESERVED1 = (OGF << 10) + OCF_BASE,
		RESERVED2,
		FUS_GET_STATE,
		FUS_RESERVED1,
		FUS_FW_UPGRADE,
		FUS_FW_DELETE,
		FUS_UPDATE_AUTH_KEY,
		FUS_LOCK_AUTH_KEY,
		FUS_STORE_USR_KEY,
		FUS_LOAD_USR_KEY,
		FUS_START_WS,
		FUS_RESERVED2,
		FUS_RESERVED3,
		FUS_LOCK_USR_KEY,
		FUS_RESERVED5,
		FUS_RESERVED6,
		FUS_RESERVED7,
		FUS_RESERVED8,
		FUS_RESERVED9,
		FUS_RESERVED10,
		FUS_RESERVED11,
		FUS_RESERVED12,
		C2_BLE_INIT,
		THREAD_INIT,
		C2_DEBUG_INIT,
		FLASH_ERASE_ACTIVITY,
		CONCURRENT_SET_MODE,
		FLASH_STORE_DATA,
		FLASH_ERASE_DATA,
		RADIO_ALLOW_LOW_POWER,
		MAC_802_15_4_INIT,
		REINIT,
		ZIGBEE_INIT,
		LLD_TESTS_INIT,
		EXTPA_CONFIG,
		SET_FLASH_ACTIVITY_CONTROL,
		LLD_BLE_INIT
	};
		
	static void send(Opcode opcode, byte length, byte * payload, TL::EvtPacket * evt = nullptr);
	static void init(void (*callback)(TaskHandle_t));
};