#include "TL.hpp"
#include "IPCC.hpp"
#include "utilities.h"
#include "stdio.h"

/******************************************************************************
 * GENERAL
 ******************************************************************************/
PLACE_IN_SECTION("MAPPING_TABLE") TL::RefTable		TL::refTable;
PLACE_IN_SECTION("MB_MEM1") ALIGN(4) TL::Mailbox	TL::mailbox;

/******************************************************************************
 * MEMORY MANAGER
 ******************************************************************************/
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) byte TL::MemoryManager::evtPool[TL::MemoryManager::poolSize];
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) byte TL::MemoryManager::systemSpareEvtBuffer[sizeof(TL::PacketHeader) + TL_EVT_HDR_SIZE + 255];
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) byte TL::MemoryManager::bleSpareEvtBuffer[sizeof(TL::PacketHeader) + TL_EVT_HDR_SIZE + 255];
PLACE_IN_SECTION("MB_MEM1") ALIGN(4) List::Node TL::MemoryManager::freeBufQueue;
List::Node TL::MemoryManager::localFreeBufQueue;

/******************************************************************************
 * TRACE
 ******************************************************************************/
PLACE_IN_SECTION("MB_MEM1") ALIGN(4) List::Node TL::Trace::evtQueue;

/******************************************************************************
 * GENERAL
 ******************************************************************************/
void TL::setSHCIBuffer(CmdPacket &commandBuf, List::Node &evtQueue)
{
	refTable.system->cmd = (byte *)&commandBuf;
	refTable.system->queue = (byte *)&evtQueue;
}

void TL::setHCIBuffer(CmdPacket &commandBuf, byte *commandStatusBuf, List::Node &evtQueue)
{
	refTable.ble->cmd = (byte *)&commandBuf;
	refTable.ble->status = commandStatusBuf;
	refTable.ble->queue = (byte *)&evtQueue;
}

void TL::init()
{
	refTable.info			= &mailbox.info;
	refTable.ble			= &mailbox.ble;
	refTable.thread			= &mailbox.thread;
	refTable.lldTests		= &mailbox.lldTests;
	refTable.lldBle			= &mailbox.lldBle;
	refTable.system			= &mailbox.system;
	refTable.memoryManager	= &mailbox.memManager;
	refTable.trace			= &mailbox.traces;
	refTable.mac_802_15_4	= &mailbox.mac_802_15_4;
	refTable.zigbee			= &mailbox.zigbee;
	IPCCm::init();
	MemoryManager::init();
	Trace::init();
}

/******************************************************************************
 * MEMORY MANAGER
 ******************************************************************************/
void TL::MemoryManager::sendFreeBuf()
{
	List::Node *node;
	while (!List::empty(&localFreeBufQueue))
	{
		List::removeHead(&localFreeBufQueue, (List::Node **)&node);
		List::insertTail((List::Node *)(refTable.memoryManager->evtFreeBufQueue), node);
	}
}

void TL::MemoryManager::callback()
{
	sendFreeBuf();
	IPCCm::occupy(IPCC_CHANNEL_TRACE);
}

void TL::MemoryManager::evtDone(EvtPacket * evt)
{
	List::insertTail(&localFreeBufQueue, (List::Node *)evt);
#ifdef STACK_DEBUG
	trace(evt);
#endif // STACK_DEBUG
	if (IPCCm::pending(IPCCm::Direction::Tx, IPCC_CHANNEL_TRACE)) IPCCm::expect(IPCCm::Direction::Tx, IPCC_CHANNEL_TRACE);
	else
	{
		sendFreeBuf();
		IPCCm::occupy(IPCC_CHANNEL_TRACE);
	}
}

#ifdef STACK_DEBUG
void TL::MemoryManager::trace(EvtPacket * evt)
{
	switch (evt->serial.evt.code)
	{
	case TL_BLEEVT_CS_OPCODE:
		printf("MemMan evt released: 0x%02X; ", evt->serial.evt.code);
		printf("Cmd opcode: 0x%04X; ", ((CsEvt *)(evt->serial.evt.payload))->cmdcode);
		printf("Buffer addr: 0x%08X", (uint)evt);
		break;
	case TL_BLEEVT_CC_OPCODE:
		printf("MemMan evt released: 0x%02X; ", evt->serial.evt.code);
		printf("Cmd opcode: 0x%04X; ", ((CcEvt *)(evt->serial.evt.payload))->cmdcode);
		printf("Buffer addr: 0x%08X", (uint)evt);
		break;
	case TL_BLEEVT_VS_OPCODE:
		printf("MemMan evt released: 0x%02X; ", evt->serial.evt.code);
		printf("Subevtcode: 0x%04X; ", ((BleEvt *)(evt->serial.evt.payload))->code);
		printf("Buffer addr: 0x%08X", (uint)evt);
		break;
	default:
		printf("MemMan evt released: 0x%02X; ", evt->serial.evt.code);
		printf("Buffer addr: 0x%08X", (uint)evt);
		break;
	}
	printf("\r\n");
}
#endif // STACK_DEBUG

void TL::MemoryManager::init()
{
	List::initHead(&freeBufQueue);
	List::initHead(&localFreeBufQueue);
	
	refTable.memoryManager->blePool = evtPool;
	refTable.memoryManager->blePoolSize = poolSize;
	refTable.memoryManager->evtFreeBufQueue = (byte *)&freeBufQueue;
	refTable.memoryManager->bleBuf = bleSpareEvtBuffer;
	refTable.memoryManager->sysBuf = systemSpareEvtBuffer;
	IPCCm::setCallBack(callback, IPCCm::Direction::Tx, IPCC_CHANNEL_TRACE);
}

/******************************************************************************
 * TRACE
 ******************************************************************************/
void TL::Trace::eventCallback()
{
	while (!List::empty(&evtQueue))
	{
		EvtPacket *evt;
		List::removeHead(&evtQueue, (List::Node **)&evt);
	}
}

void TL::Trace::init()
{
	List::initHead(&evtQueue);
	refTable.trace->traceQueue = (byte *)&evtQueue;
	IPCCm::setCallBack(eventCallback, IPCCm::Direction::Rx, IPCC_CHANNEL_TRACE);
	IPCCm::expect(IPCCm::Direction::Rx, IPCC_CHANNEL_TRACE);
}