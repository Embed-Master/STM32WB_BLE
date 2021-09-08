#include "BLE.hpp"
#include "CoreSettings.h"
#include "CPU2.hpp"
#include "StackConfig.hpp"
#include "SHCI.hpp"
#include "LE.hpp"
#include "HAL.hpp"
#include "GATT.hpp"
#include "GAP.hpp"
#include "string.h"
#include "utilities.h"
#include "Service.hpp"
#include "DIS.hpp"
#include "legacy.h"
#include "uuid.h"
#include "stdio.h"
#include "P2P.hpp"

BLE::Settings BLE::settings;
BLE::Status BLE::status;
byte BLE::manufacturer[14] =
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
const byte BLE::configIRvalue[16] = CFG_BLE_IRK;// Identity root key used to derive LTK and CSRK
const byte BLE::configERvalue[16] = CFG_BLE_ERK;// Encryption root key used to derive LTK and CSRK
BLE::Context BLE::context;

struct hci_le_phy_update_complete_event_rp0
{
	byte Status;
	ushort Connection_Handle;
	byte TX_PHY;
	byte RX_PHY;
} __attribute__((packed));

struct hci_disconnection_complete_event_rp0
{
	byte Status;
	ushort Connection_Handle;
	byte Reason;
} __attribute__((packed));

struct hci_le_connection_complete_event_rp0
{
	byte Status;
	ushort Connection_Handle;
	byte Role;
	byte Peer_Address_Type;
	byte Peer_Address[6];
	ushort Conn_Interval;
	ushort Conn_Latency;
	ushort Supervision_Timeout;
	byte Master_Clock_Accuracy;
} __attribute__((packed));

struct aci_gap_pairing_complete_event_rp0
{
	ushort Connection_Handle;
	byte Status;
	byte Reason;
} __attribute__((packed));

struct aci_gap_numeric_comparison_value_event_rp0
{
	ushort Connection_Handle;
	uint Numeric_Value;
} __attribute__((packed));

void BLE::appNotification(TL::Event *evt)
{
	HCI::Status ret = HCI::Status::InvalidParams;
	switch (evt->code)
	{
	case EVT_DISCONN_COMPLETE:
		{
			hci_disconnection_complete_event_rp0 *disconnection_complete_event = (hci_disconnection_complete_event_rp0 *) evt->payload;
			if (disconnection_complete_event->Connection_Handle == context.settings.handle)
			{
				context.settings.handle = 0;
				context.connection = Connection::Idle;
#ifdef STACK_DEBUG
				printf("DISCONNECTION EVENT WITH CLIENT\n");
#endif // STACK_DEBUG
			}
			advRequest(Connection::FastAdvertasing, settings.name, 0, nullptr);// restart advertising
		}
		break;
	case EVT_LE_META_EVENT:
		{
			TL::Data *meta_evt = (TL::Data *) evt->payload;
			switch (meta_evt->type)
			{
			case EVT_LE_CONN_UPDATE_COMPLETE:
#ifdef STACK_DEBUG
				printf("CONNECTION UPDATE EVENT WITH CLIENT\n");
#endif // STACK_DEBUG
				break;
			case EVT_LE_PHY_UPDATE_COMPLETE:
				{
					hci_le_phy_update_complete_event_rp0 *evt_le_phy_update_complete = (hci_le_phy_update_complete_event_rp0*)meta_evt->data;
#ifdef STACK_DEBUG
					printf("EVT_UPDATE_PHY_COMPLETE\n");
					if (evt_le_phy_update_complete->Status) printf("EVT_UPDATE_PHY_COMPLETE, status nok\n"); 
					else printf("EVT_UPDATE_PHY_COMPLETE, status ok\n");
#endif // STACK_DEBUG
					byte TX_PHY, RX_PHY;
					if (LE::readPhy(context.settings.handle, &TX_PHY, &RX_PHY) == HCI::Status::Success)
					{
#ifdef STACK_DEBUG
						printf("Read_PHY success\n");
						printf("PHY Param TX = %d, RX = %d\n", TX_PHY, RX_PHY);
#endif // STACK_DEBUG
					}
#ifdef STACK_DEBUG
					else printf("Read conf not succeess\n");
#endif // STACK_DEBUG
				}
				break;
			case EVT_LE_CONN_COMPLETE:
				{
					hci_le_connection_complete_event_rp0 *connection_complete_event;
					connection_complete_event = (hci_le_connection_complete_event_rp0 *) meta_evt->data;// The connection is done, there is no need anymore to schedule the LP ADV
//					xTimerStop(context.advTim, 0);
#ifdef STACK_DEBUG
					printf("EVT_LE_CONN_COMPLETE for connection handle 0x%x\n", connection_complete_event->Connection_Handle);
#endif // STACK_DEBUG
					if (context.connection == BLE::Connection::LowPowerConnecting) context.connection = BLE::Connection::ConnectedClient;// Connection as client
					else context.connection = BLE::Connection::ConnectedServer; // Connection as server
					context.settings.handle = connection_complete_event->Connection_Handle;
					P2P::connectionSet(context.settings.handle);
				}
				break;
			default: break;
			}
		}
		break;
	case EVT_VENDOR:
		{
			TL::BleEvt *blue_evt = (TL::BleEvt *) evt->payload;
			switch (blue_evt->code)
			{
				aci_gap_pairing_complete_event_rp0 *pairing_complete;
			case EVT_BLUE_GAP_LIMITED_DISCOVERABLE:
#ifdef STACK_DEBUG
				printf("\r\n\r** EVT_BLUE_GAP_LIMITED_DISCOVERABLE\n");
#endif // STACK_DEBUG
				break;
			case EVT_BLUE_GAP_PASS_KEY_REQUEST:  
#ifdef STACK_DEBUG
				printf("\r\n\r** EVT_BLUE_GAP_PASS_KEY_REQUEST\n");
#endif // STACK_DEBUG
				GAP::passKeyResp(context.settings.handle, 123456);
#ifdef STACK_DEBUG
				printf("aci_gap_pass_key_resp\n");
#endif // STACK_DEBUG
				break;
			case EVT_BLUE_GAP_AUTHORIZATION_REQUEST:
#ifdef STACK_DEBUG
				printf("EVT_BLUE_GAP_AUTHORIZATION_REQUEST\n");
#endif // STACK_DEBUG
				break;
			case EVT_BLUE_GAP_SLAVE_SECURITY_INITIATED:
#ifdef STACK_DEBUG
				printf("EVT_BLUE_GAP_SLAVE_SECURITY_INITIATED\n");
#endif // STACK_DEBUG
				break;
			case EVT_BLUE_GAP_BOND_LOST:    
#ifdef STACK_DEBUG
				printf("EVT_BLUE_GAP_BOND_LOST\n");
#endif // STACK_DEBUG
				GAP::allowRebond(context.settings.handle);
#ifdef STACK_DEBUG
				printf("Send allow rebond\n");
#endif // STACK_DEBUG
				break;
			case EVT_BLUE_GAP_DEVICE_FOUND:
#ifdef STACK_DEBUG
				printf("EVT_BLUE_GAP_DEVICE_FOUND\n");
#endif // STACK_DEBUG
				break;
			case EVT_BLUE_GAP_ADDR_NOT_RESOLVED:
#ifdef STACK_DEBUG
				printf("EVT_BLUE_GAP_DEVICE_FOUND\n");
#endif // STACK_DEBUG
				break;
			case EVT_BLUE_GAP_KEYPRESS_NOTIFICATION:
#ifdef STACK_DEBUG
				printf("EVT_BLUE_GAP_KEYPRESS_NOTIFICATION\n");
#endif // STACK_DEBUG
				break;
			case EVT_BLUE_GAP_NUMERIC_COMPARISON_VALUE:
#ifdef STACK_DEBUG
				printf("numeric_value = %d\n", ((aci_gap_numeric_comparison_value_event_rp0 *)(blue_evt->payload))->Numeric_Value);
				printf("Hex_value = %x\n", ((aci_gap_numeric_comparison_value_event_rp0 *)(blue_evt->payload))->Numeric_Value);
#endif // STACK_DEBUG
				GAP::numericComparisonValueConfirm(context.settings.handle, true);
#ifdef STACK_DEBUG
				printf("aci_gap_numeric_comparison_value_confirm_yesno-->YES\n");
#endif // STACK_DEBUG
				break;
			case (EVT_BLUE_GAP_PAIRING_CMPLT):
				{
					pairing_complete = (aci_gap_pairing_complete_event_rp0*)blue_evt->payload;
#ifdef STACK_DEBUG
					printf("BLE_CTRL_App_Notification: EVT_BLUE_GAP_PAIRING_CMPLT, pairing_complete->Status = %d\n", pairing_complete->Status);
					if (pairing_complete->Status == 0) printf("Pairing OK\n");
					else printf("Pairing KO\n");
#endif // STACK_DEBUG
				}
				break;
			case EVT_BLUE_GAP_PROCEDURE_COMPLETE:
#ifdef STACK_DEBUG
				printf("EVT_BLUE_GAP_PROCEDURE_COMPLETE\n");
#endif // STACK_DEBUG
				break;
			}
		}
		break;
	default: break;
	}
}

void BLE::advRequest(Connection status, char *name, byte uuidLen, byte *uuid)
{
	if (context.connection == status) return;
	if (!(status == Connection::FastAdvertasing || status == BLE::Connection::LowPowerAdvertasing)) return;
	
//	xTimerStop(context.advTim, 0);// Stop the timer, it will be restarted for a new shot
#ifdef STACK_DEBUG
	printf("Start %s advertising; Current connection state: %s\n", connectionName[(byte)status], connectionName[(byte)context.connection]);
#endif // STACK_DEBUG
	HCI::Status result = HCI::Status::InvalidParams;
	if (status == Connection::LowPowerAdvertasing && context.connection == Connection::FastAdvertasing)
	{
		result = GAP::setNonDiscoverable(); // Connection in ADVERTISE mode have to stop the current advertising
#ifdef STACK_DEBUG
		if(result == HCI::Status::Success) printf("Successfully Stopped Advertising\n");
		else printf("Stop Advertising Failed; Status: %d\n", (byte)result);
#endif // STACK_DEBUG
	}
	context.connection = BLE::Connection::Idle;
	// Start Fast or Low Power Advertising
	char _name[40] = { AD_TYPE_COMPLETE_LOCAL_NAME };
	strcpy(_name + 1, name);
	result = GAP::updateAdvData(sizeof(manufacturer), manufacturer);
	ushort min = status == BLE::Connection::FastAdvertasing ? CFG_FAST_CONN_ADV_INTERVAL_MIN : CFG_LP_CONN_ADV_INTERVAL_MIN;
	ushort max = status == BLE::Connection::FastAdvertasing ? CFG_FAST_CONN_ADV_INTERVAL_MAX : CFG_LP_CONN_ADV_INTERVAL_MAX;
	result = GAP::setDiscoverable(GAP::AdvertiseType::Ind, min, max, PUBLIC_ADDR, NO_WHITE_LIST_USE, strlen(_name), (byte *)_name, uuidLen, uuid, 0, 0);
	if (result == HCI::Status::Success)
	{
		context.connection = status;
#ifdef STACK_DEBUG
		printf("Successfully Start Advertising\n");
#endif // STACK_DEBUG
	}
#ifdef STACK_DEBUG
	else printf("Start %s Advertising Failed, Status: %d\n", connectionName[(byte)result], (byte)result);
#endif // STACK_DEBUG
}

void BLE::secondStage(TaskHandle_t thread)
{
	HCI::init([]()
	{
		HCI::Init bleInitCmdParemeter =
		{
			0,
			0,
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
		};
		SHCI::send(SHCI::Opcode::C2_BLE_INIT, sizeof(HCI::Init), (byte *)&bleInitCmdParemeter);// Starts the BLE Stack on CPU2
	},
	thread);
	LE::reset();// Initialize HCI layer; HCI Reset to synchronise BLE Stack
	HAL::writeConfigData(CONFIG_DATA_PUBADDR_OFFSET, CONFIG_DATA_PUBADDR_LEN, settings.dis.serial);
	for (byte i = 0; i < 6; i++) manufacturer[sizeof(manufacturer) - i - 1] = settings.dis.serial[i]; // BLE MAC in ADV Packet
	HAL::writeConfigData(CONFIG_DATA_IR_OFFSET, CONFIG_DATA_IR_LEN, (byte *)configIRvalue);// Write Identity root key used to derive LTK and CSRK
	HAL::writeConfigData(CONFIG_DATA_ER_OFFSET, CONFIG_DATA_ER_LEN, (byte *)configERvalue);// Write Encryption root key used to derive LTK and CSRK
	HAL::writeConfigData(CONFIG_DATA_RANDOM_ADDRESS_OFFSET, CONFIG_DATA_RANDOM_ADDRESS_LEN, (byte *)UID64_BASE);
	HAL::setTxPowerLevel(HAL::Power::_0_dBm, true);
	GATT::init();
	GAP::InitHandlers handlers;
	if (GAP::init(GAP::Role::Peripheral, false, strlen(settings.name), handlers) == HCI::Status::Success)// Initialize GAP interface
	{
		GATT::updateCharValue(handlers.service, handlers.name, 0, strlen(settings.name), (byte *)settings.name);
		GATT::updateCharValue(handlers.service, handlers.appearance, 0, 2, (byte *)(const ushort[]){ BLE_CFG_GAP_APPEARANCE });
	}
	else
	{
		status = Status::InitalizeError;
		return;
	}
	LE::setDefaultPhy(ALL_PHYS_PREFERENCE, TX_2M_PREFERRED, RX_2M_PREFERRED);// Initialize Default PHY
	GAP::setIoCapability(CFG_IO_CAPABILITY); // Initialize IO capability
	// Initialize authentication
	GAP::setAuthenticationRequirement(	CFG_BONDING_MODE, CFG_MITM_PROTECTION, CFG_SC_SUPPORT, CFG_KEYPRESS_NOTIFICATION_SUPPORT, CFG_ENCRYPTION_KEY_SIZE_MIN, CFG_ENCRYPTION_KEY_SIZE_MAX, CFG_USED_FIXED_PIN, CFG_FIXED_PIN, PUBLIC_ADDR);
	if (CFG_BONDING_MODE) GAP::configureWhitelist();
	Service::init(settings.dis);
	context.connection = Connection::Idle;
	context.settings.handle = 0xFFFF;
	advRequest(Connection::LowPowerAdvertasing, settings.dis.model, 0, 0);// internal name
}

BLE::Status BLE::init(Settings &settings)
{
	if (!strlen(settings.name) || !strlen(settings.dis.firmware) || !strlen(settings.dis.hardware) || !strlen(settings.dis.manufacturer) || !strlen(settings.dis.model)) return Status::EmptyParameters;
	BLE::settings = settings;
	__NVIC_SetPriorityGrouping(3);
	__NVIC_SetPriority(IRQn_Type::IPCC_C1_RX_IRQn, 2);
	__NVIC_SetPriority(IRQn_Type::IPCC_C1_TX_IRQn, 2);
	RCC->CSR |= RCC_CSR_RFWKPSEL_0;
	
	TL::init();
	SHCI::init(secondStage);
	CPU2::enable();
	return Status::Success;
}