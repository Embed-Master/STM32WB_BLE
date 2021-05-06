#pragma once

#include "Types.h"

/**
 *********************************************************************************
 * IPCC CHANNELS
 *********************************************************************************
 */
/*  CPU1                                             CPU2
 *   |             (SYSTEM)                            |
 *   |----HW_IPCC_SYSTEM_CMD_RSP_CHANNEL-------------->|
 *   |                                                 |
 *   |<---HW_IPCC_SYSTEM_EVENT_CHANNEL-----------------|
 *   |                                                 |
 *   |             (BLE)                               |
 *   |----HW_IPCC_BLE_CMD_CHANNEL--------------------->|
 *   |                                                 |
 *   |----HW_IPCC_HCI_ACL_DATA_CHANNEL---------------->|
 *   |                                                 |
 *   |<---HW_IPCC_BLE_EVENT_CHANNEL--------------------|
 *   |                                                 |
 *   |             (BUFFER)                            |
 *   |----HW_IPCC_MM_RELEASE_BUFFER_CHANNE------------>|
 *   |                                                 |
 *   |             (TRACE)                             |
 *   |<----HW_IPCC_TRACES_CHANNEL----------------------|
 *   |                                                 |
 */

extern "C"
{
	void IPCC_C1_RX_IRQHandler();
	void IPCC_C1_TX_IRQHandler();
}

class IPCCm
{
public:
	enum class Direction : byte
	{
		Rx,
		Tx
	};
	
	static bool expected(Direction direction, byte channel);
	static bool pending(Direction direction, byte channel);
	static bool eventReady(Direction direction, byte channel);
	static void unExpect(Direction direction, byte channel);
	static void expect(Direction direction, byte channel);
	static void occupy(byte channel, bool expect = false);
	static void setCallBack(void(*callback)(), Direction direction, byte channel);
	static void init();
	
private:
	static void (*callback[12])();
	friend void IPCC_C1_RX_IRQHandler();
	friend void IPCC_C1_TX_IRQHandler();
	static void interrupt(Direction direction);
};