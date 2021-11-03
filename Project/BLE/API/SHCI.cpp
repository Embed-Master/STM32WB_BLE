#include "SHCI.hpp"
#include "utilities.h"
#include "stdio.h"
#include "string.h"
#include "IPCC.hpp"

PLACE_IN_SECTION("MB_MEM2") ALIGN(4) TL::CmdPacket SHCI::packet;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) List::Node SHCI::evtQueue;
List::Node SHCI::asynchEventQueue;
TaskHandle_t SHCI::eventHandlerHandle;
void (*SHCI::callback)(TaskHandle_t);

#ifdef STACK_DEBUG
void SHCI::commandTrace(TL::CmdPacket *cmd)
{
	printf("Sys cmd: 0x%04X;", cmd->serial.cmd.code);
	if (cmd->serial.cmd.length)
	{
		printf(" Payload: \n");
		for (ushort i = 0; i < cmd->serial.cmd.length; i++) printf(" %02X", *((byte*)(cmd->serial.cmd.payload + i)));
		fflush(stdout);
	}
	else printf("\n");
}

void SHCI::eventTrace(TL::EvtPacket *evt)
{
	if (evt->serial.evt.code == TL_BLEEVT_VS_OPCODE)
	{
		printf("Sys evt: 0x%02X;", evt->serial.evt.code);
		printf(" Subevtcode: 0x%04X;", ((TL::BleEvt *)(evt->serial.evt.payload))->code);
		if (evt->serial.evt.length > 2)
		{
			printf(" Payload: \n");
			for (ushort i = 0; i < evt->serial.evt.length - 2; i++) printf(" %02X", *((byte*)(((TL::BleEvt*)(evt->serial.evt.payload))->payload + i)));
			fflush(stdout);
		}
		else printf("\n");
	}
	else printf("Unknown sys evt received: %02X\n", evt->serial.evt.code);
}

void SHCI::responseTrace(TL::EvtPacket *evt)
{
	if (evt->serial.evt.code == TL_BLEEVT_CC_OPCODE)
	{
		printf("Sys rsp: 0x%02X; ", evt->serial.evt.code);
		printf("Cmd opcode: 0x%04X; ", ((TL::CcEvt *)(evt->serial.evt.payload))->cmdcode);
		printf("Status: 0x%02X;", ((TL::CcEvt *)(evt->serial.evt.payload))->payload[0]);
		if (evt->serial.evt.length > 4)
		{
			printf(" Payload: \n");
			for (ushort i = 0; i < evt->serial.evt.length - 4; i++) printf(" %02X", *((byte*)(((TL::CcEvt*)(evt->serial.evt.payload))->payload + 1 + i)));
			fflush(stdout);
		}
		else printf("\n");
	}
	else printf("Unknown Sys rsp received: %02X\n", evt->serial.evt.code);
}
#endif // STACK_DEBUG

void SHCI::eventHandler(void *args)
{
	while (true)
	{
		if (!List::empty(&asynchEventQueue))
		{
			TL::EvtPacket *evt;
			List::removeHead(&asynchEventQueue, (List::Node **)&evt);
#ifdef STACK_DEBUG
			eventTrace(evt);
#endif // STACK_DEBUG
			callback(eventHandlerHandle);
			TL::MemoryManager::evtDone(evt);
		}
		else vTaskDelete(nullptr);
	}
}

void SHCI::eventCallback()
{
	while (!List::empty(&evtQueue))
	{
		TL::EvtPacket *evt;
		List::removeHead(&evtQueue, (List::Node **)&evt);
		List::insertTail(&asynchEventQueue, (List::Node *)evt);
		portYIELD_FROM_ISR(xTaskResumeFromISR(eventHandlerHandle));
	}
}

void SHCI::cmdResponse()
{
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	vTaskNotifyGiveFromISR(eventHandlerHandle, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void SHCI::send(Opcode opcode, byte length, byte * payload, TL::EvtPacket * evt)
{
	packet.serial.cmd.code = (ushort)opcode;
	packet.serial.cmd.length = length;
	packet.serial.type = (byte)TL::PacketType::SYSCMD;
	memcpy(packet.serial.cmd.payload, payload, length);
#ifdef STACK_DEBUG
	commandTrace(&packet);
#endif // STACK_DEBUG
	IPCCm::occupy(IPCC_CHANNEL_SYSTEM, true);
	ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
	if (evt)
	{
		memcpy(&(evt->serial), &packet, ((TL::EvtSerial *)&packet)->evt.length + TL_EVT_HDR_SIZE);
#ifdef STACK_DEBUG
		responseTrace(evt);
#endif // STACK_DEBUG
	}
}

void SHCI::init(void (*callback)(TaskHandle_t))
{
	xTaskCreate(eventHandler, "SHCI::eventHandler", configMINIMAL_STACK_SIZE * 4, nullptr, BLE_FREERTOS_THREAD_PRIORITY, &eventHandlerHandle);
	vTaskSuspend(eventHandlerHandle);
	SHCI::callback = callback;
	List::initHead(&evtQueue);
	List::initHead(&asynchEventQueue);
	TL::setSHCIBuffer(packet, evtQueue);
	IPCCm::setCallBack(eventCallback, IPCCm::Direction::Rx, IPCC_CHANNEL_SYSTEM);
	IPCCm::setCallBack(cmdResponse, IPCCm::Direction::Tx, IPCC_CHANNEL_SYSTEM);
	IPCCm::expect(IPCCm::Direction::Rx, IPCC_CHANNEL_SYSTEM);
}