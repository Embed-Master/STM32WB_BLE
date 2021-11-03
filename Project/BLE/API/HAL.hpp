#pragma once

#include "HCI.hpp"

class HAL
{
public:
	enum class Power : byte
	{
		_neg_40_dBm		= 0x00,
		_neg_20_85_dBm	= 0x01,
		_neg_19_75_dBm	= 0x02,
		_neg_18_85_dBm	= 0x03,
		_neg_17_6_dBm	= 0x04,
		_neg_16_5_dBm	= 0x05,
		_neg_15_25_dBm	= 0x06,
		_neg_14_1_dBm	= 0x07,
		_neg_13_15_dBm	= 0x08,
		_neg_12_05_dBm	= 0x09,
		_neg_10_9_dBm	= 0x0A,
		_neg_9_9_dBm	= 0x0B,
		_neg_8_85_dBm	= 0x0C,
		_neg_7_8_dBm	= 0x0D,
		_neg_6_9_dBm	= 0x0E,
		_neg_5_9_dBm	= 0x0F,
		_neg_4_95_dBm	= 0x10,
		_neg_4_dBm		= 0x11,
		_neg_3_15_dBm	= 0x12,
		_neg_2_45_dBm	= 0x13,
		_neg_1_8_dBm	= 0x14,
		_neg_1_3_dBm	= 0x15,
		_neg_0_85_dBm	= 0x16,
		_neg_0_5_dBm	= 0x17,
		_neg_0_15_dBm	= 0x18,
		_0_dBm			= 0x19,
		_1_dBm			= 0x1A,
		_2_dBm			= 0x1B,
		_3_dBm			= 0x1C,
		_4_dBm			= 0x1D,
		_5_dBm			= 0x1E,
		_6_dBm			= 0x1F
	};
	struct LinkStatus
	{
		byte status[8];
		ushort handle[8];
	};
	
private:
	enum class Opcode : ushort
	{
		WriteConfigData = 0xFC0C,
		SetTxPower      = 0xFC0F,
		GetLinkStatus   = 0xFC17,
		ReadRawRSSI     = 0xFC32
	};
	struct WriteConfigData
	{
		byte offset;
		byte length;
		byte value[BLE_CMD_MAX_PARAM_LEN - 2];
	} __attribute__((packed));
	struct setTxPowerCom
	{
		bool highPowerEn;
		byte power;
	} __attribute__((packed));
	struct GetLinkStatus
	{
		struct Response
		{
			HCI::Status status;
			LinkStatus link;
		} __attribute__((packed));
	};
	struct ReadRawRssi
	{
		struct Response
		{
			HCI::Status status;
			byte rssi[3];
		} __attribute__((packed));
	};

public:
//	/**
//	  * @brief This command returns the build number associated with the firmware version currently running
//	  * @param[out] Build_Number Build number of the firmware.
//	  * @retval Value indicating success or error code.
//	*/
//	static HCI::Status getFwBuildNumber(ushort *buildNumber);
//
	/**
	  * @brief This command writes a value to a low level configure data structure. It is useful to setup
	  directly some low level parameters for the system in the runtime.
	    * @param Offset Offset of the element in the configuration data structure
	    which has to be written. The valid offsets are:

	    - 0x00: Bluetooth public address, Value length to be written: 6 bytes
	    - 0x08: Encryption root key used to derive LTK and CSRK, Value length to be written: 16 bytes
	    - 0x18: Identity root key used to derive LTK and CSRK, Value length to be written: 16 bytes
	    - 0x2E: Static Random Address: 6 bytes
	      * Values:
	      - 0x00: CONFIG_DATA_PUBADDR_OFFSET
	      - 0x08: CONFIG_DATA_ER_OFFSET
	      - 0x18: CONFIG_DATA_IR_OFFSET
	      - 0x2E: CONFIG_DATA_RANDOM_ADDRESS_WR
	      * @param Length Length of data to be written
	      * @param Value Data to be written
	      * @retval Value indicating success or error code.
	      */
	static HCI::Status writeConfigData(byte offset, byte length, byte value[]);
//
//	/**
//	  * @brief This command requests the value in the low level configure data structure.
//	  The number of read bytes changes for different Offset. 
//	    * @param Offset Offset of the element in the configuration data structure
//	    which has to be read. The valid offsets are:
//
//	    * 0x00: Bluetooth public address, Value length returned: 6 bytes
//	    * 0x08: Encryption root key used to derive LTK and CSRK, Value length returned: 16 bytes
//	    * 0x18: Identity root key used to derive LTK and CSRK, Value length returned: 16 bytes
//	    * 0x80: Static random address. Value length returned: 6 bytes (read-only)
//	      * Values:
//	      - 0x00: CONFIG_DATA_PUBADDR_OFFSET
//	      - 0x08: CONFIG_DATA_ER_OFFSET
//	      - 0x18: CONFIG_DATA_IR_OFFSET
//	      - 0x80: CONFIG_DATA_RANDOM_ADDRESS
//	      * @param[out] Data_Length Length of Data in octets
//	      * @param[out] Data Data field associated with Offset parameter
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status readConfigData(byte offset, byte *length, byte data[]);
//
	/**
	  * @brief This command sets the TX power level of the device. By controlling the
	  PA_LEVEL, that determines the output power level (dBm) at the IC pin. 
	  When the system starts up or reboots, the default TX power level will be used, which is the
	  maximum value of 6 dBm. Once this command is given, the output power will be changed
	  instantly, regardless if there is Bluetooth communication going on or not. For example, for
	  debugging purpose, the device can be set to advertise all the time. And use this
	  command to observe the signal strength changing.
	  The system will keep the last received TX power level from the command, i.e. the 2nd
	  command overwrites the previous TX power level. The new TX power level remains until
	  another Set TX Power command, or the system reboots.
	    * @param En_High_Power Enable High Power mode - Deprecated and ignored on STM32WB
	    * Values:
	    - 0x00: Standard Power
	    - 0x01: High Power
	    * @param PA_Level Power amplifier output level. Output power is indicative and it depends on the PCB layout and associated 
	    components.Here the values are given at the IC pin
	      * Values:
	      - 0x00: -40 dBm
	      - 0x01: -20.85 dBm
	      - 0x02: -19.75 dBm
	      - 0x03: -18.85 dBm
	      - 0x04: -17.6 dBm
	      - 0x05: -16.5 dBm
	      - 0x06: -15.25 dBm
	      - 0x07: -14.1 dBm
	      - 0x08: -13.15 dBm
	      - 0x09: -12.05 dBm
	      - 0x0A: -10.9 dBm
	      - 0x0B: -9.9 dBm
	      - 0x0C: -8.85 dBm
	      - 0x0D: -7.8 dBm
	      - 0x0E: -6.9 dBm
	      - 0x0F: -5.9 dBm
	      - 0x10: -4.95 dBm
	      - 0x11: -4 dBm
	      - 0x12: -3.15 dBm
	      - 0x13: -2.45 dBm
	      - 0x14: -1.8 dBm
	      - 0x15: -1.3 dBm
	      - 0x16: -0.85 dBm
	      - 0x17: -0.5 dBm
	      - 0x18: -0.15 dBm
	      - 0x19: 0 dBm
	      - 0x1A: +1 dBm
	      - 0x1B: +2 dBm
	      - 0x1C: +3 dBm
	      - 0x1D: +4 dBm
	      - 0x1E: +5 dBm
	      - 0x1F: +6 dBm
	      * @retval Value indicating success or error code.
	      */
	static HCI::Status setTxPowerLevel(Power level, byte enHighPower);
//
//	/**
//	  * @brief This command returns the number of packets sent in Direct Test Mode.
//	  When the Direct TX test is started, a 32-bit counter is used to count how many packets have been transmitted. 
//	  This command can be used to check how many packets have been sent during the Direct TX test.
//	  The counter starts from 0 and counts upwards. The counter can wrap and start from 0 again. 
//	  The counter is not cleared until the next Direct TX test starts. 
//	    * @param[out] Number_Of_Packets Number of packets sent during the last Direct TX test.
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status leTxTestPacketNumber(uint *packetsNumber);
//
//	/**
//	  * @brief This command starts a carrier frequency, i.e. a tone, on a specific channel. The frequency
//	  sine wave at the specific channel may be used for debugging purpose only. The channel ID
//	  is a parameter from 0x00 to 0x27 for the 40 BLE channels, e.g. 0x00 for 2.402 GHz, 0x01
//	  for 2.404 GHz etc.
//	  This command should not be used when normal Bluetooth activities are ongoing.
//	  The tone should be stopped by @ref tone_stop command.
//	    * @param RF_Channel BLE Channel ID, from 0x00 to 0x27 meaning (2.402 + 2*0xXX) GHz
//	    Device will continuously emit 0s, that means that the tone
//	    will be at the channel center frequency less the maximum
//	    frequency deviation (250kHz).
//	      * Values:
//	      - 0x00 ... 0x27
//	      * @param Freq_offset Frequency Offset for tone channel
//	      * Values:
//	      - 0x00 ... 0xFF
//	      * @retval Value indicating success or error code.
//	      */
//	static HCI::Status toneStart(byte rfChannel, byte freqOffset);
//
//	/**
//	  * @brief This command is used to stop the previously started @ref tone_start command.
//	  * @retval Value indicating success or error code.
//	  */
//	static HCI::Status toneStop();

	/**
	  * @brief This command returns the status of the 8 Bluetooth low energy links managed by the device
	  * @param[out] Link_Status Array of link status (8 links). Each link status is 1 byte.
	  * @param[out] Link_Connection_Handle Array of connection handles (2 bytes) for 8 links.
	  * @retval Value indicating success or error code.
	  */
	static HCI::Status getLinkStatus(LinkStatus &status);
//
//	/**
//	  * @brief This command set the bitmask associated to @ref end_of_radio_activity_event. 
//	  Only the radio activities enabled in the mask will be reported to application by @ref end_of_radio_activity_event
//	    * @param Radio_Activity_Mask Bitmask of radio events
//	    * Flags:
//	    - 0x0001: Idle
//	    - 0x0002: Advertising
//	    - 0x0004: Connection event slave
//	    - 0x0008: Scanning
//	    - 0x0010: Connection request
//	    - 0x0020: Connection event master
//	    - 0x0040: TX test mode
//	    - 0x0080: RX test mode
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status setRadioActivityMask(ushort mask);
//
//	/**
//	  * @brief This command returns information about the Anchor Period to help application in selecting 
//	                      slot timings when operating in multi-link scenarios.
//	                    * @param[out] Anchor_Period Current anchor period.
//	                    T = N * 0.625 ms.
//	                      * @param[out] Max_Free_Slot Maximum available time that can be allocated for a new slot.
//	                      T = N * 0.625 ms.
//	                        * @retval Value indicating success or error code.
//	                        */
//	static HCI::Status getAnchorPeriod(uint *period, uint *maxFreeSlot);
//
//	/**
//	  * @brief This command is used to enable/disable the generation of HAL events 
//	  * @param Event_Mask Mask to enable/disable generation of HAL events
//	  * Flags:
//	  - 0x00000000: No events specified (Default)
//	  - 0x00000001: ACI_HAL_SCAN_REQ_REPORT_EVENT
//	  * @retval Value indicating success or error code.
//	  */
//	static HCI::Status setEventMask(uint mask);
//
//	/**
//	  * @brief This command is used to provide a specific engineering setup to the Security Manager Protocol Layer. It may be used during development/debug only!
//	  * @param SMP_Config Mask to configure SMP engineering knobs
//	  * Flags:
//	  - 0x00000000: Default config (all reset)
//	  - 0x00000001: Cheat Level 1 ON
//	  - 0x00000002: RFU
//	  - 0x00000003: Cheat Level 3 ON
//	  - 0x00000004: RFU
//	  - 0x00000005: Cheat Level 5 ON
//	  - 0x00000006: Cheat Level 6 ON
//	  - 0x00000007: Cheat Level 7 ON
//	  - 0x00000010: DBG messages ON
//	  - 0x00000100: Debug Public Key ON
//	  - 0x00000107: Debug KEY On + DBG msg Off + CL=7
//	  - 0x00000117: Debug KEY On + DBG msg On + CL=7
//	  * @retval Value indicating success or error code.
//	  */
//	static HCI::Status setSmpEngConfig(uint config);
//
//	/**
//	  * @brief This command is used to retrieve TX, RX and total buffer count allocated for ACL packets.
//	  * @param[out] Allocated_For_TX MBlocks allocated for TXing
//	  * @param[out] Allocated_For_RX MBlocks allocated for RXing
//	  * @param[out] Allocated_MBlocks Overall allocated MBlocks
//	  * @retval Value indicating success or error code.
//	  */
//	static HCI::Status getPmDebugInfo(byte *allocatedForTx, byte *allocatedForRx, byte *allocatedMblocks);
//
//	/**
//	  * @brief This command Reads Register value from the RF module 
//	  * @param Register_Address Address of the register to be read
//	  * @param[out] reg_val Register value
//	  * @retval Value indicating success or error code.
//	  */
//	static HCI::Status readRadioReg(byte address, byte *value);
//
//	/**
//	  * @brief This command writes Register value to the RF module 
//	  * @param Register_Address Address of the register to be written
//	  * @param Register_Value Value to be written
//	  * @retval Value indicating success or error code.
//	  */
//	static HCI::Status writeRadioReg(byte address, byte value);

	/**
	  * @brief This command returns the raw value of the RSSI 
	  * @param[out] Value RAW RSSI value
	  * @retval Value indicating success or error code.
	  */
	static HCI::Status readRawRssi(byte rssi[3]);

//	/**
//	  * @brief This command does set up the RF to listen to a specific RF channel 
//	  * @param RF_Channel BLE Channel ID, from 0x00 to 0x27 meaning (2.402 + 2*0xXX) GHz
//	  Device will continuously emit 0s, that means that the tone
//	  will be at the channel center frequency less the maximum
//	  frequency deviation (250kHz).
//	    * Values:
//	    - 0x00 ... 0x27
//	    * @retval Value indicating success or error code.
//	    */
//	static HCI::Status rxStart(byte channel);
//
//	/**
//	  * @brief This command stop a previous ACI_HAL_RX_START command 
//	  * @retval Value indicating success or error code.
//	  */
//	static HCI::Status rxStop();
//
//	/**
//	  * @brief This command is equivalent to HCI_RESET but ensures the sleep mode is entered' immediately after its completion
//	  * @retval Value indicating success or error code.
//	  */
//	static HCI::Status stackReset();
};