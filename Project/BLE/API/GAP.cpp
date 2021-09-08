#include "GAP.hpp"
#include "string.h"

HCI::Status GAP::setNonDiscoverable()
{
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::SetNonDiscoverable, &rq);
	return status;
}

//HCI::Status GAP::aci_gap_set_limited_discoverable(byte Advertising_Type,
//	ushort Advertising_Interval_Min,
//	ushort Advertising_Interval_Max,
//	byte Own_Address_Type,
//	byte Advertising_Filter_Policy,
//	byte Local_Name_Length,
//	byte Local_Name[],
//	byte Service_Uuid_length,
//	byte Service_Uuid_List[],
//	ushort Slave_Conn_Interval_Min,
//	ushort Slave_Conn_Interval_Max)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_set_limited_discoverable_cp0 *cp0 = (aci_gap_set_limited_discoverable_cp0*)(cmd_buffer);
//	aci_gap_set_limited_discoverable_cp1 *cp1 = (aci_gap_set_limited_discoverable_cp1*)(cmd_buffer + 1 + 2 + 2 + 1 + 1 + 1 + Local_Name_Length * (sizeof(byte)));
//	aci_gap_set_limited_discoverable_cp2 *cp2 = (aci_gap_set_limited_discoverable_cp2*)(cmd_buffer + 1 + 2 + 2 + 1 + 1 + 1 + Local_Name_Length * (sizeof(byte)) + 1 + Service_Uuid_length * (sizeof(byte)));
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Advertising_Type = htob(Advertising_Type, 1);
//	index_input += 1;
//	cp0->Advertising_Interval_Min = htob(Advertising_Interval_Min, 2);
//	index_input += 2;
//	cp0->Advertising_Interval_Max = htob(Advertising_Interval_Max, 2);
//	index_input += 2;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Advertising_Filter_Policy = htob(Advertising_Filter_Policy, 1);
//	index_input += 1;
//	cp0->Local_Name_Length = htob(Local_Name_Length, 1);
//	index_input += 1;
//	/* var_len_data input */
//	{
//		Osal_MemCpy((void *) &cp0->Local_Name, (const void *) Local_Name, Local_Name_Length);
//		index_input += Local_Name_Length;
//		{
//			cp1->Service_Uuid_length = htob(Service_Uuid_length, 1);
//		}
//		index_input += 1;
//		Osal_MemCpy((void *) &cp1->Service_Uuid_List, (const void *) Service_Uuid_List, Service_Uuid_length);
//		index_input += Service_Uuid_length;
//		{
//			cp2->Slave_Conn_Interval_Min = htob(Slave_Conn_Interval_Min, 2);
//		}
//		index_input += 2;
//		{
//			cp2->Slave_Conn_Interval_Max = htob(Slave_Conn_Interval_Max, 2);
//		}
//		index_input += 2;
//	}
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x082;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status GAP::setDiscoverable(AdvertiseType advType, ushort advIntervalMin, ushort advIntervalMax, byte ownAddrType, byte advFilterPolicy, byte nameLength, byte name[], byte uuidLength, byte uuidList[], ushort connectionIntervalMin, ushort connectionIntervalMax)
{
	byte buf[BLE_CMD_MAX_PARAM_LEN];
	SetDiscoverable::Com0 *cmd0 = (SetDiscoverable::Com0 *)buf;
	SetDiscoverable::Com1 *cmd1 = (SetDiscoverable::Com1 *)(buf + 1 + 2 + 2 + 1 + 1 + 1 + nameLength);
	SetDiscoverable::Com2 *cmd2 = (SetDiscoverable::Com2 *)(buf + 1 + 2 + 2 + 1 + 1 + 1 + nameLength + 1 + uuidLength);
	cmd0->Advertising_Type = advType;
	cmd0->Advertising_Interval_Min = advIntervalMin;
	cmd0->Advertising_Interval_Max = advIntervalMax;
	cmd0->Own_Address_Type = ownAddrType;
	cmd0->Advertising_Filter_Policy = advFilterPolicy;
	cmd0->Local_Name_Length = nameLength;
	memcpy(cmd0->Local_Name, name, nameLength);
	cmd1->Service_Uuid_length = uuidLength;
	memcpy(cmd1->Service_Uuid_List, uuidList, uuidLength);
	cmd2->Slave_Conn_Interval_Min = connectionIntervalMin;
	cmd2->Slave_Conn_Interval_Max = connectionIntervalMax;
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::SetDiscoverable, &rq, nameLength + uuidLength + 13, buf);
	return status;
}

//HCI::Status GAP::aci_gap_set_direct_connectable(byte Own_Address_Type,
//	byte Directed_Advertising_Type,
//	byte Direct_Address_Type,
//	byte Direct_Address[6],
//	ushort Advertising_Interval_Min,
//	ushort Advertising_Interval_Max)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_set_direct_connectable_cp0 *cp0 = (aci_gap_set_direct_connectable_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Directed_Advertising_Type = htob(Directed_Advertising_Type, 1);
//	index_input += 1;
//	cp0->Direct_Address_Type = htob(Direct_Address_Type, 1);
//	index_input += 1;
//	Osal_MemCpy((void *) &cp0->Direct_Address, (const void *) Direct_Address, 6);
//	index_input += 6;
//	cp0->Advertising_Interval_Min = htob(Advertising_Interval_Min, 2);
//	index_input += 2;
//	cp0->Advertising_Interval_Max = htob(Advertising_Interval_Max, 2);
//	index_input += 2;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x084;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status GAP::setIoCapability(byte capability)
{
	SetIoCapability cmd;
	cmd.capability = capability;
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::SetIoCapability, &rq, sizeof(cmd), (byte *)&cmd);
	return status;
}

HCI::Status GAP::setAuthenticationRequirement(byte bondingMode, byte mitmMode, byte SCsupport, byte keyPressNotificationSupport, byte minEncryptionKeySize, byte maxEncryptionKeySize, byte useFixedPin, uint fixedPin, byte identityAddressType)
{
	SetAuthenticationRequirement cmd;
	cmd.bondingMode = bondingMode;
	cmd.mitmMode = mitmMode;
	cmd.SCsupport = SCsupport;
	cmd.keyPressNotificationSupport = keyPressNotificationSupport;
	cmd.minEncryptionKeySize = minEncryptionKeySize;
	cmd.maxEncryptionKeySize = maxEncryptionKeySize;
	cmd.useFixedPin = useFixedPin;
	cmd.fixedPin = fixedPin;
	cmd.identityAddressType = identityAddressType;
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::SetAuthenticationRequirement, &rq, sizeof(cmd), (byte *)&cmd);
	return status;
}

//HCI::Status GAP::aci_gap_set_authorization_requirement(ushort Connection_Handle,
//	byte Authorization_Enable)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_set_authorization_requirement_cp0 *cp0 = (aci_gap_set_authorization_requirement_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Connection_Handle = htob(Connection_Handle, 2);
//	index_input += 2;
//	cp0->Authorization_Enable = htob(Authorization_Enable, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x087;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status GAP::passKeyResp(ushort handle, uint key)
{
	PassKeyResp::Com0 cmd;
	cmd.handle = handle;
	cmd.key = key;
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::PassKeyResp, &rq, sizeof(cmd), (byte *)&cmd);
	return status;
}

//HCI::Status GAP::aci_gap_authorization_resp(ushort Connection_Handle,
//	byte Authorize)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_authorization_resp_cp0 *cp0 = (aci_gap_authorization_resp_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Connection_Handle = htob(Connection_Handle, 2);
//	index_input += 2;
//	cp0->Authorize = htob(Authorize, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x089;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status GAP::init(Role role, byte privacy, byte deviceNameCharLength, InitHandlers & handlers)
{
	InitCommand cmd;
	cmd.role = role;
	cmd.privacy = privacy;
	cmd.deviceNameCharLen = deviceNameCharLength;
	InitResponse rsp = { };
	HCI::Request rq = { &rsp, sizeof(rsp) };
	HCI::send((ushort)Opcode::Initialize, &rq, sizeof(cmd), (byte *)&cmd);
	if (rsp.status == HCI::Status::Success)
	{
		handlers.service = rsp.serviceHandle;
		handlers.name = rsp.devNameCharHandle;
		handlers.appearance = rsp.appearanceCharHandle;
	}
	return rsp.status;
}

//HCI::Status GAP::aci_gap_set_non_connectable(byte Advertising_Event_Type,
//	byte Own_Address_Type)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_set_non_connectable_cp0 *cp0 = (aci_gap_set_non_connectable_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Advertising_Event_Type = htob(Advertising_Event_Type, 1);
//	index_input += 1;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x08b;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_set_undirected_connectable(ushort Advertising_Interval_Min,
//	ushort Advertising_Interval_Max,
//	byte Own_Address_Type,
//	byte Adv_Filter_Policy)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_set_undirected_connectable_cp0 *cp0 = (aci_gap_set_undirected_connectable_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Advertising_Interval_Min = htob(Advertising_Interval_Min, 2);
//	index_input += 2;
//	cp0->Advertising_Interval_Max = htob(Advertising_Interval_Max, 2);
//	index_input += 2;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Adv_Filter_Policy = htob(Adv_Filter_Policy, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x08c;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_slave_security_req(ushort Connection_Handle)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_slave_security_req_cp0 *cp0 = (aci_gap_slave_security_req_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Connection_Handle = htob(Connection_Handle, 2);
//	index_input += 2;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x08d;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status GAP::updateAdvData(byte AdvDataLen, byte AdvData[])
{
	UpdateAdvertiseData::Com0 cmd0 = { AdvDataLen };
	memcpy(cmd0.AdvData, AdvData, AdvDataLen);
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::UpdateAdvertiseData, &rq, AdvDataLen + 1, (byte *)&cmd0);
	return status;
}

//HCI::Status GAP::aci_gap_delete_ad_type(byte ADType)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_delete_ad_type_cp0 *cp0 = (aci_gap_delete_ad_type_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->ADType = htob(ADType, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x08f;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_get_security_level(ushort Connection_Handle,
//	byte *Security_Mode,
//	byte *Security_Level)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_get_security_level_cp0 *cp0 = (aci_gap_get_security_level_cp0*)(cmd_buffer);
//	aci_gap_get_security_level_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	int index_input = 0;
//	cp0->Connection_Handle = htob(Connection_Handle, 2);
//	index_input += 2;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x090;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*Security_Mode = btoh(resp.Security_Mode, 1);
//	*Security_Level = btoh(resp.Security_Level, 1);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_set_event_mask(ushort GAP_Evt_Mask)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_set_event_mask_cp0 *cp0 = (aci_gap_set_event_mask_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->GAP_Evt_Mask = htob(GAP_Evt_Mask, 2);
//	index_input += 2;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x091;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status GAP::configureWhitelist()
{
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::ConfigureWhitelist, &rq);
	return status;
}

//HCI::Status GAP::aci_gap_terminate(ushort Connection_Handle,
//	byte Reason)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_terminate_cp0 *cp0 = (aci_gap_terminate_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Connection_Handle = htob(Connection_Handle, 2);
//	index_input += 2;
//	cp0->Reason = htob(Reason, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x093;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_clear_security_db(void)
//{
//	struct hci_request rq;
//	HCI::Status GAP::status = 0;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x094;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status GAP::allowRebond(ushort handle)
{
	AllowRebond::Com0 cmd;
	cmd.handle = handle;
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::AllowRebond, &rq, sizeof(cmd), (byte *)&cmd);
	return status;
}

//HCI::Status GAP::aci_gap_start_limited_discovery_proc(ushort LE_Scan_Interval,
//	ushort LE_Scan_Window,
//	byte Own_Address_Type,
//	byte Filter_Duplicates)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_start_limited_discovery_proc_cp0 *cp0 = (aci_gap_start_limited_discovery_proc_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
//	index_input += 2;
//	cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
//	index_input += 2;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Filter_Duplicates = htob(Filter_Duplicates, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x096;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_start_general_discovery_proc(ushort LE_Scan_Interval,
//	ushort LE_Scan_Window,
//	byte Own_Address_Type,
//	byte Filter_Duplicates)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_start_general_discovery_proc_cp0 *cp0 = (aci_gap_start_general_discovery_proc_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
//	index_input += 2;
//	cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
//	index_input += 2;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Filter_Duplicates = htob(Filter_Duplicates, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x097;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_start_name_discovery_proc(ushort LE_Scan_Interval,
//	ushort LE_Scan_Window,
//	byte Peer_Address_Type,
//	byte Peer_Address[6],
//	byte Own_Address_Type,
//	ushort Conn_Interval_Min,
//	ushort Conn_Interval_Max,
//	ushort Conn_Latency,
//	ushort Supervision_Timeout,
//	ushort Minimum_CE_Length,
//	ushort Maximum_CE_Length)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_start_name_discovery_proc_cp0 *cp0 = (aci_gap_start_name_discovery_proc_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
//	index_input += 2;
//	cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
//	index_input += 2;
//	cp0->Peer_Address_Type = htob(Peer_Address_Type, 1);
//	index_input += 1;
//	Osal_MemCpy((void *) &cp0->Peer_Address, (const void *) Peer_Address, 6);
//	index_input += 6;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Conn_Interval_Min = htob(Conn_Interval_Min, 2);
//	index_input += 2;
//	cp0->Conn_Interval_Max = htob(Conn_Interval_Max, 2);
//	index_input += 2;
//	cp0->Conn_Latency = htob(Conn_Latency, 2);
//	index_input += 2;
//	cp0->Supervision_Timeout = htob(Supervision_Timeout, 2);
//	index_input += 2;
//	cp0->Minimum_CE_Length = htob(Minimum_CE_Length, 2);
//	index_input += 2;
//	cp0->Maximum_CE_Length = htob(Maximum_CE_Length, 2);
//	index_input += 2;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x098;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_start_auto_connection_establish_proc(ushort LE_Scan_Interval,
//	ushort LE_Scan_Window,
//	byte Own_Address_Type,
//	ushort Conn_Interval_Min,
//	ushort Conn_Interval_Max,
//	ushort Conn_Latency,
//	ushort Supervision_Timeout,
//	ushort Minimum_CE_Length,
//	ushort Maximum_CE_Length,
//	byte Num_of_Whitelist_Entries,
//	Whitelist_Entry_t Whitelist_Entry[])
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_start_auto_connection_establish_proc_cp0 *cp0 = (aci_gap_start_auto_connection_establish_proc_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
//	index_input += 2;
//	cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
//	index_input += 2;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Conn_Interval_Min = htob(Conn_Interval_Min, 2);
//	index_input += 2;
//	cp0->Conn_Interval_Max = htob(Conn_Interval_Max, 2);
//	index_input += 2;
//	cp0->Conn_Latency = htob(Conn_Latency, 2);
//	index_input += 2;
//	cp0->Supervision_Timeout = htob(Supervision_Timeout, 2);
//	index_input += 2;
//	cp0->Minimum_CE_Length = htob(Minimum_CE_Length, 2);
//	index_input += 2;
//	cp0->Maximum_CE_Length = htob(Maximum_CE_Length, 2);
//	index_input += 2;
//	cp0->Num_of_Whitelist_Entries = htob(Num_of_Whitelist_Entries, 1);
//	index_input += 1;
//	Osal_MemCpy((void*) &cp0->Whitelist_Entry, (const void *) Whitelist_Entry, Num_of_Whitelist_Entries * (sizeof(Whitelist_Entry_t)));
//	index_input += Num_of_Whitelist_Entries * (sizeof(Whitelist_Entry_t));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x099;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_start_general_connection_establish_proc(byte LE_Scan_Type,
//	ushort LE_Scan_Interval,
//	ushort LE_Scan_Window,
//	byte Own_Address_Type,
//	byte Scanning_Filter_Policy,
//	byte Filter_Duplicates)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_start_general_connection_establish_proc_cp0 *cp0 = (aci_gap_start_general_connection_establish_proc_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->LE_Scan_Type = htob(LE_Scan_Type, 1);
//	index_input += 1;
//	cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
//	index_input += 2;
//	cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
//	index_input += 2;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Scanning_Filter_Policy = htob(Scanning_Filter_Policy, 1);
//	index_input += 1;
//	cp0->Filter_Duplicates = htob(Filter_Duplicates, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x09a;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_start_selective_connection_establish_proc(byte LE_Scan_Type,
//	ushort LE_Scan_Interval,
//	ushort LE_Scan_Window,
//	byte Own_Address_Type,
//	byte Scanning_Filter_Policy,
//	byte Filter_Duplicates,
//	byte Num_of_Whitelist_Entries,
//	Whitelist_Entry_t Whitelist_Entry[])
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_start_selective_connection_establish_proc_cp0 *cp0 = (aci_gap_start_selective_connection_establish_proc_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->LE_Scan_Type = htob(LE_Scan_Type, 1);
//	index_input += 1;
//	cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
//	index_input += 2;
//	cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
//	index_input += 2;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Scanning_Filter_Policy = htob(Scanning_Filter_Policy, 1);
//	index_input += 1;
//	cp0->Filter_Duplicates = htob(Filter_Duplicates, 1);
//	index_input += 1;
//	cp0->Num_of_Whitelist_Entries = htob(Num_of_Whitelist_Entries, 1);
//	index_input += 1;
//	Osal_MemCpy((void*) &cp0->Whitelist_Entry, (const void *) Whitelist_Entry, Num_of_Whitelist_Entries * (sizeof(Whitelist_Entry_t)));
//	index_input += Num_of_Whitelist_Entries * (sizeof(Whitelist_Entry_t));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x09b;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_create_connection(ushort LE_Scan_Interval,
//	ushort LE_Scan_Window,
//	byte Peer_Address_Type,
//	byte Peer_Address[6],
//	byte Own_Address_Type,
//	ushort Conn_Interval_Min,
//	ushort Conn_Interval_Max,
//	ushort Conn_Latency,
//	ushort Supervision_Timeout,
//	ushort Minimum_CE_Length,
//	ushort Maximum_CE_Length)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_create_connection_cp0 *cp0 = (aci_gap_create_connection_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
//	index_input += 2;
//	cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
//	index_input += 2;
//	cp0->Peer_Address_Type = htob(Peer_Address_Type, 1);
//	index_input += 1;
//	Osal_MemCpy((void *) &cp0->Peer_Address, (const void *) Peer_Address, 6);
//	index_input += 6;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Conn_Interval_Min = htob(Conn_Interval_Min, 2);
//	index_input += 2;
//	cp0->Conn_Interval_Max = htob(Conn_Interval_Max, 2);
//	index_input += 2;
//	cp0->Conn_Latency = htob(Conn_Latency, 2);
//	index_input += 2;
//	cp0->Supervision_Timeout = htob(Supervision_Timeout, 2);
//	index_input += 2;
//	cp0->Minimum_CE_Length = htob(Minimum_CE_Length, 2);
//	index_input += 2;
//	cp0->Maximum_CE_Length = htob(Maximum_CE_Length, 2);
//	index_input += 2;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x09c;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_terminate_gap_proc(byte Procedure_Code)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_terminate_gap_proc_cp0 *cp0 = (aci_gap_terminate_gap_proc_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Procedure_Code = htob(Procedure_Code, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x09d;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_start_connection_update(ushort Connection_Handle,
//	ushort Conn_Interval_Min,
//	ushort Conn_Interval_Max,
//	ushort Conn_Latency,
//	ushort Supervision_Timeout,
//	ushort Minimum_CE_Length,
//	ushort Maximum_CE_Length)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_start_connection_update_cp0 *cp0 = (aci_gap_start_connection_update_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Connection_Handle = htob(Connection_Handle, 2);
//	index_input += 2;
//	cp0->Conn_Interval_Min = htob(Conn_Interval_Min, 2);
//	index_input += 2;
//	cp0->Conn_Interval_Max = htob(Conn_Interval_Max, 2);
//	index_input += 2;
//	cp0->Conn_Latency = htob(Conn_Latency, 2);
//	index_input += 2;
//	cp0->Supervision_Timeout = htob(Supervision_Timeout, 2);
//	index_input += 2;
//	cp0->Minimum_CE_Length = htob(Minimum_CE_Length, 2);
//	index_input += 2;
//	cp0->Maximum_CE_Length = htob(Maximum_CE_Length, 2);
//	index_input += 2;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x09e;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_send_pairing_req(ushort Connection_Handle,
//	byte Force_Rebond)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_send_pairing_req_cp0 *cp0 = (aci_gap_send_pairing_req_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Connection_Handle = htob(Connection_Handle, 2);
//	index_input += 2;
//	cp0->Force_Rebond = htob(Force_Rebond, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x09f;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_resolve_private_addr(byte Address[6],
//	byte Actual_Address[6])
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_resolve_private_addr_cp0 *cp0 = (aci_gap_resolve_private_addr_cp0*)(cmd_buffer);
//	aci_gap_resolve_private_addr_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	int index_input = 0;
//	Osal_MemCpy((void *) &cp0->Address, (const void *) Address, 6);
//	index_input += 6;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a0;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	Osal_MemCpy((void *) Actual_Address, (const void *) resp.Actual_Address, 6);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_set_broadcast_mode(ushort Advertising_Interval_Min,
//	ushort Advertising_Interval_Max,
//	byte Advertising_Type,
//	byte Own_Address_Type,
//	byte Adv_Data_Length,
//	byte Adv_Data[],
//	byte Num_of_Whitelist_Entries,
//	Whitelist_Entry_t Whitelist_Entry[])
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_set_broadcast_mode_cp0 *cp0 = (aci_gap_set_broadcast_mode_cp0*)(cmd_buffer);
//	aci_gap_set_broadcast_mode_cp1 *cp1 = (aci_gap_set_broadcast_mode_cp1*)(cmd_buffer + 2 + 2 + 1 + 1 + 1 + Adv_Data_Length * (sizeof(byte)));
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Advertising_Interval_Min = htob(Advertising_Interval_Min, 2);
//	index_input += 2;
//	cp0->Advertising_Interval_Max = htob(Advertising_Interval_Max, 2);
//	index_input += 2;
//	cp0->Advertising_Type = htob(Advertising_Type, 1);
//	index_input += 1;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Adv_Data_Length = htob(Adv_Data_Length, 1);
//	index_input += 1;
//	/* var_len_data input */
//	{
//		Osal_MemCpy((void *) &cp0->Adv_Data, (const void *) Adv_Data, Adv_Data_Length);
//		index_input += Adv_Data_Length;
//		{
//			cp1->Num_of_Whitelist_Entries = htob(Num_of_Whitelist_Entries, 1);
//		}
//		index_input += 1;
//		Osal_MemCpy((void *) &cp1->Whitelist_Entry, (const void *) Whitelist_Entry, Num_of_Whitelist_Entries * (sizeof(Whitelist_Entry_t)));
//		index_input += Num_of_Whitelist_Entries * (sizeof(Whitelist_Entry_t));
//	}
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a1;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_start_observation_proc(ushort LE_Scan_Interval,
//	ushort LE_Scan_Window,
//	byte LE_Scan_Type,
//	byte Own_Address_Type,
//	byte Filter_Duplicates,
//	byte Scanning_Filter_Policy)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_start_observation_proc_cp0 *cp0 = (aci_gap_start_observation_proc_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->LE_Scan_Interval = htob(LE_Scan_Interval, 2);
//	index_input += 2;
//	cp0->LE_Scan_Window = htob(LE_Scan_Window, 2);
//	index_input += 2;
//	cp0->LE_Scan_Type = htob(LE_Scan_Type, 1);
//	index_input += 1;
//	cp0->Own_Address_Type = htob(Own_Address_Type, 1);
//	index_input += 1;
//	cp0->Filter_Duplicates = htob(Filter_Duplicates, 1);
//	index_input += 1;
//	cp0->Scanning_Filter_Policy = htob(Scanning_Filter_Policy, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a2;
//	rq.event = 0x0F;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_get_bonded_devices(byte *Num_of_Addresses,
//	Bonded_Device_Entry_t Bonded_Device_Entry[])
//{
//	struct hci_request rq;
//	aci_gap_get_bonded_devices_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a3;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*Num_of_Addresses = btoh(resp.Num_of_Addresses, 1);
//	Osal_MemCpy((void *) Bonded_Device_Entry, (const void *) resp.Bonded_Device_Entry, *Num_of_Addresses * (sizeof(Bonded_Device_Entry_t)));
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_is_device_bonded(byte Peer_Address_Type,
//	byte Peer_Address[6])
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_is_device_bonded_cp0 *cp0 = (aci_gap_is_device_bonded_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Peer_Address_Type = htob(Peer_Address_Type, 1);
//	index_input += 1;
//	Osal_MemCpy((void *) &cp0->Peer_Address, (const void *) Peer_Address, 6);
//	index_input += 6;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a4;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status GAP::numericComparisonValueConfirm(ushort handle, bool confirm)
{
	NumericComparisonValueConfirm::Com0 cmd;
	cmd.handle = handle;
	cmd.confirm = confirm;
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::NumericComparisonValueConfirm, &rq, sizeof(cmd), (byte *)&cmd);
	return status;
}

//HCI::Status GAP::aci_gap_passkey_input(ushort Connection_Handle,
//	byte Input_Type)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_passkey_input_cp0 *cp0 = (aci_gap_passkey_input_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Connection_Handle = htob(Connection_Handle, 2);
//	index_input += 2;
//	cp0->Input_Type = htob(Input_Type, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a6;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_get_oob_data(byte OOB_Data_Type,
//	byte *Address_Type,
//	byte Address[6],
//	byte *OOB_Data_Len,
//	byte OOB_Data[16])
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_get_oob_data_cp0 *cp0 = (aci_gap_get_oob_data_cp0*)(cmd_buffer);
//	aci_gap_get_oob_data_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	int index_input = 0;
//	cp0->OOB_Data_Type = htob(OOB_Data_Type, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a7;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*Address_Type = btoh(resp.Address_Type, 1);
//	Osal_MemCpy((void *) Address, (const void *) resp.Address, 6);
//	*OOB_Data_Len = btoh(resp.OOB_Data_Len, 1);
//	Osal_MemCpy((void *) OOB_Data, (const void *) resp.OOB_Data, 16);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_set_oob_data(byte Device_Type,
//	byte Address_Type,
//	byte Address[6],
//	byte OOB_Data_Type,
//	byte OOB_Data_Len,
//	byte OOB_Data[16])
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_set_oob_data_cp0 *cp0 = (aci_gap_set_oob_data_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Device_Type = htob(Device_Type, 1);
//	index_input += 1;
//	cp0->Address_Type = htob(Address_Type, 1);
//	index_input += 1;
//	Osal_MemCpy((void *) &cp0->Address, (const void *) Address, 6);
//	index_input += 6;
//	cp0->OOB_Data_Type = htob(OOB_Data_Type, 1);
//	index_input += 1;
//	cp0->OOB_Data_Len = htob(OOB_Data_Len, 1);
//	index_input += 1;
//	Osal_MemCpy((void *) &cp0->OOB_Data, (const void *) OOB_Data, 16);
//	index_input += 16;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a8;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_add_devices_to_resolving_list(byte Num_of_Resolving_list_Entries,
//	Whitelist_Identity_Entry_t Whitelist_Identity_Entry[],
//	byte Clear_Resolving_List)
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_add_devices_to_resolving_list_cp0 *cp0 = (aci_gap_add_devices_to_resolving_list_cp0*)(cmd_buffer);
//	aci_gap_add_devices_to_resolving_list_cp1 *cp1 = (aci_gap_add_devices_to_resolving_list_cp1*)(cmd_buffer + 1 + Num_of_Resolving_list_Entries * (sizeof(Whitelist_Identity_Entry_t)));
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Num_of_Resolving_list_Entries = htob(Num_of_Resolving_list_Entries, 1);
//	index_input += 1;
//	/* var_len_data input */
//	{
//		Osal_MemCpy((void *) &cp0->Whitelist_Identity_Entry, (const void *) Whitelist_Identity_Entry, Num_of_Resolving_list_Entries * (sizeof(Whitelist_Identity_Entry_t)));
//		index_input += Num_of_Resolving_list_Entries * (sizeof(Whitelist_Identity_Entry_t));
//		{
//			cp1->Clear_Resolving_List = htob(Clear_Resolving_List, 1);
//		}
//		index_input += 1;
//	}
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0a9;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status GAP::aci_gap_remove_bonded_device(byte Peer_Identity_Address_Type,
//	byte Peer_Identity_Address[6])
//{
//	struct hci_request rq;
//	byte cmd_buffer[BLE_CMD_MAX_PARAM_LEN];
//	aci_gap_remove_bonded_device_cp0 *cp0 = (aci_gap_remove_bonded_device_cp0*)(cmd_buffer);
//	HCI::Status GAP::status = 0;
//	int index_input = 0;
//	cp0->Peer_Identity_Address_Type = htob(Peer_Identity_Address_Type, 1);
//	index_input += 1;
//	Osal_MemCpy((void *) &cp0->Peer_Identity_Address, (const void *) Peer_Identity_Address, 6);
//	index_input += 6;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x0aa;
//	rq.cparam = cmd_buffer;
//	rq.clen = index_input;
//	rq.rparam = &status;
//	rq.rlen = 1;
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (status) 
//	{
//		return status;
//	}
//	return BLE_STATUS_SUCCESS;
//}