#pragma once

#include "TL.hpp"

/* HCI parameters length */
#define HCI_COMMAND_MAX_PARAM_LEN        255
#define HCI_EVENT_MAX_PARAM_LEN          255

class HCI
{
public:
	struct Init
	{
		byte* pBleBufferAddress; /**< NOT USED CURRENTLY */
		uint BleBufferSize; /**< Size of the Buffer allocated in pBleBufferAddress  */
		ushort NumAttrRecord;
		ushort NumAttrServ;
		ushort AttrValueArrSize;
		byte NumOfLinks;
		byte ExtendedPacketLengthEnable;
		byte PrWriteListSize;
		byte MblockCount;
		ushort AttMtu;
		ushort SlaveSca;
		byte MasterSca;
		byte LsSource;
		uint MaxConnEventLength;
		ushort HsStartupTime;
		byte ViterbiEnable;
		byte LlOnly;
		byte HwVersion;
	} __attribute__((packed));
	enum class Status : byte
	{
		Success = 0x00,
		SecUnknownConnectionID = 0x40,
		Failed = 0x41,
		InvalidParams = 0x42,
		Busy = 0x43,
		Pending = 0x45,
		NotAllowed = 0x46,
		Error = 0x47,
		OutOfMemory = 0x48,
		InvalidCID = 0x50,
		DevInBlacklist = 0x59,
		CsrkNotFound = 0x5A,
		IrkNotFound = 0x5B,
		DevNotFoundInDb = 0x5C,
		SecDbFull = 0x5D,
		DevNotBonded = 0x5E,
		InsufficientEncKeysize = 0x5F,
		InvalidHandle = 0x60,
		OutOfHandle = 0x61,
		InvalidOperation = 0x62,
		CharacAlreadyExists = 0x63,
		InsufficientResources = 0x64,
		SecPermissionError = 0x65,
		AddrNotResolved = 0x70,

		/* Returned when no valid slots are available
		 * (e.g. when there are no available state machines).
		 */
		NoValidSlot = 0x82,

		/* Returned when a scan window shorter than minimum allowed value has been
		 * requested (i.e. 2ms)
		 */
		ScanWindowShort = 0x83,

		/* Returned when the maximum requested interval to be allocated is shorter
		 * then the current anchor period and a there is no submultiple for the
		 * current anchor period that is between the minimum and the maximum requested
		 * intervals.
		 */
		NewIntervalFailed = 0x84,

		/* Returned when the maximum requested interval to be allocated is greater
		 * than the current anchor period and there is no multiple of the anchor
		 * period that is between the minimum and the maximum requested intervals.
		 */
		IntervalTooLarge = 0x85,

		/* Returned when the current anchor period or a new one can be found that
		 * is compatible to the interval range requested by the new slot but the
		 * maximum available length that can be allocated is less than the minimum
		 * requested slot length.
		 */
		LengthFailed = 0x86,
		Timeout = 0xFF
	};
	struct Request
	{
		void *parameter;
		uint length;
	};
	
private:		
	static TaskHandle_t thread;
	static TaskHandle_t eventHandlerHandle;
	static TL::CmdPacket packet;
	static List::Node evtQueue;
	static List::Node cmdEventQueue;
	static List::Node asynchEventQueue;
	static byte csBuffer[sizeof(TL::PacketHeader) + TL_EVT_HDR_SIZE + sizeof(TL::CsEvt)];
	
#ifdef STACK_DEBUG
	static void commandTrace(TL::CmdPacket *pack);
	static void responseTrace(TL::EvtPacket *evt);
	static void eventTrace(TL::EvtPacket *evt);
#endif // STACK_DEBUG
	static void eventCallback();
	static void eventHandler(void *args);
	
	public:
	static void send(ushort opcode, Request * request = nullptr, byte length = 0, byte * payload = nullptr);
	static void init(void (* nextStage)(), TaskHandle_t initThread);
};