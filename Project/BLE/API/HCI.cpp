#include "HCI.hpp"
#include "utilities.h"
#include "stdio.h"
#include "string.h"
#include "IPCC.hpp"
#include "algorithm"
#include "Service.hpp"
#include "FreeRTOS.h"
#include "task.h"
#ifdef STACK_DEBUG
#include "Debug.hpp"
#endif // STACK_DEBUG

PLACE_IN_SECTION("MB_MEM1") ALIGN(4) TL::CmdPacket HCI::packet;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) List::Node HCI::evtQueue;
List::Node HCI::cmdEventQueue;
List::Node HCI::asynchEventQueue;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) byte HCI::csBuffer[sizeof(TL::PacketHeader) + TL_EVT_HDR_SIZE + sizeof(TL::CsEvt)];
TaskHandle_t HCI::thread;
TaskHandle_t HCI::eventHandlerHandle;

#ifdef STACK_DEBUG
void HCI::commandTrace(TL::CmdPacket *pack)
{
	printf("Ble cmd: 0x%04X;", pack->serial.cmd.code);
	if (pack->serial.cmd.length)
	{
		printf(" Payload: ");
		fflush(stdout);
		serial.sendBufHex(pack->serial.cmd.payload, pack->serial.cmd.length);
	}
	else printf("\n");
}

void HCI::eventTrace(TL::EvtPacket *evt)
{
	printf("Ble evt: 0x%02X;", evt->serial.evt.code);
	if (evt->serial.evt.code == TL_BLEEVT_VS_OPCODE)
	{
		printf(" Subevtcode: 0x%04X;", ((TL::BleEvt *)(evt->serial.evt.payload))->code);
		if (evt->serial.evt.length > 2)
		{
			printf(" Payload: ");
			fflush(stdout);
			serial.sendBufHex(((TL::BleEvt *)(evt->serial.evt.payload))->payload, evt->serial.evt.length - 2);
		}
		else printf("\n");
	}
	else
	{
		if (evt->serial.evt.length)
		{
			printf(" Payload: ");
			fflush(stdout);
			serial.sendBufHex(evt->serial.evt.payload, evt->serial.evt.length);
		}
		else printf("\n");
	}
}

void HCI::responseTrace(TL::EvtPacket *evt)
{
	if (evt->serial.evt.code == TL_BLEEVT_CC_OPCODE || evt->serial.evt.code == TL_BLEEVT_CS_OPCODE)
	{
		printf("Ble rsp: 0x%02X; ", evt->serial.evt.code);
		TL::CcEvt * cEvt = ((TL::CcEvt *)(evt->serial.evt.payload));
		TL::CsEvt * sEvt = ((TL::CsEvt *)(evt->serial.evt.payload));
		printf("Cmd opcode: 0x%04X; ", evt->serial.evt.code == TL_BLEEVT_CC_OPCODE ? cEvt->cmdcode	: sEvt->cmdcode);
		printf("numHCI: 0x%02X; ", evt->serial.evt.code == TL_BLEEVT_CC_OPCODE ? cEvt->numcmd		: sEvt->numcmd);
		printf("Status: 0x%02X;", evt->serial.evt.code == TL_BLEEVT_CC_OPCODE ? cEvt->payload[0]	: sEvt->status);
		if (evt->serial.evt.code == TL_BLEEVT_CC_OPCODE)
		{
			if (evt->serial.evt.length > 4)
			{
				printf(" Payload: ");
				fflush(stdout);
				serial.sendBufHex(&cEvt->payload[1], evt->serial.evt.length - 4);
			}
			else printf("\n");
		}
		else printf("\n");
	}
	else printf("Unknown Ble rsp received: %02X\n", evt->serial.evt.code);
}
#endif // STACK_DEBUG

void HCI::eventHandler(void *args)
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
			Service::eventReceived(&evt->serial.evt);
			TL::MemoryManager::evtDone(evt);
		}
		else vTaskSuspend(nullptr);	
	}
}

void HCI::eventCallback()
{
	while (!List::empty(&evtQueue))
	{
		TL::EvtPacket *evt;
		List::removeHead(&evtQueue, (List::Node **) &evt);
		if (evt->serial.evt.code == TL_BLEEVT_CS_OPCODE || evt->serial.evt.code == TL_BLEEVT_CC_OPCODE)
		{
			List::insertTail(&cmdEventQueue, (List::Node *)evt);
			BaseType_t xHigherPriorityTaskWoken = pdFALSE;
			vTaskNotifyGiveFromISR(thread, &xHigherPriorityTaskWoken);
			portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
		}
		else
		{
			List::insertTail(&asynchEventQueue, (List::Node *)evt);
			portYIELD_FROM_ISR(xTaskResumeFromISR(eventHandlerHandle));
		}
	}
}

void HCI::send(ushort opcode, Request * request, byte length, byte * payload)
{
	packet.serial.cmd.code = opcode;
	packet.serial.type = (byte)TL::PacketType::BLECMD;
	packet.serial.cmd.length = length;
	memcpy(packet.serial.cmd.payload, payload, length);
#ifdef STACK_DEBUG
	commandTrace(&packet);
#endif // STACK_DEBUG
	thread = xTaskGetCurrentTaskHandle();
	IPCCm::occupy(IPCC_CHANNEL_BLE, false);
	
	while (true)// while command status is Busy
	{
		ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
		while (!List::empty(&cmdEventQueue))
		{
			TL::EvtPacket *evt;
			List::removeHead(&cmdEventQueue, (List::Node **)&evt);
#ifdef STACK_DEBUG
			responseTrace(evt);
#endif // STACK_DEBUG
			if (evt->serial.evt.code == TL_BLEEVT_CS_OPCODE)
			{
				TL::CsEvt *commandStatusEvt = (TL::CsEvt*)evt->serial.evt.payload;
				if (commandStatusEvt->cmdcode == opcode) *(byte *)request->parameter = commandStatusEvt->status;
				if (commandStatusEvt->numcmd) return;
			}
			else
			{
				TL::CcEvt *commandCompleteEvt = (TL::CcEvt*)evt->serial.evt.payload;
				if (request && commandCompleteEvt->cmdcode == opcode) memcpy(request->parameter, commandCompleteEvt->payload, std::min((uint)evt->serial.evt.length - TL_EVT_HDR_SIZE, request->length));
				if (commandCompleteEvt->numcmd) return;
			}
		}
	}
}

void HCI::init(void(* nextStage)(), TaskHandle_t thread)
{
	xTaskCreate(eventHandler, "HCI::eventHandler", configMINIMAL_STACK_SIZE * 2, nullptr, BLE_FREERTOS_THREAD_PRIORITY, &eventHandlerHandle);
	vTaskSuspend(eventHandlerHandle);
	List::initHead(&evtQueue);
	List::initHead(&cmdEventQueue);
	List::initHead(&asynchEventQueue);
	TL::setHCIBuffer(packet, csBuffer, evtQueue);
	IPCCm::setCallBack(eventCallback, IPCCm::Direction::Rx, IPCC_CHANNEL_BLE);
	IPCCm::expect(IPCCm::Direction::Rx, IPCC_CHANNEL_BLE);
	HCI::thread = thread;
	nextStage();
}