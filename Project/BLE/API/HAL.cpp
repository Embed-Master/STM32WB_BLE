#include "HAL.hpp"
#include "string.h"

//HCI::Status aci_hal_get_fw_build_number(uint16_t *Build_Number)
//{
//	struct hci_request rq;
//	aci_hal_get_fw_build_number_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x000;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*Build_Number = btoh(resp.Build_Number, 2);
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status HAL::writeConfigData(byte offset, byte length, byte value[])
{
	WriteConfigData cmd;
	cmd.offset = offset;
	cmd.length = length;
	memcpy(cmd.value, value, length);
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1};
	HCI::send((ushort)Opcode::WriteConfigData, &rq, length + 2, (byte *)&cmd);
	return status;
}

//HCI::Status aci_hal_read_config_data(byte Offset,
//	byte *Data_Length,
//	byte Data[])
//{
//	struct hci_request rq;
//	byte buf[BLE_CMD_MAX_PARAM_LEN];
//	aci_hal_read_config_data_cp0 *cp0 = (aci_hal_read_config_data_cp0*)(buf);
//	aci_hal_read_config_data_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	int index_input = 0;
//	cp0->Offset = htob(Offset, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x00d;
//	rq.cparam = buf;
//	rq.clen = index_input;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*Data_Length = btoh(resp.Data_Length, 1);
//	Osal_MemCpy((void *) Data, (const void *) resp.Data, *Data_Length);
//	return BLE_STATUS_SUCCESS;
//}

HCI::Status HAL::setTxPowerLevel(Power level, byte enHighPower)
{
	setTxPowerCom cmd;
	cmd.highPowerEn = enHighPower;
	cmd.power = (byte)level;
	HCI::Status status = HCI::Status::Success;
	HCI::Request rq = { &status, 1 };
	HCI::send((ushort)Opcode::SetTxPower, &rq, sizeof(cmd), (byte *)&cmd);
	return status;
}

//HCI::Status aci_hal_le_tx_test_packet_number(uint32_t *Number_Of_Packets)
//{
//	struct hci_request rq;
//	aci_hal_le_tx_test_packet_number_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x014;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*Number_Of_Packets = btoh(resp.Number_Of_Packets, 4);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status aci_hal_tone_start(byte RF_Channel,
//	byte Freq_offset)
//{
//	struct hci_request rq;
//	byte buf[BLE_CMD_MAX_PARAM_LEN];
//	aci_hal_tone_start_cp0 *cp0 = (aci_hal_tone_start_cp0*)(buf);
//	HCI::Status status = 0;
//	int index_input = 0;
//	cp0->RF_Channel = htob(RF_Channel, 1);
//	index_input += 1;
//	cp0->Freq_offset = htob(Freq_offset, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x015;
//	rq.cparam = buf;
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
//HCI::Status aci_hal_tone_stop(void)
//{
//	struct hci_request rq;
//	HCI::Status status = 0;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x016;
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
//HCI::Status aci_hal_get_link_status(byte Link_Status[8],
//	uint16_t Link_Connection_Handle[16 / 2])
//{
//	struct hci_request rq;
//	aci_hal_get_link_status_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x017;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	Osal_MemCpy((void *) Link_Status, (const void *) resp.Link_Status, 8);
//	Osal_MemCpy((void *) Link_Connection_Handle, (const void *) resp.Link_Connection_Handle, 16);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status aci_hal_set_radio_activity_mask(uint16_t Radio_Activity_Mask)
//{
//	struct hci_request rq;
//	byte buf[BLE_CMD_MAX_PARAM_LEN];
//	aci_hal_set_radio_activity_mask_cp0 *cp0 = (aci_hal_set_radio_activity_mask_cp0*)(buf);
//	HCI::Status status = 0;
//	int index_input = 0;
//	cp0->Radio_Activity_Mask = htob(Radio_Activity_Mask, 2);
//	index_input += 2;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x018;
//	rq.cparam = buf;
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
//HCI::Status aci_hal_get_anchor_period(uint32_t *Anchor_Period,
//	uint32_t *Max_Free_Slot)
//{
//	struct hci_request rq;
//	aci_hal_get_anchor_period_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x019;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*Anchor_Period = btoh(resp.Anchor_Period, 4);
//	*Max_Free_Slot = btoh(resp.Max_Free_Slot, 4);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status aci_hal_set_event_mask(uint32_t Event_Mask)
//{
//	struct hci_request rq;
//	byte buf[BLE_CMD_MAX_PARAM_LEN];
//	aci_hal_set_event_mask_cp0 *cp0 = (aci_hal_set_event_mask_cp0*)(buf);
//	HCI::Status status = 0;
//	int index_input = 0;
//	cp0->Event_Mask = htob(Event_Mask, 4);
//	index_input += 4;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x01a;
//	rq.cparam = buf;
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
//HCI::Status aci_hal_set_smp_eng_config(uint32_t SMP_Config)
//{
//	struct hci_request rq;
//	byte buf[BLE_CMD_MAX_PARAM_LEN];
//	aci_hal_set_smp_eng_config_cp0 *cp0 = (aci_hal_set_smp_eng_config_cp0*)(buf);
//	HCI::Status status = 0;
//	int index_input = 0;
//	cp0->SMP_Config = htob(SMP_Config, 4);
//	index_input += 4;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x01b;
//	rq.cparam = buf;
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
//HCI::Status aci_hal_get_pm_debug_info(byte *Allocated_For_TX,
//	byte *Allocated_For_RX,
//	byte *Allocated_MBlocks)
//{
//	struct hci_request rq;
//	aci_hal_get_pm_debug_info_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x01c;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*Allocated_For_TX = btoh(resp.Allocated_For_TX, 1);
//	*Allocated_For_RX = btoh(resp.Allocated_For_RX, 1);
//	*Allocated_MBlocks = btoh(resp.Allocated_MBlocks, 1);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status aci_hal_read_radio_reg(byte Register_Address,
//	byte *reg_val)
//{
//	struct hci_request rq;
//	byte buf[BLE_CMD_MAX_PARAM_LEN];
//	aci_hal_read_radio_reg_cp0 *cp0 = (aci_hal_read_radio_reg_cp0*)(buf);
//	aci_hal_read_radio_reg_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	int index_input = 0;
//	cp0->Register_Address = htob(Register_Address, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x030;
//	rq.cparam = buf;
//	rq.clen = index_input;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	*reg_val = btoh(resp.reg_val, 1);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status aci_hal_write_radio_reg(byte Register_Address,
//	byte Register_Value)
//{
//	struct hci_request rq;
//	byte buf[BLE_CMD_MAX_PARAM_LEN];
//	aci_hal_write_radio_reg_cp0 *cp0 = (aci_hal_write_radio_reg_cp0*)(buf);
//	HCI::Status status = 0;
//	int index_input = 0;
//	cp0->Register_Address = htob(Register_Address, 1);
//	index_input += 1;
//	cp0->Register_Value = htob(Register_Value, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x031;
//	rq.cparam = buf;
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
//HCI::Status aci_hal_read_raw_rssi(byte Value[3])
//{
//	struct hci_request rq;
//	aci_hal_read_raw_rssi_rp0 resp;
//	Osal_MemSet(&resp, 0, sizeof(resp));
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x032;
//	rq.rparam = &resp;
//	rq.rlen = sizeof(resp);
//	if (hci_send_req(&rq, FALSE) < 0)
//		return BLE_STATUS_TIMEOUT;
//	if (resp.Status) 
//	{
//		return resp.Status;
//	}
//	Osal_MemCpy((void *) Value, (const void *) resp.Value, 3);
//	return BLE_STATUS_SUCCESS;
//}
//
//HCI::Status aci_hal_rx_start(byte RF_Channel)
//{
//	struct hci_request rq;
//	byte buf[BLE_CMD_MAX_PARAM_LEN];
//	aci_hal_rx_start_cp0 *cp0 = (aci_hal_rx_start_cp0*)(buf);
//	HCI::Status status = 0;
//	int index_input = 0;
//	cp0->RF_Channel = htob(RF_Channel, 1);
//	index_input += 1;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x033;
//	rq.cparam = buf;
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
//HCI::Status aci_hal_rx_stop(void)
//{
//	struct hci_request rq;
//	HCI::Status status = 0;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x034;
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
//HCI::Status aci_hal_stack_reset(void)
//{
//	struct hci_request rq;
//	HCI::Status status = 0;
//	Osal_MemSet(&rq, 0, sizeof(rq));
//	rq.ogf = 0x3f;
//	rq.ocf = 0x03b;
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