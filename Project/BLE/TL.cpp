#include "TL.h"
#include "IPCC.h"
#include "utilities.h"
#include "Debug.h"
#include "CPU2.h"
#include "Settings.h"
#include "stdio.h"
#include <cstring>

/******************************************************************************
 * GENERAL
 ******************************************************************************/
PLACE_IN_SECTION("MAPPING_TABLE") TL::RefTable	TL::refTable;
PLACE_IN_SECTION("MEM1") ALIGN(4) TL::Mailbox	TL::mailbox;

/******************************************************************************
 * SYSTEM
 ******************************************************************************/
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) TL::Packet TL::SHCI::packet;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) List::Node TL::SHCI::evtQueue;
PLACE_IN_SECTION("SYSTEM_DRIVER_CONTEXT") List::Node TL::SHCI::asynchEventQueue;
TaskHandle_t TL::SHCI::eventHandlerHandle;
void (* TL::SHCI::secondStage)();

/******************************************************************************
 * HCI
 ******************************************************************************/
PLACE_IN_SECTION("MB_MEM1") ALIGN(4) TL::Packet TL::HCI::packet;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) List::Node TL::HCI::evtQueue;
List::Node TL::HCI::cmdEventQueue;
PLACE_IN_SECTION("BLE_DRIVER_CONTEXT") List::Node TL::HCI::asynchEventQueue;
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) byte TL::HCI::csBuffer[sizeof(TL::PacketHeader) + TL_EVT_HDR_SIZE + sizeof(TL::CsEvt)];
const byte TL::HCI::configIRvalue[16] = CFG_BLE_IRK;   // Identity root key used to derive LTK and CSRK
const byte TL::HCI::configERvalue[16] = CFG_BLE_ERK;  // Encryption root key used to derive LTK and CSRK
TaskHandle_t TL::HCI::eventHandlerHandle;
byte TL::HCI::mac[6];
byte  TL::HCI::manufacturer[14] =
{
	sizeof(manufacturer) - 1,
	AD_TYPE_MANUFACTURER_SPECIFIC_DATA,
	0x01,// SKD version
	0x00,// Generic
	0x00,// GROUP A Feature
	0x00,// GROUP A Feature
	0x00,// GROUP B Feature
	0x00,// GROUP B Feature
	0x00,// BLE MAC start -MSB
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,// BLE MAC stop
};
PLACE_IN_SECTION("BLE_APP_CONTEXT") TL::HCI::BleApplicationContext_t TL::HCI::BleApplicationContext;
PLACE_IN_SECTION("BLE_DRIVER_CONTEXT") TL::HCI::Service::EvtHandler TL::HCI::Service::evtHandlerList;
PLACE_IN_SECTION("BLE_DRIVER_CONTEXT") TL::HCI::Service::CltHandler TL::HCI::Service::cltHandlerList;
PLACE_IN_SECTION("BLE_DRIVER_CONTEXT") TL::HCI::Service::DeviceInfoContext TL::HCI::Service::context;

/******************************************************************************
 * MEMORY MANAGER
 ******************************************************************************/
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) byte TL::MemoryManager::evtPool[TL::MemoryManager::poolSize];
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) byte TL::MemoryManager::systemSpareEvtBuffer[sizeof(TL::PacketHeader) + TL_EVT_HDR_SIZE + 255U];
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) byte TL::MemoryManager::bleSpareEvtBuffer[sizeof(TL::PacketHeader) + TL_EVT_HDR_SIZE + 255];
PLACE_IN_SECTION("MB_MEM1") ALIGN(4) List::Node  TL::MemoryManager::freeBufQueue;
List::Node TL::MemoryManager::localFreeBufQueue;

/******************************************************************************
 * TRACE
 ******************************************************************************/
PLACE_IN_SECTION("MB_MEM1") ALIGN(4) List::Node TL::Trace::evtQueue;

/******************************************************************************
 * GENERAL
 ******************************************************************************/
void TL::secondStageInit()
{
	CPU2::setup();
//	HCI::preinit();// Initialize Ble Transport Layer
	/**
	* Starts the BLE Stack on CPU2
	*/
	BleInitCmdPacket bleInitCmdPacket =
	{
		{ 0, 0, 0 },// Header unused
		{
			0,// pBleBufferAddress not used
			0,// BleBufferSize not used
			CFG_BLE_NUM_GATT_ATTRIBUTES,
			CFG_BLE_NUM_GATT_SERVICES,
			CFG_BLE_ATT_VALUE_ARRAY_SIZE,
			CFG_BLE_NUM_LINK,
			CFG_BLE_DATA_LENGTH_EXTENSION,
			CFG_BLE_PREPARE_WRITE_LIST_SIZE,
			CFG_BLE_MBLOCK_COUNT,
			CFG_BLE_MAX_ATT_MTU,
			CFG_BLE_SLAVE_SCA,
			CFG_BLE_MASTER_SCA,
			CFG_BLE_LSE_SOURCE,
			CFG_BLE_MAX_CONN_EVENT_LENGTH,
			CFG_BLE_HSE_STARTUP_TIME,
			CFG_BLE_VITERBI_MODE,
			CFG_BLE_LL_ONLY,
			0
		}
	};
	SHCI::send((ushort)SHCI::Opcode::C2_BLE_INIT, sizeof(BleInitCmdParam), (byte *)&bleInitCmdPacket.parameter, nullptr);
	HCI::init();
}

void TL::init(const Config *config)
{
	refTable.info = &mailbox.info;
	refTable.ble = &mailbox.ble;
	refTable.thread = &mailbox.thread;
	refTable.lldTests = &mailbox.lldTests;
	refTable.lldBle = &mailbox.lldBle;
	refTable.system = &mailbox.system;
	refTable.memoryManager = &mailbox.memManager;
	refTable.trace = &mailbox.traces;
	refTable.mac_802_15_4 = &mailbox.mac_802_15_4;
	refTable.zigbee = &mailbox.zigbee;
	IPCCm::init();
	SHCI::init(secondStageInit);
	MemoryManager::init();
	Trace::init();
	CPU2::enable();
}

/******************************************************************************
 * SYSTEM
 ******************************************************************************/
void TL::SHCI::commandTrace(Packet *cmd)
{
	printf("Sys cmd: 0x%04X;", cmd->serial.cmd.code);
	if (cmd->serial.cmd.length)
	{
		printf(" Payload: ");
		fflush(stdout);
		serial.sendBufHex(cmd->serial.cmd.payload, cmd->serial.cmd.length);
	}
}

void TL::SHCI::eventTrace(EvtPacket *evt)
{
	if (evt->serial.evt.evtcode == TL_BLEEVT_VS_OPCODE)
	{
		printf("Sys evt: 0x%02X;", evt->serial.evt.evtcode);
		printf(" Subevtcode: 0x%04X;", ((AsynchEvt *)(evt->serial.evt.payload))->subevtcode);
		if (evt->serial.evt.plen - 2)
		{
			printf(" Payload: ");
			fflush(stdout);
			serial.sendBufHex(((AsynchEvt *)(evt->serial.evt.payload))->payload, evt->serial.evt.plen - 2);
		}
	}
	else printf("Unknown sys evt received: %02X\n", evt->serial.evt.evtcode);
}

void TL::SHCI::responseTrace(EvtPacket *evt)
{
	if (evt->serial.evt.evtcode == TL_BLEEVT_CC_OPCODE)
	{
		printf("Sys rsp: 0x%02X; ", evt->serial.evt.evtcode);
		printf("Cmd opcode: 0x%02X; ", ((CcEvt *)(evt->serial.evt.payload))->cmdcode);
		printf("Status: 0x%02X;", ((CcEvt *)(evt->serial.evt.payload))->payload[0]);
		if (evt->serial.evt.plen - 4)
		{
			serial.sendLine(" Payload: ");
			fflush(stdout);
			serial.sendBufHex(&((CcEvt *)(evt->serial.evt.payload))->payload[1], evt->serial.evt.plen - 4);
		}
	}
	else printf("Unknown sys rsp received: %02X\n", evt->serial.evt.evtcode);
}

void TL::SHCI::eventHandler(void *args)
{
	if (!List::empty(&asynchEventQueue))
	{
		EvtPacket *evt;
		List::removeHead(&asynchEventQueue, (List::Node **)&evt);
		eventTrace(evt);
		secondStage();
		MemoryManager::evtDone(evt);
		vTaskDelete(nullptr);
	}
}

void TL::SHCI::cmdEventCallback()
{

}

void TL::SHCI::eventCallback()
{
	while (!List::empty(&evtQueue))
	{
		EvtPacket *evt;
		List::removeHead(&evtQueue, (List::Node **)&evt);
		List::insertTail(&asynchEventQueue, (List::Node *)evt);
		portYIELD_FROM_ISR(xTaskResumeFromISR(eventHandlerHandle));
	}
}

void TL::SHCI::send(ushort cmdCode, byte length, byte * payload, EvtPacket * evt)
{
	packet.serial.cmd.code = cmdCode;
	packet.serial.cmd.length = length;
	memcpy(packet.serial.cmd.payload, payload, length);
	packet.serial.type = (byte)PacketType::SYSCMD;
	commandTrace(&packet);
	IPCCm::occupy(IPCC_CHANNEL_SYSTEM, true);
	ulTaskNotifyTake(1, portMAX_DELAY);
	if (evt)
	{
		memcpy(&(evt->serial), &packet, ((EvtSerial *)&packet)->evt.plen + TL_EVT_HDR_SIZE);
		responseTrace(evt);	
	}
}

void TL::SHCI::init(void (* _secondStage)())
{
	xTaskCreate(eventHandler, "SHCI::eventHandler", configMINIMAL_STACK_SIZE, nullptr, FREERTOS_PRIORITY_BLE, &eventHandlerHandle);
	vTaskSuspend(eventHandlerHandle);
	secondStage = _secondStage;
	List::initHead(&evtQueue);
	List::initHead(&asynchEventQueue);
	refTable.system->pcmd_buffer = (byte *)&packet;
	refTable.system->sys_queue = (byte *)&evtQueue;
	IPCCm::setCallBack(eventCallback, IPCCm::Direction::Rx, IPCC_CHANNEL_SYSTEM);
	IPCCm::setCallBack(cmdEventCallback, IPCCm::Direction::Tx, IPCC_CHANNEL_SYSTEM);
	IPCCm::expect(IPCCm::Direction::Rx, IPCC_CHANNEL_SYSTEM);
}

/******************************************************************************
 * HCI
 ******************************************************************************/
void TL::HCI::eventHandler(void *args)
{
	//	TL_EvtPacket_t *phcievtbuffer;
	//	tHCI_UserEvtRxParam UserEvtRxParam;
	//
	//	if ((LST_is_empty(&HciAsynchEventQueue) == FALSE) && (UserEventFlow != HCI_TL_UserEventFlow_Disable))
	//	{
	//		LST_remove_head(&HciAsynchEventQueue, (tListNode **)&phcievtbuffer);
	//
	//		OutputEvtTrace(phcievtbuffer);
	//
	//		if (hciContext.UserEvtRx != NULL)
	//		{
	//			UserEvtRxParam.pckt = phcievtbuffer;
	//			UserEvtRxParam.status = HCI_TL_UserEventFlow_Enable;
	//			hciContext.UserEvtRx((void *)&UserEvtRxParam);
	//			UserEventFlow = UserEvtRxParam.status;
	//		}
	//		else
	//		{
	//			UserEventFlow = HCI_TL_UserEventFlow_Enable;
	//		}
	//
	//		if (UserEventFlow != HCI_TL_UserEventFlow_Disable)
	//		{
	//			TL_MM_EvtDone(phcievtbuffer);
	//		}
	//		else
	//		{
	//			/**
	//			 * put back the event in the queue
	//			 */
	//			LST_insert_head(&HciAsynchEventQueue, (tListNode *)phcievtbuffer);
	//		}
	//	}
	//
	//	if ((LST_is_empty(&HciAsynchEventQueue) == FALSE) && (UserEventFlow != HCI_TL_UserEventFlow_Disable))
	//	{
	//		hci_notify_asynch_evt((void*) &HciAsynchEventQueue);
	//	}
}

void TL::HCI::eventCallback()
{
	while (!List::empty(&evtQueue))
	{
		EvtPacket *evt;
		List::removeHead(&evtQueue, (List::Node **) &evt);
		if (evt->serial.evt.evtcode == TL_BLEEVT_CS_OPCODE || evt->serial.evt.evtcode == TL_BLEEVT_CC_OPCODE)
		{
			List::insertTail(&cmdEventQueue, (List::Node *)evt);
//			UTIL_SEQ_SetEvt(1 << CFG_IDLEEVT_HCI_CMD_EVT_RSP_ID);;// Notify the application a full Cmd Event has been received
			//CFG_IDLEEVT_HCI_CMD_EVT_RSP_ID = 0
		}
		else
		{
			List::insertTail(&asynchEventQueue, (List::Node *)evt);
			portYIELD_FROM_ISR(xTaskResumeFromISR(eventHandlerHandle));
		}
	}
}

void TL::HCI::sendCommand(Opcode opcode, byte plen, void *param)
{
	
}

int TL::HCI::sendRequest(Request *p_cmd, bool async)
{
	
}

TL::HCI::Status TL::HCI::ACI::sendReqPrepare(byte *cmd, ushort ogf, ushort ocf, int clen)
{
	Status status = Status::Success;
	Request rq = { ogf, ocf, 0, cmd, clen, &status, 1};
	if (sendRequest(&rq) < 0) return Status::Timeout;
	return status;
}

TL::HCI::Status TL::HCI::ACI::gapConfigureWhitelist()
{
	return sendReqPrepare(nullptr, 0x3F, 0x92, 1);
}

TL::HCI::Status TL::HCI::ACI::gapSetAuthenticationRequirement(	byte Bonding_Mode, byte MITM_Mode, byte SC_Support, byte KeyPress_Notification_Support, byte Min_Encryption_Key_Size, 
																byte Max_Encryption_Key_Size, byte Use_Fixed_Pin, uint Fixed_Pin, byte Identity_Address_Type)
{
	uint8_t cmd[BLE_CMD_MAX_PARAM_LEN];
	GapSetAuthenticationRequirementCP *cp0 = (GapSetAuthenticationRequirementCP *)(cmd);
	cp0->Bonding_Mode = Bonding_Mode;
	cp0->MITM_Mode = MITM_Mode;
	cp0->SC_Support = SC_Support;
	cp0->KeyPress_Notification_Support = KeyPress_Notification_Support;
	cp0->Min_Encryption_Key_Size = Min_Encryption_Key_Size;
	cp0->Max_Encryption_Key_Size = Max_Encryption_Key_Size;
	cp0->Use_Fixed_Pin = Use_Fixed_Pin;
	cp0->Fixed_Pin = Fixed_Pin;
	cp0->Identity_Address_Type = Identity_Address_Type;
	return sendReqPrepare(cmd, 0x3F, 0x86, 12);
}

TL::HCI::Status TL::HCI::ACI::gapSetIOcapability(byte IO_Capability)
{
	byte cmd[BLE_CMD_MAX_PARAM_LEN];
	cmd[0] = IO_Capability;
	return sendReqPrepare(cmd, 0x3F, 0x85, 1);
}

TL::HCI::Status TL::HCI::ACI::gattUpdateCharValue(ushort Service_Handle, ushort Char_Handle, byte Val_Offset, byte Char_Value_Length, byte Char_Value[])
{
	byte cmd[BLE_CMD_MAX_PARAM_LEN];
	GattUpdateCharValueCP *cp0 = (GattUpdateCharValueCP *)(cmd);
	cp0->Service_Handle = Service_Handle;
	cp0->Char_Handle = Char_Handle;
	cp0->Val_Offset = Val_Offset;
	cp0->Char_Value_Length = Char_Value_Length;
	memcpy(&cp0->Char_Value, Char_Value, Char_Value_Length);
	return sendReqPrepare(cmd, 0x3F, 0x106, Char_Value_Length + 6);
}

TL::HCI::Status TL::HCI::ACI::gapInit(byte role, bool privacy, byte device_name_char_len, ushort *Service_Handle, ushort *Dev_Name_Char_Handle, ushort *Appearance_Char_Handle)
{
	byte cmd[BLE_CMD_MAX_PARAM_LEN];
	GapInitCP *cp0 = (GapInitCP *)(cmd);
	cp0->Role = role;
	cp0->privacy_enabled = privacy;
	cp0->device_name_char_len = device_name_char_len;
	GapInitRP resp = { };
	Request rq = { };
	rq.ogf = 0x3F;
	rq.ocf = 0x8A;
	rq.cparam = cmd;
	rq.clen = 3;
	rq.rparam = &resp;
	rq.rlen = sizeof(resp);
	if (sendRequest(&rq) < 0) return Status::Timeout;
	if (resp.status == Status::Success)
	{
		*Service_Handle = resp.Service_Handle;
		*Dev_Name_Char_Handle = resp.Dev_Name_Char_Handle;
		*Appearance_Char_Handle = resp.Appearance_Char_Handle;
	}
	return resp.status;
}

TL::HCI::Status TL::HCI::ACI::gattInit()
{
	return ACI::sendReqPrepare(nullptr, 0x3F, 0x101, 0);
}

TL::HCI::Status TL::HCI::ACI::setTxPower(Power power, bool highPowerEn)
{
	byte cmd[BLE_CMD_MAX_PARAM_LEN];
	setTxPowerCP *cp0 = (setTxPowerCP *)cmd;
	cp0->highPowerEn = highPowerEn;
	cp0->power = (byte)power;
	return sendReqPrepare(cmd, 0x3F, 0x0F, 2);
}

TL::HCI::Status TL::HCI::ACI::writeConfigData(byte Offset, byte Length, byte Value[])
{
	byte cmd[BLE_CMD_MAX_PARAM_LEN];
	WriteConfigDataCP *cp0 = (WriteConfigDataCP *)cmd;
	cp0->Offset = Offset;
	cp0->Length = Length;
	memcpy(&cp0->Value, Value, Length);
	return sendReqPrepare(cmd, 0x3F, 0x0C, Length + 2);
}

void TL::HCI::Service::thread()
{
	Event evt;
	for (byte i = 0; i < evtHandlerList.count; i++) evtHandlerList.ptr[i](&evt);
}

void TL::HCI::Service::addService(EvtAckStatus(* evtHandler)(Event *))
{
	if (evtHandlerList.count < BLE_CFG_SVCCTL_MAX) evtHandlerList.ptr[evtHandlerList.count++] = evtHandler;
}

void TL::HCI::Service::init()
{
	evtHandlerList.count = 0;
	cltHandlerList.count = 0;
}

TL::HCI::Status TL::HCI::setDefaultPhy(byte ALL_PHYS, byte TX_PHYS, byte RX_PHYS)
{
	byte cmd[BLE_CMD_MAX_PARAM_LEN];
	SetDefaultPhyCP *cp0 = (SetDefaultPhyCP *)(cmd);
	cp0->ALL_PHYS = ALL_PHYS;
	cp0->TX_PHYS = TX_PHYS;
	cp0->RX_PHYS = RX_PHYS;
	return ACI::sendReqPrepare(cmd, 0x08, 0x31, 3);
}

void TL::HCI::initMac(byte *buf)
{
	for (byte i = 0; i < 6; i++) mac[i] = buf[i];
}

TL::HCI::Status TL::HCI::reset()
{
	return ACI::sendReqPrepare(nullptr, 0x03, 0x03, 0);
}

void TL::HCI::init(byte *_mac, byte *_sra)
{
	xTaskCreate(eventHandler, "HCI::eventHandler", configMINIMAL_STACK_SIZE, nullptr, FREERTOS_PRIORITY_BLE, &eventHandlerHandle);
	vTaskSuspend(eventHandlerHandle);
	List::initHead(&evtQueue);
	List::initHead(&cmdEventQueue);
	List::initHead(&asynchEventQueue);
	refTable.ble->pcmd_buffer = (byte *)&packet;
	refTable.ble->pcs_buffer = csBuffer;
	refTable.ble->pevt_queue = (byte *)&evtQueue;
	IPCCm::setCallBack(eventCallback, IPCCm::Direction::Rx, IPCC_CHANNEL_BLE);
	IPCCm::expect(IPCCm::Direction::Rx, IPCC_CHANNEL_BLE);
	
	/**
	* Initialization of HCI & GATT & GAP layer
	*/
	reset();
	if (_mac) initMac(_mac);
	else
	{
		if (*((uint *)UID64_BASE) != 0xFFFFFFFF) initMac((byte *)UID64_BASE);
		else
		{
			static const byte temp[6] = { 0, 1, 2, 3, 4, 5 };
			initMac((byte *)temp);
		}
	}
	ACI::writeConfigData(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN, (byte *) mac);
	for (byte i = 0; i < 6; i++) manufacturer[sizeof(manufacturer) - i - 1] = mac[i];// BLE MAC in ADV Packet
	
	ACI::writeConfigData(CONFIG_DATA_IR_OFFSET, CONFIG_DATA_IR_LEN, (byte *)configIRvalue);// Write Identity root key used to derive LTK and CSRK
	ACI::writeConfigData(CONFIG_DATA_ER_OFFSET, CONFIG_DATA_ER_LEN, (byte *)configERvalue);// Write Encryption root key used to derive LTK and CSRK
	
	if (_sra) ACI::writeConfigData(CONFIG_DATA_RANDOM_ADDRESS_OFFSET, CONFIG_DATA_RANDOM_ADDRESS_LEN, _sra);// Static random Address; The two upper bits shall be set to 1
	else
	{
		uint sra[2] = { *((uint *)UID64_BASE), 0xED6E };// The lowest 32bits is read from the UDN to differentiate between devices
		ACI::writeConfigData(CONFIG_DATA_RANDOM_ADDRESS_OFFSET, CONFIG_DATA_RANDOM_ADDRESS_LEN, (byte *)sra);
	}
	
	ACI::writeConfigData(CONFIG_DATA_IR_OFFSET, CONFIG_DATA_IR_LEN, (byte*)configIRvalue);// Write Identity root key used to derive LTK and CSRK
	ACI::writeConfigData(CONFIG_DATA_ER_OFFSET, CONFIG_DATA_ER_LEN, (byte *)configERvalue);// Write Encryption root key used to derive LTK and CSRK
	
	ACI::setTxPower(ACI::Power::_0dBm, true);
	
	/**
	* Initialize GATT interface
	*/
	ACI::gattInit();
	/**
	* Initialize GAP interface
	*/
	byte role = GAP_PERIPHERAL_ROLE;
	const char *name = "HRSTM";
	ushort gap_service_handle, gap_dev_name_char_handle, gap_appearance_char_handle;
	ushort appearance[1] = { BLE_CFG_GAP_APPEARANCE };
	ACI::gapInit(role, false, 7, &gap_service_handle, &gap_dev_name_char_handle, &gap_appearance_char_handle);	
	if (ACI::gattUpdateCharValue(gap_service_handle, gap_dev_name_char_handle, 0, strlen(name), (byte *) name) != TL::HCI::Status::Success) printf("Device Name ACI::gattUpdateCharValue failed.\n");
	if (ACI::gattUpdateCharValue(gap_service_handle, gap_appearance_char_handle, 0, 2, (byte *)&appearance) != TL::HCI::Status::Success) printf("Appearance ACI::gattUpdateCharValue failed.\n");
	/**
	* Initialize Default PHY
	*/
	setDefaultPhy(ALL_PHYS_PREFERENCE, TX_2M_PREFERRED, RX_2M_PREFERRED);
	/**
	* Initialize IO capability
	*/
	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.ioCapability = CFG_IO_CAPABILITY;
	ACI::gapSetIOcapability(BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.ioCapability);
	/**
	* Initialize authentication
	*/
	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.mitm_mode = CFG_MITM_PROTECTION;
	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.OOB_Data_Present = 0;
	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.encryptionKeySizeMin = CFG_ENCRYPTION_KEY_SIZE_MIN;
	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.encryptionKeySizeMax = CFG_ENCRYPTION_KEY_SIZE_MAX;
	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.Use_Fixed_Pin = CFG_USED_FIXED_PIN;
	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.Fixed_Pin = CFG_FIXED_PIN;
	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.bonding_mode = CFG_BONDING_MODE;
	for (byte index = 0; index < 16; index++) BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.OOB_Data[index] = index;
	
	ACI::gapSetAuthenticationRequirement(	BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.bonding_mode,
											BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.mitm_mode,
											CFG_SC_SUPPORT,
											CFG_KEYPRESS_NOTIFICATION_SUPPORT,
											BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.encryptionKeySizeMin,
											BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.encryptionKeySizeMax,
											BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.Use_Fixed_Pin,
											BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.Fixed_Pin,
											PUBLIC_ADDR);
	/**
	* Initialize whitelist
	*/
	if (BleApplicationContext.BleApplicationContext_legacy.bleSecurityParam.bonding_mode) ACI::gapConfigureWhitelist();
	
	Service::init();
}

//void TL::HCI::preinit()
//{
	
	// BLE_UserEvtRx
//	static void BLE_UserEvtRx(void * pPayload)
//	{
//	SVCCTL_UserEvtFlowStatus_t svctl_return_status;
//	tHCI_UserEvtRxParam *pParam;
//
//	pParam = (tHCI_UserEvtRxParam *)pPayload; 
//
//	svctl_return_status = SVCCTL_UserEvtRx((void *)&(pParam->pckt->evtserial));
//	if (svctl_return_status != SVCCTL_UserEvtFlowDisable)
//	{
//		pParam->status = HCI_TL_UserEventFlow_Enable;
//	}
//	else
//	{
//		pParam->status = HCI_TL_UserEventFlow_Disable;
//	}
	// BLE_UserEvtRx

//	xTaskCreate(eventHandler, "eventHandler", configMINIMAL_STACK_SIZE, nullptr, FREERTOS_PRIORITY_BLE, &eventHandlerHandle);
//	vTaskSuspend(eventHandlerHandle);
//	secondStage = _secondStage;
	
//	refTable.system->sys_queue = (byte *)&evtQueue;
//}

/******************************************************************************
 * MEMORY MANAGER
 ******************************************************************************/
void TL::MemoryManager::sendFreeBuf()
{
	List::Node *node;
	while (!List::empty(&localFreeBufQueue))
	{
		List::removeHead(&localFreeBufQueue, (List::Node **)&node);
		List::insertTail((List::Node *)(refTable.memoryManager->pevt_free_buffer_queue), node);
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
	trace(evt);
	if (IPCCm::pending(IPCCm::Direction::Tx, IPCC_CHANNEL_TRACE)) IPCCm::expect(IPCCm::Direction::Tx, IPCC_CHANNEL_TRACE);
	else
	{
		sendFreeBuf();
		IPCCm::occupy(IPCC_CHANNEL_TRACE);
	}
}

void TL::MemoryManager::trace(EvtPacket * evt)
{
	switch (evt->serial.evt.evtcode)
	{
	case TL_BLEEVT_CS_OPCODE:
		printf("MemMan evt released: 0x%02X; ", evt->serial.evt.evtcode);
		printf("Cmd opcode: 0x%04X; ", ((CsEvt *)(evt->serial.evt.payload))->cmdcode);
		printf("Buffer addr: 0x%08X", (uint)evt);
		break;
	case TL_BLEEVT_CC_OPCODE:
		printf("MemMan evt released: 0x%02X; ", evt->serial.evt.evtcode);
		printf("Cmd opcode: 0x%04X; ", ((CcEvt *)(evt->serial.evt.payload))->cmdcode);
		printf("Buffer addr: 0x%08X", (uint)evt);
		break;
	case TL_BLEEVT_VS_OPCODE:
		printf("MemMan evt released: 0x%02X; ", evt->serial.evt.evtcode);
		printf("Subevtcode: 0x%04X; ", ((AsynchEvt *)(evt->serial.evt.payload))->subevtcode);
		printf("Buffer addr: 0x%08X", (uint)evt);
		break;
	default:
		printf("MemMan evt released: 0x%02X; ", evt->serial.evt.evtcode);
		printf("Buffer addr: 0x%08X", (uint)evt);
		break;
	}
	printf("\r\n");
}

void TL::MemoryManager::init()
{
	List::initHead(&freeBufQueue);
	List::initHead(&localFreeBufQueue);
	
	refTable.memoryManager->blepool = evtPool;
	refTable.memoryManager->blepoolsize = poolSize;
	refTable.memoryManager->pevt_free_buffer_queue = (byte *)&freeBufQueue;
	refTable.memoryManager->spare_ble_buffer = bleSpareEvtBuffer;
	refTable.memoryManager->spare_sys_buffer = systemSpareEvtBuffer;
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
	refTable.trace->traces_queue = (byte *)&evtQueue;
	IPCCm::setCallBack(eventCallback, IPCCm::Direction::Rx, IPCC_CHANNEL_TRACE);
	IPCCm::expect(IPCCm::Direction::Rx, IPCC_CHANNEL_TRACE);
}