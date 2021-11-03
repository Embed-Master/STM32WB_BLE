#pragma once

#include "HCI.hpp"

class LE
{
public:
	struct SupportedCommands
	{
		struct _0
		{
			byte HCI_Inquiry : 1;
			byte HCI_Inquiry_Cancel : 1;
			byte HCI_Periodic_Inquiry_Mode : 1;
			byte HCI_Exit_Periodic_Inquiry_Mode : 1;
			byte HCI_Create_Connection : 1;
			byte HCI_Disconnect : 1;
			byte HCI_Add_SCO_Connection_deprecated : 1;
			byte HCI_Create_Connection_Cancel : 1;
		} st_0;
		struct _1
		{
			byte HCI_Accept_Connection_Request : 1;
			byte HCI_Reject_Connection_Request : 1;
			byte HCI_Link_Key_Request_Reply : 1;
			byte HCI_Link_Key_Request_Negative_Reply : 1;
			byte HCI_PIN_Code_Request_Reply : 1;
			byte HCI_PIN_Code_Request_Negative_Reply : 1;
			byte HCI_Change_Connection_Packet_Type : 1;
			byte HCI_Authentication_Requested : 1;
		} st_1;
		struct _2
		{
			byte HCI_Set_Connection_Encryption : 1;
			byte HCI_Change_Connection_Link_Key : 1;
			byte HCI_Master_Link_Key : 1;
			byte HCI_Remote_Name_Request : 1;
			byte HCI_Remote_Name_Request_Cancel : 1;
			byte HCI_Read_Remote_Supported_Features : 1;
			byte HCI_Read_Remote_Extended_Features : 1;
			byte HCI_Read_Remote_Version_Information : 1;
		} st_2;
		struct _3
		{
			byte HCI_Read_Clock_Offset : 1;
			byte HCI_Read_LMP_Handle : 1;
			byte Reserved_for_future_use : 6;
		} st_3;
		struct _4
		{
			byte Reserved_for_future_use : 1;
			byte HCI_Hold_Mode : 1;
			byte HCI_Sniff_Mode : 1;
			byte HCI_Exit_Sniff_Mode : 1;
			byte Previously_used1 : 1;
			byte Previously_used2 : 1;
			byte HCI_QoS_Setup : 1;
			byte HCI_Role_Discovery : 1;
		} st_4;
		struct _5
		{
			byte HCI_Switch_Role : 1;
			byte HCI_Read_Link_Policy_Settings : 1;
			byte HCI_Write_Link_Policy_Settings : 1;
			byte HCI_Read_Default_Link_Policy_Settings : 1;
			byte HCI_Write_Default_Link_Policy_Settings : 1;
			byte HCI_Flow_Specification : 1;
			byte HCI_Set_Event_Mask : 1;
			byte HCI_Reset : 1;
		} st_5;
		struct _6
		{
			byte HCI_Set_Event_Filter : 1;
			byte HCI_Flush : 1;
			byte HCI_Read_PIN_Type : 1;
			byte HCI_Write_PIN_Type : 1;
			byte Previously_used : 1;
			byte HCI_Read_Stored_Link_Key : 1;
			byte HCI_Write_Stored_Link_Key : 1;
			byte HCI_Delete_Stored_Link_Key : 1;
		} st_6;
		struct _7
		{
			byte HCI_Write_Local_Name : 1;
			byte HCI_Read_Local_Name : 1;
			byte HCI_Read_Connection_Accept_Timeout : 1;
			byte HCI_Write_Connection_Accept_Timeout : 1;
			byte HCI_Read_Page_Timeout : 1;
			byte HCI_Write_Page_Timeout : 1;
			byte HCI_Read_Scan_Enable : 1;
			byte HCI_Write_Scan_Enable : 1;
		} st_7;
		struct _8
		{
			byte HCI_Read_Page_Scan_Activity : 1;
			byte HCI_Write_Page_Scan_Activity : 1;
			byte HCI_Read_Inquiry_Scan_Activity : 1;
			byte HCI_Write_Inquiry_Scan_Activity : 1;
			byte HCI_Read_Authentication_Enable : 1;
			byte HCI_Write_Authentication_Enable : 1;
			byte HCI_Read_Encryption_Mode_deprecated : 1;
			byte HCI_Write_Encryption_Mode_deprecated : 1;
		} st_8;
		struct _9
		{
			byte HCI_Read_Class_Of_Device : 1;
			byte HCI_Write_Class_Of_Device : 1;
			byte HCI_Read_Voice_Setting : 1;
			byte HCI_Write_Voice_Setting : 1;
			byte HCI_Read_Automatic_Flush_Timeout : 1;
			byte HCI_Write_Automatic_Flush_Timeout : 1;
			byte HCI_Read_Num_Broadcast_Retransmissions : 1;
			byte HCI_Write_Num_Broadcast_Retransmissions : 1;
		} st_9;
		struct _10
		{
			byte HCI_Read_Hold_Mode_Activity : 1;
			byte HCI_Write_Hold_Mode_Activity : 1;
			byte HCI_Read_Transmit_Power_Level : 1;
			byte HCI_Read_Synchronous_Flow_Control_Enable : 1;
			byte HCI_Write_Synchronous_Flow_Control_Enable : 1;
			byte HCI_Set_Controller_To_Host_Flow_Control : 1;
			byte HCI_Host_Buffer_Size : 1;
			byte HCI_Host_Number_Of_Completed_Packets : 1;
		} st_10;
		struct _11
		{
			byte HCI_Read_Link_Supervision_Timeout : 1;
			byte HCI_Write_Link_Supervision_Timeout : 1;
			byte HCI_Read_Number_Of_Supported_IAC : 1;
			byte HCI_Read_Current_IAC_LAP : 1;
			byte HCI_Write_Current_IAC_LAP : 1;
			byte HCI_Read_Page_Scan_Mode_Period_deprecated : 1;
			byte HCI_Write_Page_Scan_Mode_Period_deprecated : 1;
			byte HCI_Read_Page_Scan_Mode_deprecated : 1;
		} st_11;
		struct _12
		{
			byte HCI_Write_Page_Scan_Mode_deprecated : 1;
			byte HCI_Set_AFH_Host_Channel_Classification : 1;
			byte Reserved_for_future_use : 2;
			byte HCI_Read_Inquiry_Scan_Type : 1;
			byte HCI_Write_Inquiry_Scan_Type : 1;
			byte HCI_Read_Inquiry_Mode : 1;
			byte HCI_Write_Inquiry_Mode : 1;
		} st_12;
		struct _13
		{
			byte HCI_Read_Page_Scan_Type : 1;
			byte HCI_Write_Page_Scan_Type : 1;
			byte HCI_Read_AFH_Channel_Assessment_Mode : 1;
			byte HCI_Write_AFH_Channel_Assessment_Mode : 1;
			byte Reserved_for_future_use : 4;
		} st_13;
		struct _14
		{
			byte Reserved_for_future_use : 3;
			byte HCI_Read_Local_Version_Information : 1;
			byte Reserved_for_future_use2 : 1;
			byte HCI_Read_Local_Supported_Features : 1;
			byte HCI_Read_Local_Extended_Features : 1;
			byte HCI_Read_Buffer_Size : 1;
		} st_14;
		struct _15
		{
			byte HCI_Read_Country_Code_deprecated : 1;
			byte HCI_Read_BD_ADDR : 1;
			byte HCI_Read_Failed_Contact_Counter : 1;
			byte HCI_Reset_Failed_Contact_Counter : 1;
			byte HCI_Read_Link_Quality : 1;
			byte HCI_Read_RSSI : 1;
			byte HCI_Read_AFH_Channel_Map : 1;
			byte HCI_Read_Clock : 1;
		} st_15;
		struct _16
		{
			byte HCI_Read_Loopback_Mode : 1;
			byte HCI_Write_Loopback_Mode : 1;
			byte HCI_Enable_Device_Under_Test_Mode : 1;
			byte HCI_Setup_Synchronous_Connection_Request : 1;
			byte HCI_Accept_Synchronous_Connection_Request : 1;
			byte HCI_Reject_Synchronous_Connection_Request : 1;
			byte Reserved_for_future_use : 2;
		} st_16;
		struct _17
		{
			byte HCI_Read_Extended_Inquiry_Response : 1;
			byte HCI_Write_Extended_Inquiry_Response : 1;
			byte HCI_Refresh_Encryption_Key : 1;
			byte Reserved_for_future_use : 1;
			byte HCI_Sniff_Subrating : 1;
			byte HCI_Read_Simple_Pairing_Mode : 1;
			byte HCI_Write_Simple_Pairing_Mode : 1;
			byte HCI_Read_Local_OOB_Data : 1;
		} st_17;
		struct _18
		{
			byte HCI_Read_Inquiry_Response_Transmit_Power_Level : 1;
			byte HCI_Write_Inquiry_Transmit_Power_Level : 1;
			byte HCI_Read_Default_Erroneous_Data_Reporting : 1;
			byte HCI_Write_Default_Erroneous_Data_Reporting : 1;
			byte Reserved_for_future_use : 3;
			byte HCI_IO_Capability_Request_Reply : 1;
		} st_18;
		struct _19
		{
			byte HCI_User_Confirmation_Request_Reply : 1;
			byte HCI_User_Confirmation_Request_Negative_Reply : 1;
			byte HCI_User_Passkey_Request_Reply : 1;
			byte HCI_User_Passkey_Request_Negative_Reply : 1;
			byte HCI_Remote_OOB_Data_Request_Reply : 1;
			byte HCI_Write_Simple_Pairing_Debug_Mode : 1;
			byte HCI_Enhanced_Flush : 1;
			byte HCI_Remote_OOB_Data_Request_Negative_Reply : 1;
		} st_19;
		struct _20
		{
			byte Reserved_for_future_use : 2;
			byte HCI_Send_Keypress_Notification : 1;
			byte HCI_IO_Capability_Request_Negative_Reply : 1;
			byte HCI_Read_Encryption_Key_Size : 1;
			byte Reserved_for_future_use2 : 3;
		} st_20;
		struct _21
		{
			byte HCI_Create_Physical_Link : 1;
			byte HCI_Accept_Physical_Link : 1;
			byte HCI_Disconnect_Physical_Link : 1;
			byte HCI_Create_Logical_Link : 1;
			byte HCI_Accept_Logical_Link : 1;
			byte HCI_Disconnect_Logical_Link : 1;
			byte HCI_Logical_Link_Cancel : 1;
			byte HCI_Flow_Spec_Modify : 1;
		} st_21;
		struct _22
		{
			byte HCI_Read_Logical_Link_Accept_Timeout : 1;
			byte HCI_Write_Logical_Link_Accept_Timeout : 1;
			byte HCI_Set_Event_Mask_Page_2 : 1;
			byte HCI_Read_Location_Data : 1;
			byte HCI_Write_Location_Data : 1;
			byte HCI_Read_Local_AMP_Info : 1;
			byte HCI_Read_Local_AMP_ASSOC : 1;
			byte HCI_Write_Remote_AMP_ASSOC : 1;
		} st_22;
		struct _23
		{
			byte HCI_Read_Flow_Control_Mode : 1;
			byte HCI_Write_Flow_Control_Mode : 1;
			byte HCI_Read_Data_Block_Size : 1;
			byte Reserved_for_future_use : 2;
			byte HCI_Enable_AMP_Receiver_Reports : 1;
			byte HCI_AMP_Test_End : 1;
			byte HCI_AMP_Test : 1;
		} st_23;
		struct _24
		{
			byte HCI_Read_Enhanced_Transmit_Power_Level : 1;
			byte Reserved_for_future_use : 1;
			byte HCI_Read_Best_Effort_Flush_Timeout : 1;
			byte HCI_Write_Best_Effort_Flush_Timeout : 1;
			byte HCI_Short_Range_Mode : 1;
			byte HCI_Read_LE_Host_Support : 1;
			byte HCI_Write_LE_Host_Support : 1;
			byte Reserved_for_future_use2 : 1;
		} st_24;
		struct _25
		{
			byte HCI_LE_Set_Event_Mask : 1;
			byte HCI_LE_Read_Buffer_Size_v1 : 1;
			byte HCI_LE_Read_Local_Supported_Features : 1;
			byte Reserved_for_future_use : 1;
			byte HCI_LE_Set_Random_Address : 1;
			byte HCI_LE_Set_Advertising_Parameters : 1;
			byte HCI_LE_Read_Advertising_Physical_Channel_Tx_Power : 1;
			byte HCI_LE_Set_Advertising_Data : 1;
		} st_25;
		struct _26
		{
			byte HCI_LE_Set_Scan_Response_Data : 1;
			byte HCI_LE_Set_Advertising_Enable : 1;
			byte HCI_LE_Set_Scan_Parameters : 1;
			byte HCI_LE_Set_Scan_Enable : 1;
			byte HCI_LE_Create_Connection : 1;
			byte HCI_LE_Create_Connection_Cancel : 1;
			byte HCI_LE_Read_White_List_Size : 1;
			byte HCI_LE_Clear_White_List : 1;
		} st_26;
		struct _27
		{
			byte HCI_LE_Add_Device_To_White_List : 1;
			byte HCI_LE_Remove_Device_From_White_List : 1;
			byte HCI_LE_Connection_Update : 1;
			byte HCI_LE_Set_Host_Channel_Classification : 1;
			byte HCI_LE_Read_Channel_Map : 1;
			byte HCI_LE_Read_Remote_Features : 1;
			byte HCI_LE_Encrypt : 1;
			byte HCI_LE_Rand : 1;
		} st_27;
		struct _28
		{
			byte HCI_LE_Enable_Encryption : 1;
			byte HCI_LE_Long_Term_Key_Request_Reply : 1;
			byte HCI_LE_Long_Term_Key_Request_Negative_Reply : 1;
			byte HCI_LE_Read_Supported_States : 1;
			byte HCI_LE_Receiver_Test_v1 : 1;
			byte HCI_LE_Transmitter_Test_v1 : 1;
			byte HCI_LE_Test_End : 1;
			byte Reserved_for_future_use : 1;
		} st_28;
		struct _29
		{
			byte Reserved_for_future_use : 3;
			byte HCI_Enhanced_Setup_Synchronous_Connection : 1;
			byte HCI_Enhanced_Accept_Synchronous_Connection : 1;
			byte HCI_Read_Local_Supported_Codecs : 1;
			byte HCI_Set_MWS_Channel_Parameters : 1;
			byte HCI_Set_External_Frame_Configuration : 1;
		} st_29;
		struct _30
		{
			byte HCI_Set_MWS_Signaling : 1;
			byte HCI_Set_MWS_Transport_Layer : 1;
			byte HCI_Set_MWS_Scan_Frequency_Table : 1;
			byte HCI_Get_MWS_Transport_Layer_Configuration : 1;
			byte HCI_Set_MWS_PATTERN_Configuration : 1;
			byte HCI_Set_Triggered_Clock_Capture : 1;
			byte HCI_Truncated_Page : 1;
			byte HCI_Truncated_Page_Cancel : 1;
		} st_30;
		struct _31
		{
			byte HCI_Set_Connectionless_Slave_Broadcast : 1;
			byte HCI_Set_Connectionless_Slave_Broadcast_Receive : 1;
			byte HCI_Start_Synchronization_Train : 1;
			byte HCI_Receive_Synchronization_Train : 1;
			byte HCI_Set_Reserved_LT_ADDR : 1;
			byte HCI_Delete_Reserved_LT_ADDR : 1;
			byte HCI_Set_Connectionless_Slave_Broadcast_Data : 1;
			byte HCI_Read_Synchronization_Train_Parameters : 1;
		} st_31;
		struct _32
		{
			byte HCI_Write_Synchronization_Train_Parameters : 1;
			byte HCI_Remote_OOB_Extended_Data_Request_Reply : 1;
			byte HCI_Read_Secure_Connections_Host_Support : 1;
			byte HCI_Write_Secure_Connections_Host_Support : 1;
			byte HCI_Read_Authenticated_Payload_Timeout : 1;
			byte HCI_Write_Authenticated_Payload_Timeout : 1;
			byte HCI_Read_Local_OOB_Extended_Data : 1;
			byte HCI_Write_Secure_Connections_Test_Mode : 1;
		} st_32;
		struct _33
		{
			byte HCI_Read_Extended_Page_Timeout : 1;
			byte HCI_Write_Extended_Page_Timeout : 1;
			byte HCI_Read_Extended_Inquiry_Length : 1;
			byte HCI_Write_Extended_Inquiry_Length : 1;
			byte HCI_LE_Remote_Connection_Parameter_Request_Reply : 1;
			byte HCI_LE_Remote_Connection_Parameter_Request_Negative_Reply : 1;
			byte HCI_LE_Set_Data_Length : 1;
			byte HCI_LE_Read_Suggested_Default_Data_Length : 1;
		} st_33;
		struct _34
		{
			byte HCI_LE_Write_Suggested_Default_Data_Length : 1;
			byte HCI_LE_Read_Local_P256_Public_Key : 1;
			byte HCI_LE_Generate_DHKey_v1 : 1;
			byte HCI_LE_Add_Device_To_Resolving_List : 1;
			byte HCI_LE_Remove_Device_From_Resolving_List : 1;
			byte HCI_LE_Clear_Resolving_List : 1;
			byte HCI_LE_Read_Resolving_List_Size : 1;
			byte HCI_LE_Read_Peer_Resolvable_Address : 1;
		} st_34;
		struct _35
		{
			byte HCI_LE_Read_Local_Resolvable_Address : 1;
			byte HCI_LE_Set_Address_Resolution_Enable : 1;
			byte HCI_LE_Set_Resolvable_Private_Address_Timeout : 1;
			byte HCI_LE_Read_Maximum_Data_Length : 1;
			byte HCI_LE_Read_PHY : 1;
			byte HCI_LE_Set_Default_PHY : 1;
			byte HCI_LE_Set_PHY : 1;
			byte HCI_LE_Receiver_Test_v2 : 1;
		} st_35;
		struct _36
		{
			byte HCI_LE_Transmitter_Test_v2 : 1;
			byte HCI_LE_Set_Advertising_Set_Random_Address : 1;
			byte HCI_LE_Set_Extended_Advertising_Parameters : 1;
			byte HCI_LE_Set_Extended_Advertising_Data : 1;
			byte HCI_LE_Set_Extended_Scan_Response_Data : 1;
			byte HCI_LE_Set_Extended_Advertising_Enable : 1;
			byte HCI_LE_Read_Maximum_Advertising_Data_Length : 1;
			byte HCI_LE_Read_Number_of_Supported_Advertising_Sets : 1;
		} st_36;
		struct _37
		{
			byte HCI_LE_Remove_Advertising_Set : 1;
			byte HCI_LE_Clear_Advertising_Sets : 1;
			byte HCI_LE_Set_Periodic_Advertising_Parameters : 1;
			byte HCI_LE_Set_Periodic_Advertising_Data : 1;
			byte HCI_LE_Set_Periodic_Advertising_Enable : 1;
			byte HCI_LE_Set_Extended_Scan_Parameters : 1;
			byte HCI_LE_Set_Extended_Scan_Enable : 1;
			byte HCI_LE_Extended_Create_Connection : 1;
		} st_37;
		struct _38
		{
			byte HCI_LE_Periodic_Advertising_Create_Sync : 1;
			byte HCI_LE_Periodic_Advertising_Create_Sync_Cancel : 1;
			byte HCI_LE_Periodic_Advertising_Terminate_Sync : 1;
			byte HCI_LE_Add_Device_To_Periodic_Advertiser_List : 1;
			byte HCI_LE_Remove_Device_From_Periodic_Advertiser_List : 1;
			byte HCI_LE_Clear_Periodic_Advertiser_List : 1;
			byte HCI_LE_Read_Periodic_Advertiser_List_Size : 1;
			byte HCI_LE_Read_Transmit_Power : 1;
		} st_38;
		struct _39
		{
			byte HCI_LE_Read_RF_Path_Compensation : 1;
			byte HCI_LE_Write_RF_Path_Compensation : 1;
			byte HCI_LE_Set_Privacy_Mode : 1;
			byte HCI_LE_Receiver_Test_v3 : 1;
			byte HCI_LE_Transmitter_Test_v3 : 1;
			byte HCI_LE_Set_Connectionless_CTE_Transmit_Parameters : 1;
			byte HCI_LE_Set_Connectionless_CTE_Transmit_Enable : 1;
			byte HCI_LE_Set_Connectionless_IQ_Sampling_Enable : 1;
		} st_39;
		struct _40
		{
			byte HCI_LE_Set_Connection_CTE_Receive_Parameters : 1;
			byte HCI_LE_Set_Connection_CTE_Transmit_Parameters : 1;
			byte HCI_LE_Connection_CTE_Request_Enable : 1;
			byte HCI_LE_Connection_CTE_Response_Enable : 1;
			byte HCI_LE_Read_Antenna_Information : 1;
			byte HCI_LE_Set_Periodic_Advertising_Receive_Enable : 1;
			byte HCI_LE_Periodic_Advertising_Sync_Transfer : 1;
			byte HCI_LE_Periodic_Advertising_Set_Info_Transfer : 1;
		} st_40;
		struct _41
		{
			byte HCI_LE_Set_Periodic_Advertising_Sync_Transfer_Parameters : 1;
			byte HCI_LE_Set_Default_Periodic_Advertising_Sync_Transfer_Parameters : 1;
			byte HCI_LE_Generate_DHKey_v2 : 1;
			byte HCI_Read_Local_Simple_Pairing_Options : 1;
			byte HCI_LE_Modify_Sleep_Clock_Accuracy : 1;
			byte HCI_LE_Read_Buffer_Size_v2 : 1;
			byte HCI_LE_Read_ISO_TX_Sync : 1;
			byte HCI_LE_Set_CIG_Parameters : 1;
		} st_41;
		struct _42
		{
			byte HCI_LE_Set_CIG_Parameters_Test : 1;
			byte HCI_LE_Create_CIS : 1;
			byte HCI_LE_Remove_CIG : 1;
			byte HCI_LE_Accept_CIS_Request : 1;
			byte HCI_LE_Reject_CIS_Request : 1;
			byte HCI_LE_Create_BIG : 1;
			byte HCI_LE_Create_BIG_Test : 1;
			byte HCI_LE_Terminate_BIG : 1;
		} st_42;
		struct _43
		{
			byte HCI_LE_BIG_Create_Sync : 1;
			byte HCI_LE_BIG_Terminate_Sync : 1;
			byte HCI_LE_Request_Peer_SCA : 1;
			byte HCI_LE_Setup_ISO_Data_Path : 1;
			byte HCI_LE_Remove_ISO_Data_Path : 1;
			byte HCI_LE_ISO_Transmit_Test : 1;
			byte HCI_LE_ISO_Receive_Test : 1;
			byte HCI_LE_ISO_Read_Test_Counters : 1;
		} st_43;
		struct _44
		{
			byte HCI_LE_ISO_Test_End : 1;
			byte HCI_LE_Set_Host_Feature : 1;
			byte HCI_LE_Read_ISO_Link_Quality : 1;
			byte HCI_LE_Enhanced_Read_Transmit_Power_Level : 1;
			byte HCI_LE_Read_Remote_Transmit_Power_Level : 1;
			byte HCI_LE_Set_Path_Loss_Reporting_Parameters : 1;
			byte HCI_LE_Set_Path_Loss_Reporting_Enable : 1;
			byte HCI_LE_Set_Transmit_Power_Reporting_Enable : 1;
		} st_44;
		struct _45
		{
			byte HCI_LE_Transmitter_Test_v4 : 1;
			byte HCI_Set_Ecosystem_Base_Interval : 1;
			byte HCI_Read_Local_Supported_Codecs_v2 : 1;
			byte HCI_Read_Local_Supported_Codec_Capabilities : 1;
			byte HCI_Read_Local_Supported_Controller_Delay : 1;
			byte HCI_Configure_Data_Path : 1;
			byte Reserved_for_future_use : 2;
		} st_45;
	};
	struct Disconnect
	{
		struct Com0
		{
			ushort handle;
			byte reason;
		} __attribute__((packed));
		enum class Reason : byte
		{
			AuthenticationFailure = 0x05,
			RemoteUserTerminatedConnection = 0x13,
			RemoteDeviceTerminatedConnectionDueToLowResources = 0x14,
			RemoteDeviceTerminatedConnectionDueToPowerOff = 0x15,
			UnsupportedRemoteFeature = 0x1A,
			UnacceptableConnectionParameters = 0x3B
		};
	};
	
private:
	enum class Opcode : ushort
	{
		Disconnect = 0x0406,
		Reset = 0x0C03,
		ReadLocalSupportedCommands = 0x1002,
		SetDefaultPhy = 0x2031,
		ReadPhy = 0x2030,
		ReadRSSI = 0x1405
	};
	struct ReadLocalSupportedCommands
	{
		struct Response
		{
			HCI::Status status;
			SupportedCommands commands;
		} __attribute__((packed));
	};
	struct SetDefaultPhy
	{
		byte all;
		byte tx;
		byte rx;
	} __attribute__((packed));
	struct ReadPhy
	{
		struct Com0
		{
			ushort handle;
		} __attribute__((packed));
		struct Response
		{
			HCI::Status status;
			ushort handle;
			byte txPhy;
			byte rxPhy;
		} __attribute__((packed));
	};
	struct ReadRssi
	{
		struct Com0
		{
			ushort handle;
		} __attribute__((packed));
		struct Response
		{
			HCI::Status status;
			ushort handle;
			signed char rssi;
		} __attribute__((packed));
	};
	
public:
	/**
	  * @brief The @ref disconnect is used to terminate an existing connection. The
	Connection_Handle command parameter indicates which connection is to be
	disconnected. The Reason command parameter indicates the reason for ending
	the connection. The remote Controller will receive the Reason command
	parameter in the @ref disconnection_complete_event event. All synchronous connections
	on a physical link should be disconnected before the ACL connection on the
	same physical connection is disconnected.
	(See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.1.6)
	It is important to leave an 100 ms blank window before sending any new command (including system hardware reset),
	since immediately after @ref disconnection_complete_event event, system could save important information in non volatile memory.
	  * @param Connection_Handle Connection handle for which the command is given.
	  * Values:
	  - 0x0000 ... 0x0EFF
	  * @param Reason The reason for ending the connection.
	  * Values:
	  - 0x05: Authentication Failure
	  - 0x13: Remote User Terminated Connection
	  - 0x14: Remote Device Terminated Connection due to Low Resources
	  - 0x15: Remote Device Terminated Connection due to Power Off
	  - 0x1A: Unsupported Remote Feature
	  - 0x3B: Unacceptable Connection Parameters
	  * @retval Value indicating success or error code.
	*/
	static HCI::Status disconnect(ushort handle, Disconnect::Reason reason);

//	/**
//	  * @brief This command will obtain the values for the version information for the remote
//	  device identified by the Connection_Handle parameter. The Connection_Handle
//	  must be a Connection_Handle for an ACL or LE connection.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.1.23)
//	    * @param Connection_Handle Specifies which Connection_Handle's version information to get.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status readRemoteVersionInformation(ushort handle);
//
//	/**
//	  * @brief The Set_Event_Mask command is used to control which events are generated
//	  by the HCI for the Host.
//
//	  If the bit in the Event_Mask is set to a one, then the
//	  event associated with that bit will be enabled. For an LE Controller, the LE
//	  Meta Event bit in the Event_Mask shall enable or disable all LE events in the
//	  LE Meta Event (see Section 7.7.65). The Host has to deal with each event that
//	  occurs. The event mask allows the Host to control how much it is interrupted.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.3.1)
//	    * @param Event_Mask Event mask. Default: 0x20001FFFFFFFFFFF
//	    * Flags:
//	    - 0x0000000000000000: No events specified
//	    - 0x0000000000000010: Disconnection Complete Event
//	    - 0x0000000000000080: Encryption Change Event
//	    - 0x0000000000000800: Read Remote Version Information Complete Event
//	    - 0x0000000000008000: Hardware Error Event
//	    - 0x0000800000000000: Encryption Key Refresh Complete Event
//	    - 0x2000000000000000: LE Meta-Event
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status setEventMask(byte mask[8]);
//
	/**
	  * @brief The Reset command will reset the Link Layer on an LE
	  Controller.

	  The Reset command shall not affect the used HCI transport layer since the HCI transport
	  layers may have reset mechanisms of their own. After the reset is completed,
	  the current operational state will be lost, the Controller will enter standby mode
	  and the Controller will automatically revert to the default values for the parameters
	  for which default values are defined in the specification.
	  Note: The Reset command will not necessarily perform a hardware reset. This
	  is implementation defined. 
	  The Host shall not send additional HCI commands before the Command Complete
	  event related to the Reset command has been received.
	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.3.2)
	    * @retval Value indicating success or error code.
	    */
	static HCI::Status reset();
//
//	/**
//	  * @brief This command reads the values for the Transmit_Power_Level parameter for
//	  the specified Connection_Handle. The Connection_Handle shall be a Connection_Handle
//	  for an ACL connection.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.3.35)
//	    * @param Connection_Handle Specifies which Connection_Handle's Transmit Power Level setting to read.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @param Type Current or maximum transmit power level.
//	    * Values:
//	    - 0x00: Read Current Transmit Power Level.
//	    - 0x01: Read Maximum Transmit Power Level.
//	    * @param[out] Transmit_Power_Level Size: 1 Octet (signed integer)
//	    Units: dBm
//	      * Values:
//	      - -30 ... 20
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status readTransmitPowerLevel(ushort handle, byte type, byte *level);
//
//	/**
//	  * @brief This command is used by the Host to turn flow control on or off for data and/or
//	  voice sent in the direction from the Controller to the Host. If flow control is turned
//	  off, the Host should not send the Host_Number_Of_Completed_Packets
//	  command. That command will be ignored by the Controller if it is sent by the
//	  Host and flow control is off. If flow control is turned on for HCI ACL Data Packets
//	  and off for HCI synchronous Data Packets,
//	  Host_Number_Of_Completed_Packets commands sent by the Host should only
//	  contain Connection_Handles for ACL connections. If flow control is turned off for
//	  HCI ACL Data Packets and on for HCI synchronous Data Packets,
//	  Host_Number_Of_Completed_Packets commands sent by the Host should only
//	  contain Connection_Handles for synchronous connections. If flow control is
//	  turned on for HCI ACL Data Packets and HCI synchronous Data Packets, the
//	  Host will send Host_Number_Of_Completed_Packets commands both for ACL
//	  connections and synchronous connections.
//	  The Flow_Control_Enable parameter shall only be changed if no connections
//	  exist. See Bluetooth Spec v.5.0, Vol. 2, Part E, 7.3.38
//	    * @param Flow_Control_Enable Enable/Disable the Flow Control
//	    * Values:
//	    - 0x00: Flow control off in direction from Controller to Host. Default.
//	    - 0x01: Flow control on for HCI ACL Data Packets and off for HCI synchronous.Data Packets in direction from Controller to Host.
//	    - 0x02: Flow control off for HCI ACL Data Packets and on for HCI synchronous.Data Packets in direction from Controller to Host.
//	    - 0x03: Flow control on both for HCI ACL Data Packets and HCI synchronous.Data Packets in direction from Controller to Host.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status setControllerToHostFlowControl(byte enable);
//
//	/**
//	  * @brief The Host_Buffer_Size command is used by the Host to notify the Controller
//	  about the maximum size of the data portion of HCI ACL and synchronous Data
//	  Packets sent from the Controller to the Host. The Controller shall segment the
//	  data to be transmitted from the Controller to the Host according to these sizes,
//	  so that the HCI Data Packets will contain data with up to these sizes. The
//	  Host_Buffer_Size command also notifies the Controller about the total number
//	  of HCI ACL and synchronous Data Packets that can be stored in the data
//	  buffers of the Host. If flow control from the Controller to the Host is turned off,
//	  and the Host_Buffer_Size command has not been issued by the Host, this
//	  means that the Controller will send HCI Data Packets to the Host with any
//	  lengths the Controller wants to use, and it is assumed that the data buffer sizes
//	  of the Host are unlimited. If flow control from the Controller to the Host is turned
//	  on, the Host_Buffer_Size command shall after a power-on or a reset always be
//	  sent by the Host before the first Host_Number_Of_Completed_Packets
//	  command is sent.
//	  The Set Controller To Host Flow Control Command is used to turn flow control
//	  on or off. The Host_ACL_Data_Packet_Length command parameter will be
//	  used to determine the size of the L2CAP segments contained in ACL Data
//	  Packets, which are transferred from the Controller to the Host. The
//	  Host_Synchronous_Data_Packet_Length command parameter is used to
//	  determine the maximum size of HCI synchronous Data Packets. Both the Host
//	  and the Controller shall support command and event packets, where the data
//	  portion (excluding header) contained in the packets is 255 octets in size.
//	  The Host_Total_Num_ACL_Data_Packets command parameter contains the
//	  total number of HCI ACL Data Packets that can be stored in the data buffers of
//	  the Host. The Controller will determine how the buffers are to be divided
//	  between different Connection_Handles. The Host_Total_Num_Synchronous_
//	  Data_Packets command parameter gives the same information for HCI
//	  synchronous Data Packets.
//	  Note: The Host_ACL_Data_Packet_Length and Host_Synchronous_Data_
//	  Packet_Length command parameters do not include the length of the HCI Data
//	  Packet header. See Bluetooth Spec v.5.0, Vol. 2, Part E, 7.3.39
//	    * @param Host_ACL_Data_Packet_Length Maximum length (in octets) of the data portion of each HCI ACL Data Packet that the Host is able to accept. Must be greater or equal to 251 bytes
//	    * @param Host_Synchronous_Data_Packet_Length Maximum length (in octets) of the data portion of each HCI synchronous Data Packet that the Host is able to accept.
//	    * @param Host_Total_Num_ACL_Data_Packets Total number of HCI ACL Data Packets that can be stored in the data buffers of the Host.
//	    * @param Host_Total_Num_Synchronous_Data_Packets Total number of HCI synchronous Data Packets that can be stored in the data buffers of the Host.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status hostBufferSize(ushort aclDataPacketLength, byte hostSynchronousDataPacketLength, ushort hostTotalNumACLdataPackets, ushort hostTotalNumSynchronousDataPackets);
//
//	/**
//	  * @brief The Host_Number_Of_Completed_Packets command is used by the Host to
//	  indicate to the Controller the number of HCI Data Packets that have been
//	  completed for each Connection_Handle since the previous Host_Number_Of_
//	  Completed_Packets command was sent to the Controller. This means that the
//	  corresponding buffer space has been freed in the Host. Based on this
//	  information, and the Host_Total_Num_ACL_Data_Packets and
//	  Host_Total_Num_Synchronous_Data_Packets command parameters of the
//	  Host_Buffer_Size command, the Controller can determine for which
//	  Connection_Handles the following HCI Data Packets should be sent to the
//	  Host. The command should only be issued by the Host if flow control in the
//	  direction from the Controller to the Host is on and there is at least one
//	  connection, or if the Controller is in local loopback mode. Otherwise, the
//	  command will be ignored by the Controller. When the Host has completed one
//	  or more HCI Data Packet(s) it shall send a
//	  Host_Number_Of_Completed_Packets command to the Controller, until it
//	  finally reports that all pending HCI Data Packets have been completed. The
//	  frequency at which this command is sent is manufacturer specific.
//	  The Set Controller To Host Flow Control Command is used to turn flow control on
//	  or off. If flow control from the Controller to the Host is turned on, the
//	  Host_Buffer_Size command shall always be sent by the Host after a power-on or
//	  a reset before the first Host_Number_Of_Completed_Packets command is sent.
//	  Note: The Host_Number_Of_Completed_Packets command is a special
//	  command in the sense that no event is normally generated after the command
//	  has completed. The command may be sent at any time by the Host when there
//	  is at least one connection, or if the Controller is in local loopback mode
//	  independent of other commands. The normal flow control for commands is not
//	  used for the Host_Number_Of_Completed_Packets command. See Bluetooth Spec v.5.0, Vol. 2, Part E, 7.3.40
//	    * @param Number_Of_Handles The number of Connection_Handles and Host_Num_Of_Completed_Packets
//	    parameters pairs contained in this command.
//	      * Values:
//	      - 0 ... 255
//	      * @param Host_Nb_Of_Completed_Pkt_Pair See @ref Host_Nb_Of_Completed_Pkt_Pair_t
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status hostNumberOfCompletedPackets(byte numberOfHandles, Host_Nb_Of_Completed_Pkt_Pair_t hostNumberOfCompletedPktPair[]);
//
//	/**
//	  * @brief This command reads the values for the version information for the local Controller.
//	  The HCI Version information defines the version information of the HCI layer.
//	  The LMP/PAL Version information defines the version of the LMP or PAL. The
//	  Manufacturer_Name information indicates the manufacturer of the local device.
//	  The HCI Revision and LMP/PAL Subversion are implementation dependent.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.4.1)
//	    * @param[out] HCI_Version See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
//	    * @param[out] HCI_Revision Revision of the Current HCI in the BR/EDR Controller.
//	    * @param[out] LMP_PAL_Version Version of the Current LMP or PAL in the Controller.
//	    See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
//	      * @param[out] Manufacturer_Name Manufacturer Name of the BR/EDR Controller.
//	      See Bluetooth Assigned Numbers (https://www.bluetooth.org/en-us/specification/assigned-numbers)
//	        * @param[out] LMP_PAL_Subversion Subversion of the Current LMP or PAL in the Controller. This value is
//	        implementation dependent.
//	          * @retval Value indicating success or error code.
//	          */
//	static HCI::Status readLocalVersionInformation(byte *version, ushort *revision, byte *LMP_PALversion, ushort *manufacturerName, ushort *LMP_PALsubversion);
//
	/**
	  * @brief This command reads the list of HCI commands supported for the local Controller.
	  This command shall return the Supported_Commands configuration parameter.
	  It is implied that if a command is listed as supported, the feature underlying
	  that command is also supported.
	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.4.2)
	    * @param[out] Supported_Commands Bit mask for each HCI Command. If a bit is 1, the Controller supports the
	    corresponding command and the features required for the command.
	    Unsupported or undefined commands shall be set to 0.
	      * @retval Value indicating success or error code.
	      */
	static HCI::Status readLocalSupportedCommands(SupportedCommands &commands);
//
//	/**
//	  * @brief This command requests a list of the supported features for the local 
//	  Controller. This command will return a list of the LMP features. For details see
//	  Part C, Link Manager Protocol Specification on page 227.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.4.3)
//	    * @param[out] LMP_Features Bit Mask List of LMP features.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status readLocalSupportedFeatures(byte LMPfeatures[8]);
//
//	/**
//	  * @brief On an LE Controller, this command shall read the Public Device Address as
//	  defined in [Vol 6] Part B, Section 1.3, Device Address. If this Controller does
//	  not have a Public Device Address, the value 0x000000000000 shall be
//	  returned.
//	  On an LE Controller, the public address shall be the same as the
//	  BD_ADDR.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.4.6)
//	    * @param[out] BD_ADDR BD_ADDR ( Bluetooth Device Address) of the Device.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status readBdAddr(byte address[6]);

	/**
	  * @brief This command reads the Received Signal Strength Indication (RSSI) value from
	  a Controller.
	  For an LE transport, a Connection_Handle is used as the Handle command
	  parameter and return parameter. The meaning of the RSSI metric is an absolute
	  receiver signal strength value in dBm to +/- 6 dB accuracy. If the RSSI cannot
	  be read, the RSSI metric shall be set to 127.
	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.5.4)
	    * @param Connection_Handle Connection handle for which the command is given.
	    * Values:
	    - 0x0000 ... 0x0EFF
	    * @param[out] RSSI N Size: 1 Octet (signed integer)
	    Units: dBm
	      * Values:
	      - 127: RSSI not available
	      - -127 ... 20
	      * @retval Value indicating success or error code.
	      */
	static HCI::Status readRssi(ushort handle, signed char &rssi);

//	/**
//	  * @brief The LE_Set_Event_Mask command is used to control which LE events are
//	  generated by the HCI for the Host. If the bit in the LE_Event_Mask is set to a
//	  one, then the event associated with that bit will be enabled. The Host has to
//	  deal with each event that is generated by an LE Controller. The event mask
//	  allows the Host to control which events will interrupt it.
//	  For LE events to be generated, the LE Meta-Event bit in the Event_Mask shall
//	  also be set. If that bit is not set, then LE events shall not be generated, regardless
//	  of how the LE_Event_Mask is set.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.1)
//	    * @param LE_Event_Mask LE event mask. Default: 0x00000000000FFFFF.
//	    * Flags:
//	    - 0x0000000000000000: No LE events specified
//	    - 0x0000000000000001: LE Connection Complete Event
//	    - 0x0000000000000002: LE Advertising Report Event
//	    - 0x0000000000000004: LE Connection Update Complete Event
//	    - 0x0000000000000008: LE Read Remote Used Features Complete Event
//	    - 0x0000000000000010: LE Long Term Key Request Event
//	    - 0x0000000000000020: LE Remote Connection Parameter Request Event
//	    - 0x0000000000000040: LE Data Length Change Event
//	    - 0x0000000000000080: LE Read Local P-256 Public Key Complete Event
//	    - 0x0000000000000100: LE Generate DHKey Complete Event
//	    - 0x0000000000000200: LE Enhanced Connection Complete Event
//	    - 0x0000000000000400: LE Direct Advertising Report Event
//	    - 0x0000000000000800: LE PHY Update Complete Event
//	    - 0x0000000000001000: LE Extended Advertising Report Event
//	    - 0x0000000000002000: LE Periodic Advertising Sync Established Event
//	    - 0x0000000000004000: LE Periodic Advertising Report Event
//	    - 0x0000000000008000: LE Periodic Advertising Sync Lost Event
//	    - 0x0000000000010000: LE Extended Scan Timeouout Event
//	    - 0x0000000000020000: LE Extended Advertising Set Terminated Event
//	    - 0x0000000000040000: LE Scan Request Received Event
//	    - 0x0000000000080000: LE Channel Selection Algorithm Event
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status leSetEventMask(byte mask[8]);
//
//	/**
//	  * @brief The LE_Read_Buffer_Size command is used to read the maximum size of the
//	  data portion of HCI LE ACL Data Packets sent from the Host to the Controller.
//	  The Host will segment the data transmitted to the Controller according to these
//	  values, so that the HCI Data Packets will contain data with up to this size. The
//	  LE_Read_Buffer_Size command also returns the total number of HCI LE ACL
//	  Data Packets that can be stored in the data buffers of the Controller. The
//	  LE_Read_Buffer_Size command must be issued by the Host before it sends
//	  any data to an LE Controller (see Section 4.1.1).
//	  If the Controller returns a length value of zero, the Host shall use the
//	  Read_Buffer_Size command to determine the size of the data buffers
//	  Note: Both the Read_Buffer_Size and LE_Read_Buffer_Size commands may
//	  return buffer length and number of packets parameter values that are nonzero.
//	  The HC_LE_ACL_Data_Packet_Length return parameter shall be used to
//	  determine the size of the L2CAP PDU segments contained in ACL Data
//	  Packets, which are transferred from the Host to the Controller to be broken up
//	  into packets by the Link Layer. Both the Host and the Controller shall support
//	  command and event packets, where the data portion (excluding header)
//	  contained in the packets is 255 octets in size. The
//	  HC_Total_Num_LE_ACL_Data_Packets return parameter contains the total
//	  number of HCI ACL Data Packets that can be stored in the data buffers of the
//	  Controller. The Host determines how the buffers are to be divided between
//	  different Connection Handles.
//	  Note: The HC_LE_ACL_Data_Packet_Length return parameter does not
//	  include the length of the HCI Data Packet header.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.2)
//	    * @param[out] HC_LE_ACL_Data_Packet_Length 0x0000 No dedicated LE Buffer - use Read_Buffer_Size command.
//	    0x0001 - 0xFFFF Maximum length (in octets) of the data portion of each HCI ACL Data
//	    Packet that the Controller is able to accept.
//	      * @param[out] HC_Total_Num_LE_ACL_Data_Packets 0x00 No dedicated LE Buffer - use Read_Buffer_Size command.
//	      0x01 - 0xFF Total number of HCI ACL Data Packets that can be stored in the data
//	      buffers of the Controller.
//	        * @retval Value indicating success or error code.
//	        */
//	static HCI::Status leReadBufferSize(ushort *HC_LE_ACL_Data_Packet_Length, byte *HC_Total_Num_LE_ACL_Data_Packets);
//
//	/**
//	  * @brief This command requests the list of the supported LE features for the Controller.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.3)
//	    * @param[out] LE_Features Bit Mask List of LE features. See Core v5.0, Vol. 6, Part B, Section 4.6.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_read_local_supported_features(byte LE_Features[8]);
//
//	/**
//	  * @brief The LE_Set_Random_Address command is used by the Host to set the LE
//	  Random Device Address in the Controller (see [Vol 6] Part B, Section 1.3).
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.4)
//	    * @param Random_Address Random Device Address.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_set_random_address(byte Random_Address[6]);
//
//	/**
//	  * @brief The LE_Set_Advertising_Parameters command is used by the Host to set the
//	  advertising parameters.
//	  The Advertising_Interval_Min shall be less than or equal to the Advertising_Interval_Max.
//	  The Advertising_Interval_Min and Advertising_Interval_Max
//	  should not be the same value to enable the Controller to determine the best
//	  advertising interval given other activities.
//	  For high duty cycle directed advertising, i.e. when Advertising_Type is 0x01
//	  (ADV_DIRECT_IND, high duty cycle), the Advertising_Interval_Min and Advertising_Interval_Max
//	  parameters are not used and shall be ignored.
//	  The Advertising_Type is used to determine the packet type that is used for
//	  advertising when advertising is enabled.
//	  The Advertising_Interval_Min and Advertising_Interval_Max shall not be set to
//	  less than 0x00A0 (100 ms) if the Advertising_Type is set to 0x02 (ADV_SCAN_IND)
//	  or 0x03 (ADV_NONCONN_IND). The Own_Address_Type determines
//	  if the advertising packets are identified with the Public Device Address of
//	  the device, or a Random Device Address as written by the LE_Set_Random_Address
//	  command.
//	  If directed advertising is performed, i.e. when Advertising_Type is set to 0x01
//	  (ADV_DIRECT_IND, high duty cycle) or 0x04 (ADV_DIRECT_IND, low duty
//	  cycle mode), then the Direct_Address_Type and Direct_Address shall be valid,
//	  otherwise they shall be ignored by the Controller and not used.
//	  The Advertising_Channel_Map is a bit field that indicates the advertising channels
//	  that shall be used when transmitting advertising packets. At least one
//	  channel bit shall be set in the Advertising_Channel_Map parameter.
//	  The Advertising_Filter_Policy parameter shall be ignored when directed advertising
//	  is enabled.
//	  The Host shall not issue this command when advertising is enabled in the Controller;
//	  if it is the Command Disallowed error code shall be used.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.5)
//	    * @param Advertising_Interval_Min Minimum advertising interval.
//	    Time = N * 0.625 msec.
//	      * Values:
//	      - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
//	      * @param Advertising_Interval_Max Maximum advertising interval.
//	      Time = N * 0.625 msec.
//	        * Values:
//	        - 0x0020 (20.000 ms)  ... 0x4000 (10240.000 ms) 
//	        * @param Advertising_Type Advertising type.
//	        * Values:
//	        - 0x00: ADV_IND (Connectable undirected advertising)
//	        - 0x01: ADV_DIRECT_IND, high duty cycle (Connectable high duty cycle directed advertising)
//	        - 0x02: ADV_SCAN_IND (Scannable undirected advertising)
//	        - 0x03: ADV_NONCONN_IND (Non connectable undirected advertising)
//	        - 0x04: ADV_DIRECT_IND, low duty cycle (Connectable low duty cycle directed advertising)
//	        * @param Own_Address_Type Own address type.
//	       - 0x00: Public Device Address
//	       - 0x01 Random Device Address
//	       - 0x02: Controller generates Resolvable Private Address based on the local
//	               IRK from resolving list. If resolving list contains no matching entry,
//	               use public address.
//	              - 0x03: Controller generates Resolvable Private Address based on the local
//	                      IRK from resolving list. If resolving list contains no matching entry,
//	                      use random address from LE_Set_Random_Address.
//	                    * Values:
//	                    - 0x00: Public Device Address
//	                    - 0x01: Random Device Address
//	                    - 0x02: Resolvable Private Address or Public Address
//	                    - 0x03: Resolvable Private Address or Random Address
//	                    * @param Peer_Address_Type The address type of the peer device.
//	                    * Values:
//	                    - 0x00: Public Device Address
//	                    - 0x01: Random Device Address
//	                    * @param Peer_Address Public Device Address, Random Device Address, Public Identity
//	                    Address or Random (static) Identity Address of the device to be connected.
//	                      * @param Advertising_Channel_Map Advertising channel map.
//	                      Default: 00000111b (all channels enabled).
//	                        * Flags:
//	                        - 0x01: ch 37
//	                        - 0x02: ch 38
//	                        - 0x04: ch 39
//	                        * @param Advertising_Filter_Policy Advertising filter policy.
//	                        * Values:
//	                        - 0x00: Allow Scan Request from Any, Allow Connect Request from Any
//	                        - 0x01: Allow Scan Request from White List Only, Allow Connect Request from Any
//	                        - 0x02: Allow Scan Request from Any, Allow Connect Request from White List Only
//	                        - 0x03: Allow Scan Request from White List Only, Allow Connect Request from White List Only
//	                        * @retval Value indicating success or error code.
//	                        */
//	static HCI::Status le_set_advertising_parameters(ushort Advertising_Interval_Min,  ushort Advertising_Interval_Max, byte Advertising_Type, byte Own_Address_Type, byte Peer_Address_Type, byte Peer_Address[6], byte Advertising_Channel_Map, byte Advertising_Filter_Policy);
//
//	/**
//	  * @brief The LE_Read_Advertising_Channel_Tx_Power command is used by the Host
//	  to read the transmit power level used for LE advertising channel packets.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.6)
//	    * @param[out] Transmit_Power_Level Size: 1 Octet (signed integer)
//	    Units: dBm
//	    Accuracy: +/- 4 dBm
//	      * Values:
//	      - -20 ... 10
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_read_advertising_channel_tx_power(byte *Transmit_Power_Level);
//
//	/**
//	  * @brief The LE_Set_Advertising_Data command is used to set the data used in advertising
//	  packets that have a data field.
//	  Only the significant part of the Advertising_Data is transmitted in the advertising
//	  packets, as defined in [Vol 3] Part C, Section 11.,
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.7)
//	    * @param Advertising_Data_Length The number of significant octets in the following data field
//	    * @param Advertising_Data 31 octets of data formatted as defined in [Vol 3] Part C, Section 11.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_set_advertising_data(byte Advertising_Data_Length, byte Advertising_Data[31]);
//
//	/**
//	  * @brief This command is used to provide data used in Scanning Packets that have a
//	  data field.
//	  Only the significant part of the Scan_Response_Data is transmitted in the
//	  Scanning Packets, as defined in [Vol 3] Part C, Section 11.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.8)
//	    * @param Scan_Response_Data_Length The number of significant octets in the following data field
//	    * @param Scan_Response_Data 31 octets of data formatted as defined in [Vol 3] Part C, Section 11.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_set_scan_response_data(byte Scan_Response_Data_Length,  byte Scan_Response_Data[31]);
//
//	/**
//	  * @brief The LE_Set_Advertise_Enable command is used to request the Controller to
//	  start or stop advertising. The Controller manages the timing of advertisements
//	  as per the advertising parameters given in the LE_Set_Advertising_Parameters
//	  command.
//	  The Controller shall continue advertising until the Host issues an LE_Set_Advertise_Enable
//	  command with Advertising_Enable set to 0x00 (Advertising is
//	  disabled) or until a connection is created or until the Advertising is timed out
//	  due to high duty cycle Directed Advertising. In these cases, advertising is then
//	  disabled.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.9)
//	    * @param Advertising_Enable Enable/disable advertise. Default is 0 (disabled).
//	    * Values:
//	    - 0x00: Advertising is disabled
//	    - 0x01: Advertising is enabled
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_set_advertise_enable(byte Advertising_Enable);
//
//	/**
//	  * @brief The LE_Set_Scan_Parameters command is used to set the scan parameters.
//	  The LE_Scan_Type parameter controls the type of scan to perform.
//	  The LE_Scan_Interval and LE_Scan_Window parameters are recommendations
//	  from the Host on how long (LE_Scan_Window) and how frequently
//	  (LE_Scan_Interval) the Controller should scan (See [Vol 6] Part B, Section
//	  4.4.3). The LE_Scan_Window parameter shall always be set to a value smaller
//	  or equal to the value set for the LE_Scan_Interval parameter. If they are set to
//	  the same value scanning should be run continuously.
//	  The Own_Address_Type parameter determines the address used (Public or
//	  Random Device Address) when performing active scan.
//	  The Host shall not issue this command when scanning is enabled in the Controller;
//	  if it is the Command Disallowed error code shall be used.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.10)
//	    * @param LE_Scan_Type Passive or active scanning. With active scanning SCAN_REQ packets are sent.
//	    * Values:
//	    - 0x00: Passive Scanning
//	    - 0x01: Active scanning
//	    * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
//	    its last LE scan until it begins the subsequent LE scan.
//	    Time = N * 0.625 msec.
//	      * Values:
//	      - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
//	      * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
//	      shall be less than or equal to LE_Scan_Interval.
//	      Time = N * 0.625 msec.
//	        * Values:
//	        - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
//	        * @param Own_Address_Type Own address type.
//	       - 0x00: Public Device Address
//	       - 0x01 Random Device Address
//	       - 0x02: Controller generates Resolvable Private Address based on the local
//	               IRK from resolving list. If resolving list contains no matching entry,
//	               use public address.
//	              - 0x03: Controller generates Resolvable Private Address based on the local
//	                      IRK from resolving list. If resolving list contains no matching entry,
//	                      use random address from LE_Set_Random_Address.
//	                    * Values:
//	                    - 0x00: Public Device Address
//	                    - 0x01: Random Device Address
//	                    - 0x02: Resolvable Private Address or Public Address
//	                    - 0x03: Resolvable Private Address or Random Address
//	                    * @param Scanning_Filter_Policy 0x00 Accept all advertisement packets.
//	                    Directed advertising packets which are not addressed for this device
//	                    shall be ignored.
//	                    0x01 Ignore advertisement packets from devices not in the White List Only.
//	                    Directed advertising packets which are not addressed for this device
//	                    shall be ignored
//	                    0x02 Accept all undirected advertisement packets.
//	                    Directed advertisement packets where initiator address is a RPA and 
//	                    Directed advertisement packets addressed to this device shall be accepted.
//	                    0x03 Accept all undirected advertisement packets from devices that are in
//	                    the White List.Directed advertisement packets where initiator address is RPA and Directed advertisement packets addressed to this device shall be accepted.
//	                      * Values:
//	                      - 0x00: Accept all
//	                      - 0x01: Ignore devices not in the White List
//	                      - 0x02: Accept all (use resolving list)
//	                      - 0x03: Ignore devices not in the White List (use resolving list)
//	                      * @retval Value indicating success or error code.
//	                      */
//	static HCI::Status le_set_scan_parameters(byte LE_Scan_Type,  ushort LE_Scan_Interval, ushort LE_Scan_Window, byte Own_Address_Type, byte Scanning_Filter_Policy);
//
//	/**
//	  * @brief The LE_Set_Scan_Enable command is used to start scanning. Scanning is
//	  used to discover advertising devices nearby.
//	  The Filter_Duplicates parameter controls whether the Link Layer shall filter
//	  duplicate advertising reports to the Host, or if the Link Layer should generate
//	  advertising reports for each packet received.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.11)
//	    * @param LE_Scan_Enable Enable/disable scan. Default is 0 (disabled).
//	    * Values:
//	    - 0x00: Scanning disabled
//	    - 0x01: Scanning enabled
//	    * @param Filter_Duplicates Enable/disable duplicate filtering.
//	    * Values:
//	    - 0x00: Duplicate filtering disabled
//	    - 0x01: Duplicate filtering enabled
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_set_scan_enable(byte LE_Scan_Enable, byte Filter_Duplicates);
//
//	/**
//	  * @brief The LE_Create_Connection command is used to create a Link Layer connection
//	  to a connectable advertiser.
//	  The LE_Scan_Interval and LE_Scan_Window parameters are recommendations
//	  from the Host on how long (LE_Scan_Window) and how frequently
//	  (LE_Scan_Interval) the Controller should scan. The LE_Scan_Window parameter
//	  shall be set to a value smaller or equal to the value set for the LE_Scan_Interval
//	  parameter. If both are set to the same value, scanning should run
//	  continuously.
//	  The Initiator_Filter_Policy is used to determine whether the White List is used.
//	  If the White List is not used, the Peer_Address_Type and the Peer_Address
//	  parameters specify the address type and address of the advertising device to
//	  connect to.
//	  The Link Layer shall set the address in the CONNECT_REQ packets to either
//	  the Public Device Address or the Random Device Addressed based on the
//	  Own_Address_Type parameter.
//	  The Conn_Interval_Min and Conn_Interval_Max parameters define the minimum
//	  and maximum allowed connection interval. The Conn_Interval_Min
//	  parameter shall not be greater than the Conn_Interval_Max parameter.
//	  The Conn_Latency parameter defines the maximum allowed connection
//	  latency (see [Vol 6] Part B, Section 4.5.1).
//	  The Supervision_Timeout parameter defines the link supervision timeout for
//	  the connection. The Supervision_Timeout in milliseconds shall be larger than
//	  (1 + Conn_Latency) * Conn_Interval_Max * 2, where Conn_Interval_Max is
//	  given in milliseconds. (See [Vol 6] Part B, Section 4.5.2).
//	  The Minimum_CE_Length and Maximum_CE_Length parameters are informative
//	  parameters providing the Controller with the expected minimum and maximum
//	  length of the connection events. The Minimum_CE_Length parameter
//	  shall be less than or equal to the Maximum_CE_Length parameter.
//	  The Host shall not issue this command when another LE_Create_Connection
//	  is pending in the Controller; if this does occur the Controller shall return the
//	  Command Disallowed error code shall be used.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.12)
//	    * @param LE_Scan_Interval This is defined as the time interval from when the Controller started
//	    its last LE scan until it begins the subsequent LE scan.
//	    Time = N * 0.625 msec.
//	      * Values:
//	      - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
//	      * @param LE_Scan_Window Amount of time for the duration of the LE scan. LE_Scan_Window
//	      shall be less than or equal to LE_Scan_Interval.
//	      Time = N * 0.625 msec.
//	        * Values:
//	        - 0x0004 (2.500 ms)  ... 0x4000 (10240.000 ms) 
//	        * @param Initiator_Filter_Policy 0x00 White list is not used to determine which advertiser to connect to.
//	        Peer_Address_Type and Peer_Address shall be used.
//	        0x01 White list is used to determine which advertiser to connect to.
//	        Peer_Address_Type and Peer_Address shall be ignored.
//	          * Values:
//	          - 0x00: White list not used
//	          - 0x01: White list used
//	          * @param Peer_Address_Type 0x00 Public Device Address
//	          0x01 Random Device Address
//	          0x02 Public Identity Address (Corresponds to Resolved Private Address)
//	          0x03 Random (Static) Identity Address (Corresponds to Resolved Private Address)
//	            * Values:
//	            - 0x00: Public Device Address
//	            - 0x01: Random Device Address
//	            - 0x02: Public Identity Address
//	            - 0x03: Random (Static) Identity Address
//	            * @param Peer_Address Public Device Address or Random Device Address of the device
//	            to be connected.
//	              * @param Own_Address_Type Own address type.
//	             - 0x00: Public Device Address
//	             - 0x01 Random Device Address
//	             - 0x02: Controller generates Resolvable Private Address based on the local
//	                     IRK from resolving list. If resolving list contains no matching entry,
//	                     use public address.
//	                    - 0x03: Controller generates Resolvable Private Address based on the local
//	                            IRK from resolving list. If resolving list contains no matching entry,
//	                            use random address from LE_Set_Random_Address.
//	                          * Values:
//	                          - 0x00: Public Device Address
//	                          - 0x01: Random Device Address
//	                          - 0x02: Resolvable Private Address or Public Address
//	                          - 0x03: Resolvable Private Address or Random Address
//	                          * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
//	                          than or equal to Conn_Interval_Max.
//	                          Time = N * 1.25 msec.
//	                            * Values:
//	                            - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
//	                            * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
//	                            greater than or equal to Conn_Interval_Min.
//	                            Time = N * 1.25 msec.
//	                              * Values:
//	                              - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
//	                              * @param Conn_Latency Slave latency for the connection in number of connection events.
//	                              * Values:
//	                              - 0x0000 ... 0x01F3
//	                              * @param Supervision_Timeout Supervision timeout for the LE Link.
//	                              It shall be a multiple of 10 ms and larger than (1 + connSlaveLatency) * connInterval * 2.
//	                              Time = N * 10 msec.
//	                                * Values:
//	                                - 0x000A (100 ms)  ... 0x0C80 (32000 ms) 
//	                                * @param Minimum_CE_Length Information parameter about the minimum length of connection
//	                                needed for this LE connection.
//	                                Time = N * 0.625 msec.
//	                                  * Values:
//	                                  - 0x0000 (0.000 ms)  ... 0xFFFF (40959.375 ms) 
//	                                  * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
//	                                  for this LE connection.
//	                                  Time = N * 0.625 msec.
//	                                    * Values:
//	                                    - 0x0000 (0.000 ms)  ... 0xFFFF (40959.375 ms) 
//	                                    * @retval Value indicating success or error code.
//	                                    */
//	static HCI::Status le_create_connection(	ushort LE_Scan_Interval, ushort LE_Scan_Window, byte Initiator_Filter_Policy, byte Peer_Address_Type,
//											byte Peer_Address[6], byte Own_Address_Type, ushort Conn_Interval_Min, ushort Conn_Interval_Max,
//											ushort Conn_Latency, ushort Supervision_Timeout, ushort Minimum_CE_Length, ushort Maximum_CE_Length);
//
//	/**
//	  * @brief The LE_Create_Connection_Cancel command is used to cancel the LE_Create_Connection
//	  command. This command shall only be issued after the
//	  LE_Create_Connection command has been issued, a Command Status event
//	  has been received for the LE Create Connection command and before the LE
//	  Connection Complete event.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.13)
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_create_connection_cancel();
//
//	/**
//	  * @brief The LE_Read_White_List_Size command is used to read the total number of
//	  white list entries that can be stored in the Controller.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.14)
//	    * @param[out] White_List_Size Total number of white list entries that can be stored in the Controller.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_read_white_list_size(byte *White_List_Size);
//
//	/**
//	  * @brief The LE_Clear_White_List command is used to clear the white list stored in the
//	  Controller.
//	  This command can be used at any time except when:
//	  - the advertising filter policy uses the white list and advertising is enabled.
//	  - the scanning filter policy uses the white list and scanning is enabled.
//	  - the initiator filter policy uses the white list and an LE_Create_Connection
//	  command is outstanding.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.15)
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_clear_white_list();
//
//	/**
//	  * @brief The LE_Add_Device_To_White_List command is used to add a single device
//	  to the white list stored in the Controller.
//	  This command can be used at any time except when:
//	  - the advertising filter policy uses the white list and advertising is enabled.
//	  - the scanning filter policy uses the white list and scanning is enabled.
//	  - the initiator filter policy uses the white list and a create connection command
//	  is outstanding.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.16)
//	    * @param Address_Type Address type.
//	    * Values:
//	    - 0x00: Public Device Address
//	    - 0x01: Random Device Address
//	    * @param Address Public Device Address or Random Device Address of the device
//	    to be added to the white list.
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_add_device_to_white_list(byte Address_Type, byte Address[6]);
//
//	/**
//	  * @brief The LE_Remove_Device_From_White_List command is used to remove a single
//	  device from the white list stored in the Controller.
//	  This command can be used at any time except when:
//	  - the advertising filter policy uses the white list and advertising is enabled.
//	  - the scanning filter policy uses the white list and scanning is enabled.
//	  - the initiator filter policy uses the white list and a create connection command
//	  is outstanding.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.17)
//	    * @param Address_Type Address type.
//	    * Values:
//	    - 0x00: Public Device Address
//	    - 0x01: Random Device Address
//	    * @param Address Public Device Address or Random Device Address of the device 
//															 to be removed from the white list.
//		* @retval Value indicating success or error code.
//		*/
//	static HCI::Status le_remove_device_from_white_list(byte Address_Type, byte Address[6]);
//
//	/**
//	  * @brief The LE_Connection_Update command is used to change the Link Layer connection
//	  parameters of a connection. This command is supported only on master side.
//	  The Conn_Interval_Min and Conn_Interval_Max parameters are used to define
//	  the minimum and maximum allowed connection interval. The Conn_Interval_Min
//	  parameter shall not be greater than the Conn_Interval_Max parameter.
//	  The Conn_Latency parameter shall define the maximum allowed connection
//	  latency.
//	  The Supervision_Timeout parameter shall define the link supervision timeout
//	  for the LE link. The Supervision_Timeout in milliseconds shall be larger than (1
//	  + Conn_Latency) * Conn_Interval_Max * 2, where Conn_Interval_Max is given
//	  in milliseconds.
//	  The Minimum_CE_Length and Maximum_CE_Length are information parameters
//	  providing the Controller with a hint about the expected minimum and maximum
//	  length of the connection events. The Minimum_CE_Length shall be less
//	  than or equal to the Maximum_CE_Length.
//	  The actual parameter values selected by the Link Layer may be different from
//	  the parameter values provided by the Host through this command.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.18)
//	    * @param Connection_Handle Connection handle for which the command is given.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @param Conn_Interval_Min Minimum value for the connection event interval. This shall be less
//	    than or equal to Conn_Interval_Max.
//	    Time = N * 1.25 msec.
//	      * Values:
//	      - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
//	      * @param Conn_Interval_Max Maximum value for the connection event interval. This shall be
//	      greater than or equal to Conn_Interval_Min.
//	      Time = N * 1.25 msec.
//	        * Values:
//	        - 0x0006 (7.50 ms)  ... 0x0C80 (4000.00 ms) 
//	        * @param Conn_Latency Slave latency for the connection in number of connection events.
//	        * Values:
//	        - 0x0000 ... 0x01F3
//	        * @param Supervision_Timeout Supervision timeout for the LE Link.
//	        It shall be a multiple of 10 ms and larger than (1 + connSlaveLatency) * connInterval * 2.
//	        Time = N * 10 msec.
//	          * Values:
//	          - 0x000A (100 ms)  ... 0x0C80 (32000 ms) 
//	          * @param Minimum_CE_Length Information parameter about the minimum length of connection
//	          needed for this LE connection.
//	          Time = N * 0.625 msec.
//	            * Values:
//	            - 0x0000 (0.000 ms)  ... 0xFFFF (40959.375 ms) 
//	            * @param Maximum_CE_Length Information parameter about the maximum length of connection needed
//	            for this LE connection.
//	            Time = N * 0.625 msec.
//	              * Values:
//	              - 0x0000 (0.000 ms)  ... 0xFFFF (40959.375 ms) 
//	              * @retval Value indicating success or error code.
//	              */
//	static HCI::Status le_connection_update(ushort Connection_Handle, ushort Conn_Interval_Min, ushort Conn_Interval_Max, ushort Conn_Latency, ushort Supervision_Timeout, ushort Minimum_CE_Length, ushort Maximum_CE_Length);
//
//	/**
//	  * @brief The LE_Set_Host_Channel_Classification command allows the Host to specify
//	  a channel classification for data channels based on its "local information". This
//	  classification persists until overwritten with a subsequent LE_Set_Host_Channel_Classification
//	  command or until the Controller is reset using the Reset
//	  command (see [Vol 6] Part B, Section 4.5.8.1).
//	  If this command is used, the Host should send it within 10 seconds of knowing
//	  that the channel classification has changed. The interval between two successive
//	  commands sent shall be at least one second.
//	  This command shall only be used when the local device supports the Master
//	  role.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.19)
//	    * @param LE_Channel_Map This parameter contains 37 1-bit fields.
//	    The nth such field (in the range 0 to 36) contains the value for the
//	    link layer channel index n.
//	    Channel n is bad = 0.
//	    Channel n is unknown = 1.
//	    The most significant bits are reserved and shall be set to 0.
//	    At least one channel shall be marked as unknown.
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_set_host_channel_classification(byte LE_Channel_Map[5]);
//
//	/**
//	  * @brief The LE_Read_Channel_Map command returns the current Channel_Map for
//	  the specified Connection_Handle. The returned value indicates the state of the
//	  Channel_Map specified by the last transmitted or received Channel_Map (in a
//	  CONNECT_REQ or LL_CHANNEL_MAP_REQ message) for the specified
//	  Connection_Handle, regardless of whether the Master has received an
//	  acknowledgement.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.20)
//	    * @param Connection_Handle Connection handle for which the command is given.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @param[out] LE_Channel_Map This parameter contains 37 1-bit fields.
//	    The nth such field (in the range 0 to 36) contains the value for the
//	    link layer channel index n.
//	    Channel n is unused = 0.
//	    Channel n is used = 1.
//	    The most significant bits are reserved and shall be set to 0.
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_read_channel_map(ushort Connection_Handle, byte LE_Channel_Map[5]);
//
//	/**
//	  * @brief This command requests a list of the used LE features from the remote device.
//	  This command shall return a list of the used LE features. For details see [Vol 6]
//	  Part B, Section 4.6.
//	  This command may be issued on both the master and slave.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.21)
//	    * @param Connection_Handle Connection handle for which the command is given.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_read_remote_features(ushort Connection_Handle);
//
//	/**
//	  * @brief The LE_Encrypt command is used to request the Controller to encrypt the
//	  Plaintext_Data in the command using the Key given in the command and
//	  returns the Encrypted_Data to the Host. The AES-128 bit block cypher is
//	  defined in NIST Publication FIPS-197 (http://csrc.nist.gov/publications/fips/
//	  fips197/fips-197.pdf).
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.22)
//	    * @param Key 128 bit key for the encryption of the data given in the command.
//	    * @param Plaintext_Data 128 bit data block that is requested to be encrypted.
//	    * @param[out] Encrypted_Data 128 bit encrypted data block.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_encrypt(byte Key[16], byte Plaintext_Data[16], byte Encrypted_Data[16]);
//
//	/**
//	  * @brief The LE_Rand command is used to request the Controller to generate 8 octets
//	  of random data to be sent to the Host. The Random_Number shall be generated
//	  according to [Vol 2] Part H, Section 2 if the LE Feature (LL Encryption) is
//	  supported.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.23)
//	    * @param[out] Random_Number Random Number
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_rand(byte Random_Number[8]);
//
//	/**
//	  * @brief The LE_Start_Encryption command is used to authenticate the given encryption
//	  key associated with the remote device specified by the connection handle,
//	  and once authenticated will encrypt the connection. The parameters are as
//	  defined in [Vol 3] Part H, Section 2.4.4.
//	  If the connection is already encrypted then the Controller shall pause connection
//	  encryption before attempting to authenticate the given encryption key, and
//	  then re-encrypt the connection. While encryption is paused no user data shall
//	  be transmitted.
//	  On an authentication failure, the connection shall be automatically disconnected
//	  by the Link Layer. If this command succeeds, then the connection shall
//	  be encrypted.
//	  This command shall only be used when the local device's role is Master.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.24)
//	    * @param Connection_Handle Connection handle for which the command is given.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @param Random_Number 64 bit random number.
//	    * @param Encrypted_Diversifier 16 bit encrypted diversifier.
//	    * @param Long_Term_Key 128 bit long term key.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_start_encryption(ushort Connection_Handle, byte Random_Number[8], ushort Encrypted_Diversifier, byte Long_Term_Key[16]);
//
//	/**
//	  * @brief The LE_Long_Term_Key_Request_Reply command is used to reply to an LE
//	  Long Term Key Request event from the Controller, and specifies the
//	  Long_Term_Key parameter that shall be used for this Connection_Handle. The
//	  Long_Term_Key is used as defined in [Vol 6] Part B, Section 5.1.3.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.25)
//	    * @param Connection_Handle Connection handle for which the command is given.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @param Long_Term_Key 128 bit long term key.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_long_term_key_request_reply(ushort Connection_Handle, byte Long_Term_Key[16]);
//
//	/**
//	  * @brief The LE_Long_Term_Key_Request_Negative_Reply command is used to reply
//	  to an LE Long Term Key Request event from the Controller if the Host cannot
//	  provide a Long Term Key for this Connection_Handle.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.26)
//	    * @param Connection_Handle Connection handle for which the command is given.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_long_term_key_requested_negative_reply(ushort Connection_Handle);
//
//	/**
//	  * @brief The LE_Read_Supported_States command reads the states and state combinations
//	  that the link layer supports. See [Vol 6] Part B, Section 1.1.1.
//	  LE_States is an 8-octet bit field. If a bit is set to 1 then this state or state combination
//	  is supported by the Controller. Multiple bits in LE_States may be set to 1
//	  to indicate support for multiple state and state combinations.
//	  All the Advertising type with the Initiate State combinations shall be set only if
//	  the corresponding Advertising types and Master Role combination are set.
//	  All the Scanning types and the Initiate State combinations shall be set only if
//	  the corresponding Scanning types and Master Role combination are set.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.27)
//	    * @param[out] LE_States State or state combination is supported by the Controller.
//	    See Core v5.0, Vol.2, part E, Ch. 7.8.27.
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_read_supported_states(byte LE_States[8]);
//
//	/**
//	  * @brief This command is used to start a test where the DUT receives test reference
//	  packets at a fixed interval. The tester generates the test reference packets.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.28)
//	    * @param RX_Frequency N = (F - 2402) / 2
//	    Frequency Range : 2402 MHz to 2480 MHz
//	      * Values:
//	      - 0x00 ... 0x27
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_receiver_test(byte RX_Frequency);
//
//	/**
//	  * @brief This command is used to start a test where the DUT generates test reference
//	  packets at a fixed interval. The Controller shall transmit at maximum power.
//	  An LE Controller supporting the LE_Transmitter_Test command shall support
//	  Packet_Payload values 0x00, 0x01 and 0x02. An LE Controller may support
//	  other values of Packet_Payload.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.29)
//	    * @param TX_Frequency N = (F - 2402) / 2
//	    Frequency Range : 2402 MHz to 2480 MHz
//	      * Values:
//	      - 0x00 ... 0x27
//	      * @param Length_Of_Test_Data Length in bytes of payload data in each packet.
//	      * Values:
//	      - 0x00 ... 0x25
//	      * @param Packet_Payload Type of packet payload.
//	      * Values:
//	      - 0x00: Pseudo-Random bit sequence 9
//	      - 0x01: Pattern of alternating bits '11110000'
//	      - 0x02: Pattern of alternating bits '10101010'
//	      - 0x03: Pseudo-Random bit sequence 15
//	      - 0x04: Pattern of All '1' bits
//	      - 0x05: Pattern of All '0' bits
//	      - 0x06: Pattern of alternating bits '00001111'
//	      - 0x07: Pattern of alternating bits '0101'
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_transmitter_test(byte TX_Frequency, byte Length_Of_Test_Data, byte Packet_Payload);
//
//	/**
//	  * @brief This command is used to stop any test which is in progress. The Number_Of_Packets
//	  for a transmitter test shall be reported as 0x0000. The Number_Of_Packets
//	  is an unsigned number and contains the number of received
//	  packets.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.30)
//	    * @param[out] Number_Of_Packets Number of packets received
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_test_end(ushort *Number_Of_Packets);
//
//	/**
//	  * @brief The LE_Set_Data_Length command allows the Host to suggest maximum
//	  transmission packet size and maximum packet transmission time
//	  (connMaxTxOctets and connMaxTxTime - see Bluetooth Specification v5.0 [Vol 6] Part B, Section 4.5.10) to
//	  be used for a given connection. The Controller may use smaller or larger
//	  values based on local information. 
//	    * @param Connection_Handle Connection handle for which the command is given.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @param TxOctets Preferred maximum number of payload octets that the local Controller
//	    should include in a single Link Layer packet on this connection.
//	      * Values:
//	      - 0x001B ... 0x00FB
//	      * @param TxTime Preferred maximum number of microseconds that the local Controller
//	      should use to transmit a single Link Layer packet on this connection.
//	        * Values:
//	        - 0x0148 ... 0x4290
//	        * @retval Value indicating success or error code.
//	        */
//	static HCI::Status le_set_data_length(ushort Connection_Handle, ushort TxOctets, ushort TxTime);
//
//	/**
//	  * @brief The LE_Read_Suggested_Default_Data_Length command allows the Host to
//	  read the Host's suggested values (SuggestedMaxTxOctets and
//	  SuggestedMaxTxTime) for the Controller's maximum transmitted number of
//	  payload octets and maximum packet transmission time to be used for new
//	  connections (see Bluetooth Specification v5.0 [Vol 6] Part B, Section 4.5.10). 
//	    * @param[out] SuggestedMaxTxOctets The Host's suggested value for the Controller's maximum transmitted
//	    number of payload octets to be used for new connections.
//	      * Values:
//	      - 0x001B ... 0x00FB
//	      * @param[out] SuggestedMaxTxTime The Host's suggested value for the Controller's maximum packet
//	      transmission time to be used for new connections.
//	        * Values:
//	        - 0x0148 ... 0x4290
//	        * @retval Value indicating success or error code.
//	        */
//	static HCI::Status le_read_suggested_default_data_length(ushort *SuggestedMaxTxOctets, ushort *SuggestedMaxTxTime);
//
//	/**
//	  * @brief The LE_Write_Suggested_Default_Data_Length command allows the Host to
//	  specify its suggested values for the Controller's maximum transmission
//	  number of payload octets and maximum packet transmission time to be used
//	  for new connections. The Controller may use smaller or larger values for
//	  connInitialMaxTxOctets and connInitialMaxTxTime based on local
//	  information.(see Bluetooth Specification [Vol 6] Part B, Section 4.5.10). 
//	    * @param SuggestedMaxTxOctets The Host's suggested value for the Controller's maximum transmitted
//	    number of payload octets to be used for new connections.
//	      * Values:
//	      - 0x001B ... 0x00FB
//	      * @param SuggestedMaxTxTime The Host's suggested value for the Controller's maximum packet
//	      transmission time to be used for new connections.
//	        * Values:
//	        - 0x0148 ... 0x4290
//	        * @retval Value indicating success or error code.
//	        */
//	static HCI::Status le_write_suggested_default_data_length(ushort SuggestedMaxTxOctets, ushort SuggestedMaxTxTime);
//
//	/**
//	  * @brief The LE_Read_Local_P-256_Public_Key command is used to return the local
//	  P-256 public key from the Controller. The Controller shall generate a new P-
//	  256 public/private key pair upon receipt of this command.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.36)
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_read_local_p256_public_key();
//
//	/**
//	  * @brief The LE_Generate_DHKey command is used to initiate generation of a Diffie-
//	  Hellman key in the Controller for use over the LE transport. This command
//	  takes the remote P-256 public key as input. The Diffie-Hellman key generation
//	  uses the private key generated by LE_Read_Local_P256_Public_Key command.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.37)
//	    * @param Remote_P256_Public_Key The remote P-256 public key:
//	    X, Y format
//	    Octets 31-0: X co-ordinate
//	    Octets 63-32: Y co-ordinate
//	    Little Endian Format
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_generate_dhkey(byte Remote_P256_Public_Key[64]);
//
//	/**
//	  * @brief The LE_Add_Device_To_Resolving_List command is used to add one device
//	  to the list of address translations used to resolve Resolvable Private Addresses
//	  in the Controller.
//	  This command cannot be used when address translation is enabled in the
//	  Controller and:
//	  - Advertising is enabled
//	  - Scanning is enabled
//	  - Create connection command is outstanding
//	  This command can be used at any time when address translation is disabled in
//	  the Controller.
//	  When a Controller cannot add a device to the resolving list because the list is
//	  full, it shall respond with error code 0x07 (Memory Capacity Exceeded).
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.38)
//	    * @param Peer_Identity_Address_Type Identity address type.
//	    * Values:
//	    - 0x00: Public Identity Address
//	    - 0x01: Random (static) Identity Address
//	    * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
//	    * @param Peer_IRK IRK of the peer device
//	    * @param Local_IRK IRK of the local device
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_add_device_to_resolving_list(byte Peer_Identity_Address_Type, byte Peer_Identity_Address[6], byte Peer_IRK[16], byte Local_IRK[16]);
//
//	/**
//	  * @brief The LE_Remove_Device_From_Resolving_List command is used to remove
//	  one device from the list of address translations used to resolve Resolvable
//	  Private Addresses in the controller.
//	  This command cannot be used when address translation is enabled in the
//	  Controller and:
//	  - Advertising is enabled
//	  - Scanning is enabled
//	  - Create connection command is outstanding
//	  This command can be used at any time when address translation is disabled in
//	  the Controller.
//	  When a Controller cannot remove a device from the resolving list because it is
//	  not found, it shall respond with error code 0x02 (Unknown Connection
//	  Identifier).
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.39)
//	    * @param Peer_Identity_Address_Type Identity address type.
//	    * Values:
//	    - 0x00: Public Identity Address
//	    - 0x01: Random (static) Identity Address
//	    * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_remove_device_from_resolving_list(byte Peer_Identity_Address_Type, byte Peer_Identity_Address[6]);
//
//	/**
//	  * @brief The LE_Clear_Resolving_List command is used to remove all devices from the
//	  list of address translations used to resolve Resolvable Private Addresses in the
//	  Controller.
//	  This command cannot be used when address translation is enabled in the
//	  Controller and:
//	  - Advertising is enabled
//	  - Scanning is enabled
//	  - Create connection command is outstanding
//	  This command can be used at any time when address translation is disabled in
//	  the Controller.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.40)
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_clear_resolving_list();
//
//	/**
//	  * @brief The LE_Read_Resolving_List_Size command is used to read the total number
//	  of address translation entries in the resolving list that can be stored in the
//	  Controller.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.41)
//	    * @param[out] Resolving_List_Size Number of address translation entries in the resolving list
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_read_resolving_list_size(byte *Resolving_List_Size);
//
//	/**
//	  * @brief The LE_Read_Peer_Resolvable_Address command is used to get the current
//	  peer Resolvable Private Address being used for the corresponding peer Public
//	  and Random (static) Identity Address. The peer's resolvable address being
//	  used may change after the command is called.
//	  This command can be used at any time.
//	  When a Controller cannot find a Resolvable Private Address associated with
//	  the Peer Identity Address, it shall respond with error code 0x02 (Unknown
//	  Connection Identifier).
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.42)
//	    * @param Peer_Identity_Address_Type Identity address type.
//	    * Values:
//	    - 0x00: Public Identity Address
//	    - 0x01: Random (static) Identity Address
//	    * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
//	    * @param[out] Peer_Resolvable_Address Resolvable Private Address being used by the peer device
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_read_peer_resolvable_address(byte Peer_Identity_Address_Type, byte Peer_Identity_Address[6], byte Peer_Resolvable_Address[6]);
//
//	/**
//	  * @brief The LE_Read_Local_Resolvable_Address command is used to get the current
//	  local Resolvable Private Address being used for the corresponding peer
//	  Identity Address. The local's resolvable address being used may change after
//	  the command is called.
//	  This command can be used at any time.
//	  When a Controller cannot find a Resolvable Private Address associated with
//	  the Peer Identity Address, it shall respond with error code 0x02 (Unknown
//	  Connection Identifier).
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.43)
//	    * @param Peer_Identity_Address_Type Identity address type.
//	    * Values:
//	    - 0x00: Public Identity Address
//	    - 0x01: Random (static) Identity Address
//	    * @param Peer_Identity_Address Public or Random (static) Identity address of the peer device
//	    * @param[out] Local_Resolvable_Address Resolvable Private Address being used by the local device
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_read_local_resolvable_address(byte Peer_Identity_Address_Type, byte Peer_Identity_Address[6], byte Local_Resolvable_Address[6]);
//
//	/**
//	  * @brief The LE_Set_Address_Resolution_Enable command is used to enable
//	  resolution of Resolvable Private Addresses in the Controller. This causes the
//	  Controller to use the resolving list whenever the Controller receives a local or
//	  peer Resolvable Private Address.
//	  This command can be used at any time except when:
//	  - Advertising is enabled
//	  - Scanning is enabled
//	  - Create connection command is outstanding
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.44)
//	    * @param Address_Resolution_Enable Enable/disable address resolution in the controller.
//	    0x00: Address Resolution in controller disabled (default),
//	    0x01: Address Resolution in controller enabled
//	      * Values:
//	      - 0x00: Address Resolution in controller disabled (default)
//	      - 0x01: Address Resolution in controller enabled
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_set_address_resolution_enable(byte Address_Resolution_Enable);
//
//	/**
//	  * @brief The LE_Set_Resolvable_Private_Address_Timeout command set the length of
//	  time the controller uses a Resolvable Private Address before a new resolvable
//	  private address is generated and starts being used.
//	  This timeout applies to all addresses generated by the controller.
//	  (See Bluetooth Specification v.5.0, Vol. 2, Part E, 7.8.45)
//	    * @param RPA_Timeout RPA_Timeout measured in seconds.
//	    Range for N: 0x0001 - 0xA1B8 (1 sec - approximately 11.5 hours)
//	    Default: N= 0x0384 (900 secs or 15 minutes)
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_set_resolvable_private_address_timeout(ushort RPA_Timeout);
//
//	/**
//	  * @brief The LE_Read_Maximum_Data_Length command allows the Host to read the
//	  Controller’s maximum supported payload octets and packet duration times for
//	  transmission and reception (supportedMaxTxOctets and
//	  supportedMaxTxTime, supportedMaxRxOctets, and supportedMaxRxTime,
//	  see Bluetooth Specification v5.0 [Vol 6] Part B, Section 4.5.10). 
//	    * @param[out] supportedMaxTxOctets Maximum number of payload octets that the local Controller supports
//	    for transmission of a single Link Layer packet on a data connection.
//	      * Values:
//	      - 0x001B ... 0x00FB
//	      * @param[out] supportedMaxTxTime Maximum time, in microseconds, that the local Controller supports for
//	      transmission of a single Link Layer packet on a data connection.
//	        * Values:
//	        - 0x0148 ... 0x4290
//	        * @param[out] supportedMaxRxOctets Maximum number of payload octets that the local Controller supports
//	        for reception of a single Link Layer packet on a data connection.
//	          * Values:
//	          - 0x001B ... 0x00FB
//	          * @param[out] supportedMaxRxTime Maximum time, in microseconds, that the local Controller supports for
//	          reception of a single Link Layer packet on a data connection.
//	            * Values:
//	            - 0x0148 ... 0x4290
//	            * @retval Value indicating success or error code.
//	            */
//	static HCI::Status le_read_maximum_data_length(ushort *supportedMaxTxOctets, ushort *supportedMaxTxTime, ushort *supportedMaxRxOctets, ushort *supportedMaxRxTime);

	/**
	  * @brief The LE_Read_PHY command is used to read the current transmitter PHY and
	  receiver PHY on the connection identified by the Connection_Handle. see Bluetooth Specification [vol2] part E Section 7.8.47
	    * @param Connection_Handle Connection handle for which the command is given.
	    * Values:
	    - 0x0000 ... 0x0EFF
	    * @param[out] TX_PHY Transmitter PHY in use
	    * Values:
	    - 0x01: The transmitter PHY for the connection is LE 1M
	    - 0x02: The transmitter PHY for the connection is LE 2M
	    - 0x03: The transmitter PHY for the connection is LE Coded (Not Supported by STM32WB)
	    * @param[out] RX_PHY Receiver PHY in use
	    * Values:
	    - 0x01: The receiver PHY for the connection is LE 1M
	    - 0x02: The receiver PHY for the connection is LE 2M
	    - 0x03: The receiver PHY for the connection is LE Coded (Not Supported by STM32WB)
	    * @retval Value indicating success or error code.
	    */
	static HCI::Status readPhy(ushort handle, byte *txPhy, byte *rxPhy);

	/**
	  * @brief The LE_Set_Default_PHY command allows the Host to specify its preferred
	  values for the transmitter PHY and receiver PHY to be used for all subsequent
	  connections over the LE transport.
	  The ALL_PHYS parameter is a bit field that allows the Host to specify, for each
	  direction, whether it has no preference among the PHYs that the Controller
	  supports in a given direction or whether it has specified particular PHYs that it
	  prefers in the TX_PHYS or RX_PHYS parameter.
	  The TX_PHYS parameter is a bit field that indicates the transmitter PHYs that
	  the Host prefers the Controller to use. If the ALL_PHYS parameter specifies
	  that the Host has no preference, the TX_PHYS parameter is ignored;
	  otherwise at least one bit shall be set to 1.
	  The RX_PHYS parameter is a bit field that indicates the receiver PHYs that the
	  Host prefers the Controller to use. If the ALL_PHYS parameter specifies that
	  the Host has no preference, the RX_PHYS parameter is ignored; otherwise at
	  least one bit shall be set to 1. See Bluetooth Specification [Vol2] Part E Section 7.8.48
	    * @param ALL_PHYS Host preferences for TX PHY and RX PHY
	    * Values:
	    - 0x00 ... 0x03
	    * @param TX_PHYS Host preferences for TX PHY (no LE coded support)
	    * Values:
	    - 0x00 ... 0x03
	    * @param RX_PHYS Host preferences for RX PHY (no LE coded support)
	    * Values:
	    - 0x00 ... 0x03
	    * @retval Value indicating success or error code.
	    */
	static HCI::Status setDefaultPhy(byte all, byte tx, byte rx);

//	/**
//	  * @brief The LE_Set_PHY command is used to set the PHY preferences for the
//	  connection identified by the Connection_Handle. The Controller might not be
//	  able to make the change (e.g. because the peer does not support the
//	  requested PHY) or may decide that the current PHY is preferable.
//	  The ALL_PHYS parameter is a bit field that allows the Host to specify, for each
//	  direction, whether it has no preference among the PHYs that the Controller
//	  supports in a given direction or whether it has specified particular PHYs that it
//	  prefers in the TX_PHYS or RX_PHYS parameter.
//	  The TX_PHYS parameter is a bit field that indicates the transmitter PHYs that
//	  the Host prefers the Controller to use. If the ALL_PHYS parameter specifies
//	  that the Host has no preference, the TX_PHYS parameter is ignored;
//	  otherwise at least one bit shall be set to 1.
//	  The RX_PHYS parameter is a bit field that indicates the receiver PHYs that the
//	  Host prefers the Controller to use. If the ALL_PHYS parameter specifies that
//	  the Host has no preference, the RX_PHYS parameter is ignored; otherwise at
//	  least one bit shall be set to 1.
//	  If, for at least one direction, the Host has specified a preference and the current
//	  PHY is not one of those preferred, the Controller shall request a change.
//	  Otherwise the Controller may, but need not, request a change.
//	  The PHY preferences provided by the LE Set PHY command override those
//	  provided via the LE Set Default PHY command (Section 7.8.48) or any
//	  preferences previously set using the LE Set PHY command on the same
//	  connection.
//	  The PHY_options parameter is a bit field that allows the Host to specify options
//	  for PHYs. The default value for a new connection shall be all zero bits. The
//	  Controller may override any preferred coding for transmitting on the LE Coded
//	  PHY.
//	  The Host may specify a preferred coding even if it prefers not to use the LE
//	  Coded transmitter PHY since the Controller may override the PHY preference.
//	  see Bluetooth Specification v5.0 [Vol 6] Part B, Section 7.8.49 
//	    * @param Connection_Handle Connection handle for which the command is given.
//	    * Values:
//	    - 0x0000 ... 0x0EFF
//	    * @param ALL_PHYS Host preferences for TX PHY and RX PHY
//	    * Values:
//	    - 0x00 ... 0x03
//	    * @param TX_PHYS Host preferences for TX PHY (no LE coded support)
//	    * Values:
//	    - 0x00 ... 0x03
//	    * @param RX_PHYS Host preferences for RX PHY (no LE coded support)
//	    * Values:
//	    - 0x00 ... 0x03
//	    * @param PHY_options Not Supported by STM32WB
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status le_set_phy(ushort Connection_Handle, byte ALL_PHYS, byte TX_PHYS, byte RX_PHYS, ushort PHY_options);
//
//	/**
//	  * @brief This command is used to start a test where the DUT receives test reference
//	  packets at a fixed interval. The tester generates the test reference packets.
//	  see Bluetooth Specification v5.0 [Vol 6] Part B, Section 7.8.50 
//	    * @param RX_Frequency N = (F - 2402) / 2
//	    Frequency Range : 2402 MHz to 2480 MHz
//	      * Values:
//	      - 0x00 ... 0x27
//	      * @param PHY PHY to use for test packet
//	      * Values:
//	      - 0x00: Reserved for future use
//	      - 0x01: Transmitter set to use the LE 1M PHY
//	      - 0x02: Transmitter set to use the LE 2M PHY
//	      - 0x03: Transmitter set to use the LE Coded PHY with S=8 data coding
//	      - 0x04: Transmitter set to use the LE Coded PHY with S=2 data coding
//	      * @param Modulation_Index Modulation index capability of the transmitter
//	      * Values:
//	      - 0x00: Assume transmitter will have a standard modulation index
//	      - 0x01: Assume transmitter will have a stable modulation index
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_enhanced_receiver_test(byte RX_Frequency, byte PHY, byte Modulation_Index);
//
//	/**
//	  * @brief This command is used to start a test where the DUT generates test reference
//	  packets at a fixed interval. The Controller shall transmit at maximum power.
//	  An LE Controller supporting the LE_Enhanced Transmitter_Test command
//	  shall support Packet_Payload values 0x00, 0x01 and 0x02. An LE Controller
//	  supporting the LE Coded PHY shall also support Packet_Payload value 0x04 (not supported by STM32WB).
//	  An LE Controller may support other values of Packet_Payload. see Bluetooth Specification v5.0 [Vol 6] Part B, Section 7.8.51
//	    * @param TX_Frequency N = (F - 2402) / 2
//	    Frequency Range : 2402 MHz to 2480 MHz
//	      * Values:
//	      - 0x00 ... 0x27
//	      * @param Length_Of_Test_Data Length in bytes of payload data in each packet.
//	      * Values:
//	      - 0x00 ... 0x25
//	      * @param Packet_Payload Type of packet payload.
//	      * Values:
//	      - 0x00: Pseudo-Random bit sequence 9
//	      - 0x01: Pattern of alternating bits '11110000'
//	      - 0x02: Pattern of alternating bits '10101010'
//	      - 0x03: Pseudo-Random bit sequence 15
//	      - 0x04: Pattern of All '1' bits
//	      - 0x05: Pattern of All '0' bits
//	      - 0x06: Pattern of alternating bits '00001111'
//	      - 0x07: Pattern of alternating bits '0101'
//	      * @param PHY PHY to use for test packet
//	      * Values:
//	      - 0x00: Reserved for future use
//	      - 0x01: Transmitter set to use the LE 1M PHY
//	      - 0x02: Transmitter set to use the LE 2M PHY
//	      - 0x03: Transmitter set to use the LE Coded PHY with S=8 data coding
//	      - 0x04: Transmitter set to use the LE Coded PHY with S=2 data coding
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status le_enhanced_transmitter_test(byte TX_Frequency, byte Length_Of_Test_Data, byte Packet_Payload, byte PHY);
};