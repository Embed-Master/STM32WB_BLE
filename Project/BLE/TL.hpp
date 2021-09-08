#pragma once

#include "Types.h"
#include "List.hpp"
#include "StackConfig.hpp"
#include "FreeRTOS.h"
#include "task.h"
#include "legacy.h"

#define IPCC_CHANNEL_BLE		0
#define IPCC_CHANNEL_SYSTEM		1
#define IPCC_CHANNEL_TRACE		3

class TL
{
public:
	enum class PacketType : byte
	{
		BLECMD     = 0x01,
		ACL_DATA   = 0x02,
		BLEEVT     = 0x04,
		OTCMD      = 0x08,
		OTRSP      = 0x09,
		CLICMD     = 0x0A,
		OTNOT      = 0x0C,
		OTACK      = 0x0D,
		CLINOT     = 0x0E,
		CLIACK     = 0x0F,
		SYSCMD     = 0x10,
		SYSRSP     = 0x11,
		SYSEVT     = 0x12,
		CLIRESP    = 0x15,
		M0CMD      = 0x16,
		LOCCMD     = 0x20,
		LOCRSP     = 0x21,
		TRACES_APP = 0x40,
		TRACES_WL  = 0x41
	};
	struct PacketHeader
	{
		uint *next;
		uint *prev;
	} __attribute__((packed));
	struct Cmd
	{
		ushort code;
		byte length;
		byte payload[255];
	} __attribute__((packed));
	struct CmdSerial
	{
		byte type;
		Cmd cmd;
	} __attribute__((packed));
	struct CmdPacket
	{
		PacketHeader header;
		CmdSerial serial;
	} __attribute__((packed));
	struct Event
	{
		byte code;
		byte length;
		byte payload[1];
	} __attribute__((packed));
	struct EvtSerial
	{
		byte type;
		Event evt;
	} __attribute__((packed));
	struct EvtPacket
	{
		PacketHeader header;
		EvtSerial serial;
	} __attribute__((packed));
	struct BleEvt
	{
		ushort	code;
		byte	payload[1];
	} __attribute__((packed));
	struct CcEvt
	{
		byte	numcmd;
		ushort	cmdcode;
		byte	payload[1];
	} __attribute__((packed));
	struct CsEvt
	{
		byte	status;
		byte	numcmd;
		ushort	cmdcode;
	} __attribute__((packed));
	struct Data
	{
		byte type;
		byte data[1];
	};
	class MemoryManager
	{
		static List::Node freeBufQueue;
		static List::Node localFreeBufQueue;	
		static const uint poolSize = CFG_TLBLE_EVT_QUEUE_LENGTH * 4 * ((sizeof(TL::PacketHeader) + TL_BLE_EVENT_FRAME_SIZE + 4 - 1) / 4);
		static byte evtPool[poolSize];
		static byte systemSpareEvtBuffer[sizeof(PacketHeader) + TL_EVT_HDR_SIZE + 255U];
		static byte bleSpareEvtBuffer[sizeof(PacketHeader) + TL_EVT_HDR_SIZE + 255];
		
		static void sendFreeBuf();
#ifdef STACK_DEBUG
		static void trace(EvtPacket * phcievt);
#endif // STACK_DEBUG
		static void callback();
		
	public:
		static void evtDone(EvtPacket * evt);
		static void init();
	};
	
private:
	struct Mailbox
	{
		/**
		 * Version
		 * [0:3]   = Build - 0: Untracked - 15:Released - x: Tracked version
		 * [4:7]   = branch - 0: Mass Market - x: ...
		 * [8:15]  = Subversion
		 * [16:23] = Version minor
		 * [24:31] = Version major
		 *
		 * Memory Size
		 * [0:7]   = Flash ( Number of 4k sector)
		 * [8:15]  = Reserved ( Shall be set to 0 - may be used as flash extension )
		 * [16:23] = SRAM2b ( Number of 1k sector)
		 * [24:31] = SRAM2a ( Number of 1k sector)
		 */
		struct SafeBootInfo
		{
			uint    version;
		} __attribute__((packed)) ;
		struct FusInfo
		{
			uint    version;
			uint    memorySize;
			uint    fusInfo;
		} __attribute__((packed));
		struct WirelessFwInfo
		{
			uint    version;
			uint    memorySize;
			uint    infoStack;
			uint    reserved;
		} __attribute__((packed));
		struct DeviceInfoTable
		{
			SafeBootInfo      safeBootInfoTable;
			FusInfo           fusInfoTable;
			WirelessFwInfo    wirelessFwInfoTable;
		} __attribute__((aligned(4))) info;
		struct Ble
		{
			byte     *cmd;
			byte     *status;
			byte     *queue;
			byte     *aclDataBuffer;
		} __attribute__((aligned(4))) ble;
		struct Thread
		{
			byte   *notAck;
			byte   *cliCmdRsp;
			byte   *otCmdRsp;
		} __attribute__((aligned(4))) thread;
		struct LldTests
		{
			byte   *cliCmdRsp;
			byte   *m0cmd;
		} __attribute__((aligned(4))) lldTests;
		struct LldBle
		{
			byte   *cmdRsp;
			byte   *m0cmd;
		} __attribute__((aligned(4))) lldBle;
		struct Zigbee
		{
			byte   *notifM0toM4;
			byte   *appCmdM4toM0;
			byte   *requestM0toM4;
		} __attribute__((aligned(4))) zigbee;
		struct System
		{
			byte   *cmd;
			byte   *queue;
		} __attribute__((aligned(4))) system;
		struct MemManager
		{
			byte	*bleBuf;
			byte	*sysBuf;
			byte	*blePool;
			uint	blePoolSize;
			byte	*evtFreeBufQueue;
			byte	*traceEvt;
			uint	tracePoolSize;
		} __attribute__((aligned(4))) memManager;
		struct TracesTable
		{
			byte   *traceQueue;
		} __attribute__((aligned(4))) traces;
		struct Mac_802_15_4
		{
			byte   *cmdRsp;
			byte   *notAck;
			byte   *evtQueue;
		} __attribute__((aligned(4))) mac_802_15_4;
	};
	struct RefTable
	{
		Mailbox::DeviceInfoTable	*info;
		Mailbox::Ble				*ble;
		Mailbox::Thread				*thread;
		Mailbox::System				*system;
		Mailbox::MemManager			*memoryManager;
		Mailbox::TracesTable		*trace;
		Mailbox::Mac_802_15_4		*mac_802_15_4;
		Mailbox::Zigbee				*zigbee;
		Mailbox::LldTests			*lldTests;
		Mailbox::LldBle				*lldBle;
	};
	class Trace
	{
		static List::Node evtQueue;
		
		static void eventCallback();
	public:
		static void init();	
	};
	
	static Mailbox mailbox;
	static RefTable refTable;
	
public:
	static void init();
	static void setSHCIBuffer(CmdPacket &commandBuf, List::Node &evtQueue);
	static void setHCIBuffer(CmdPacket &commandBuf, byte *commandStatusBuf, List::Node &evtQueue);
};