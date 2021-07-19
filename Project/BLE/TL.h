#pragma once

#include "Types.h"
#include "BLEList.h"
#include "config.h"
#include "FreeRTOS.h"
#include "task.h"

#define DIVC( x, y )         (((x)+(y)-1)/(y))

#define TL_CMD_HDR_SIZE                (4)
#define TL_EVT_HDR_SIZE                (3)
#define TL_EVT_CS_PAYLOAD_SIZE         (4)

#define TL_BLEEVT_CS_PACKET_SIZE       (TL_EVT_HDR_SIZE + sizeof(CsEvt))
#define TL_BLEEVT_CS_BUFFER_SIZE       (sizeof(PacketHeader) + TL_BLEEVT_CS_PACKET_SIZE)

#define TL_BLEEVT_CC_OPCODE            (0x0E)
#define TL_BLEEVT_CS_OPCODE            (0x0F)
#define TL_BLEEVT_VS_OPCODE            (0xFF)

#define IPCC_CHANNEL_BLE	0
#define IPCC_CHANNEL_SYSTEM	1
#define IPCC_CHANNEL_TRACE	3
#define IPCC_CHANNEL_HCI	5

class TL
{
	struct Mailbox
	{
		/**
		 * Version
		 * [0:3]   = Build - 0: Untracked - 15:Released - x: Tracked version
		 * [4:7]   = branch - 0: Mass Market - x: ...
		 * [8:15]  = Subversion
		 * [16:23] = Version minor
		 * [24:31] = Version major
		 *
		 * Memory Size
		 * [0:7]   = Flash ( Number of 4k sector)
		 * [8:15]  = Reserved ( Shall be set to 0 - may be used as flash extension )
		 * [16:23] = SRAM2b ( Number of 1k sector)
		 * [24:31] = SRAM2a ( Number of 1k sector)
		 */
		struct SafeBootInfo
		{
			uint    Version;
		} __attribute__((packed)) ;
		struct FusInfo
		{
			uint    Version;
			uint    MemorySize;
			uint    FusInfo;
		} __attribute__((packed));
		struct WirelessFwInfo
		{
			uint    Version;
			uint    MemorySize;
			uint    InfoStack;
			uint    Reserved;
		} __attribute__((packed));
		struct DeviceInfoTable
		{
			SafeBootInfo      safeBootInfoTable;
			FusInfo           fusInfoTable;
			WirelessFwInfo    wirelessFwInfoTable;
		} __attribute__((aligned(4))) info;
		struct Ble
		{
			byte     *pcmd_buffer;
			byte     *pcs_buffer;
			byte     *pevt_queue;
			byte     *phci_acl_data_buffer;
		} __attribute__((aligned(4))) ble;
		struct Thread
		{
			byte   *notack_buffer;
			byte   *clicmdrsp_buffer;
			byte   *otcmdrsp_buffer;
		} __attribute__((aligned(4))) thread;
		struct LldTests
		{
			byte   *clicmdrsp_buffer;
			byte   *m0cmd_buffer;
		} __attribute__((aligned(4))) lldTests;
		struct LldBle
		{
			byte   *cmdrsp_buffer;
			byte   *m0cmd_buffer;
		} __attribute__((aligned(4))) lldBle;
		struct Zigbee
		{
			byte   *notifM0toM4_buffer;
			byte   *appliCmdM4toM0_buffer;
			byte   *requestM0toM4_buffer;
		} __attribute__((aligned(4))) zigbee;
		struct System
		{
			byte   *pcmd_buffer;
			byte   *sys_queue;
		} __attribute__((aligned(4))) system;
		struct MemManager
		{
			byte	*spare_ble_buffer;
			byte	*spare_sys_buffer;
			byte	*blepool;
			uint	blepoolsize;
			byte	*pevt_free_buffer_queue;
			byte	*traces_evt_pool;
			uint	tracespoolsize;
		} __attribute__((aligned(4))) memManager;
		struct TracesTable
		{
			byte   *traces_queue;
		} __attribute__((aligned(4))) traces;
		struct Mac_802_15_4
		{
			byte   *p_cmdrsp_buffer;
			byte   *p_notack_buffer;
			byte   *evt_queue;
		} __attribute__((aligned(4))) mac_802_15_4;
	};
	struct RefTable
	{
		Mailbox::DeviceInfoTable	*info;
		Mailbox::Ble				*ble;
		Mailbox::Thread				*thread;
		Mailbox::System				*system;
		Mailbox::MemManager			*memoryManager;
		Mailbox::TracesTable		*trace;
		Mailbox::Mac_802_15_4		*mac_802_15_4;
		Mailbox::Zigbee				*zigbee;
		Mailbox::LldTests			*lldTests;
		Mailbox::LldBle				*lldBle;
	};
	
	struct PacketHeader
	{
		uint *next;
		uint *prev;
	} __attribute__((packed));
	enum class PacketType : byte
	{
		BLECMD     = 0x01,
		ACL_DATA   = 0x02,
		BLEEVT     = 0x04,
		OTCMD      = 0x08,
		OTRSP      = 0x09,
		CLICMD     = 0x0A,
		OTNOT      = 0x0C,
		OTACK      = 0x0D,
		CLINOT     = 0x0E,
		CLIACK     = 0x0F,
		SYSCMD     = 0x10,
		SYSRSP     = 0x11,
		SYSEVT     = 0x12,
		CLIRESP    = 0x15,
		M0CMD      = 0x16,
		LOCCMD     = 0x20,
		LOCRSP     = 0x21,
		TRACES_APP = 0x40,
		TRACES_WL  = 0x41
	};
	
	struct CsEvt
	{
		byte	status;
		byte	numcmd;
		ushort	cmdcode;
	} __attribute__((packed));
	struct CcEvt
	{
		byte   numcmd;
		ushort  cmdcode;
		byte   payload[1];
	} __attribute__((packed));
	struct AsynchEvt
	{
		ushort subevtcode;
		byte   payload[1];
	} __attribute__((packed));
public:
	struct Event
	{
		byte   evtcode;
		byte   plen;
		byte   payload[1];
	} __attribute__((packed));
private:
	struct EvtSerial
	{
		byte   type;
		Event  evt;
	} __attribute__((packed));
	struct EvtPacket
	{
		PacketHeader  header;
		EvtSerial     serial;
	} __attribute__((packed));
	
	struct Cmd
	{
		ushort   code;
		byte   length;
		byte   payload[255];
	} __attribute__((packed));
	struct CmdSerial
	{
		byte   type;
		Cmd  cmd;
	} __attribute__((packed));
	struct Packet
	{
		PacketHeader  header;
		CmdSerial     serial;
	} __attribute__((packed));
	
	struct Header
	{
		uint MetaData[3];
	} __attribute__((packed));
	struct BleInitCmdParam
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
	} ;
	struct BleInitCmdPacket
	{
		Header header; /** Does not need to be initialized by the user */
		BleInitCmdParam parameter;
	} __attribute__((packed));
	
	class SHCI
	{
		enum class CmdStatus : byte
		{
			Busy,
			Available
		};
		enum class CmdRespStatus : byte
		{
			Release,
			Wait
		};
		static const byte OCF_BASE = 0x50;
		static const byte OGF = 0x3F;// OpCode Group Field
		enum class OCF : byte// OpCode Command Field
		{
			RESERVED1 = OCF_BASE,
			RESERVED2,
			FUS_GET_STATE,
			FUS_RESERVED1,
			FUS_FW_UPGRADE,
			FUS_FW_DELETE,
			FUS_UPDATE_AUTH_KEY,
			FUS_LOCK_AUTH_KEY,
			FUS_STORE_USR_KEY,
			FUS_LOAD_USR_KEY,
			FUS_START_WS,
			FUS_RESERVED2,
			FUS_RESERVED3,
			FUS_LOCK_USR_KEY,
			FUS_RESERVED5,
			FUS_RESERVED6,
			FUS_RESERVED7,
			FUS_RESERVED8,
			FUS_RESERVED9,
			FUS_RESERVED10,
			FUS_RESERVED11,
			FUS_RESERVED12,
			BLE_INIT,
			THREAD_INIT,
			DEBUG_INIT,
			FLASH_ERASE_ACTIVITY,
			CONCURRENT_SET_MODE,
			FLASH_STORE_DATA,
			FLASH_ERASE_DATA,
			RADIO_ALLOW_LOW_POWER,
			MAC_802_15_4_INIT,
			REINIT,
			ZIGBEE_INIT,
			LLD_TESTS_INIT,
			EXTPA_CONFIG,
			SET_FLASH_ACTIVITY_CONTROL,
			LLD_BLE_INIT
		};
		
		static TaskHandle_t eventHandlerHandle;
		static Packet packet;
		static List::Node evtQueue;
		static List::Node asynchEventQueue;
		static void (* secondStage)();
		
		static void commandTrace(Packet *cmd);
		static void eventTrace(EvtPacket *evt);
		static void responseTrace(EvtPacket *evt);
		static void eventHandler(void *args);
		static void eventCallback();
		static void cmdEventCallback();
		
	public:
		enum class Opcode : ushort
		{
			C2_BLE_INIT = ((OGF << 10) + (byte)OCF::BLE_INIT)
		};
		
		static void send(ushort cmdCode, byte length, byte * payload, EvtPacket * evt = nullptr);
		static void init(void (* _secondStage)());
	};
public:
	class HCI
	{
		enum class CmdStatus : byte
		{
			Busy,
			Available
		};
		struct InitConf
		{
			byte *p_cmdbuffer;
			void (* StatusNotCallBack)(CmdStatus status);
		};
		struct Request
		{
			ushort	ogf;
			ushort	ocf;
			int		event;
			void	*cparam;
			int		clen;
			void	*rparam;
			int		rlen;
		};
		enum class Status : byte
		{
			Success					= 0x00,
			SecUnknownConnectionID	= 0x40,
			Failed					= 0x41,
			InvalidParams			= 0x42,
			Busy					= 0x43,
			Pending					= 0x45,
			NotAllowed				= 0x46,
			Error					= 0x47,
			OutOfMemory				= 0x48,
			InvalidCID				= 0x50,
			DevInBlacklist			= 0x59,
			CsrkNotFound			= 0x5A,
			IrkNotFound				= 0x5B,
			DevNotFoundInDb			= 0x5C,
			SecDbFull				= 0x5D,
			DevNotBonded			= 0x5E,
			InsufficientEncKeysize	= 0x5F,
			InvalidHandle			= 0x60,
			OutOfHandle				= 0x61,
			InvalidOperation		= 0x62,
			CharacAlreadyExists		= 0x63,
			InsufficientResources	= 0x64,
			SecPermissionError		= 0x65,
			AddrNotResolved			= 0x70,
			Timeout					= 0xFF
		};
		enum class Opcode : ushort
		{
			
		};
		struct SetDefaultPhyCP
		{
			byte ALL_PHYS;
			byte TX_PHYS;
			byte RX_PHYS;
		} __attribute__((packed));
		struct tSecurityParams
		{
			byte ioCapability;// IO capability of the device
			byte mitm_mode;// Authentication requirement of the device; Man In the Middle protection required?
			byte bonding_mode;// bonding mode of the device
			byte OOB_Data_Present;// Flag to tell whether OOB data has to be used during the pairing process
			byte OOB_Data[16];// OOB data to be used in the pairing process if OOB_Data_Present is set to TRUE
			/**
			 * this variable indicates whether to use a fixed pin
			 * during the pairing process or a passkey has to be
			 * requested to the application during the pairing process
			 * 0 implies use fixed pin and 1 implies request for passkey
			 */
			byte Use_Fixed_Pin; 
			byte encryptionKeySizeMin;// minimum encryption key size requirement
			byte encryptionKeySizeMax;// maximum encryption key size requirement
			uint Fixed_Pin;// fixed pin to be used in the pairing process if Use_Fixed_Pin is set to 1
			/**
			 * this flag indicates whether the host has to initiate
			 * the security, wait for pairing or does not have any security
			 * requirements.\n
			 * 0x00 : no security required
			 * 0x01 : host should initiate security by sending the slave security
			 *        request command
			 * 0x02 : host need not send the clave security request but it
			 * has to wait for paiirng to complete before doing any other
			 * processing
			 */
			byte initiateSecurity;
		};
		struct BleGlobalContext_t
		{
			tSecurityParams bleSecurityParam;// security requirements of the host
			ushort gapServiceHandle;// gap service handle
			ushort devNameCharHandle;// device name characteristic handle
			ushort appearanceCharHandle;// appearance characteristic handle
			ushort connectionHandle;// connection handle of the current active connection; When not in connection, the handle is set to 0xFFFF
			byte advtServUUIDlen;// length of the UUID list to be used while advertising
			byte advtServUUID[100];// the UUID list to be used while advertising
		};
		typedef enum
		{
			APP_BLE_IDLE,
			APP_BLE_FAST_ADV,
			APP_BLE_LP_ADV,
			APP_BLE_SCAN,
			APP_BLE_LP_CONNECTING,
			APP_BLE_CONNECTED_SERVER,
			APP_BLE_CONNECTED_CLIENT
		} APP_BLE_ConnStatus_t;
		typedef struct
		{
			BleGlobalContext_t BleApplicationContext_legacy;
			APP_BLE_ConnStatus_t Device_Connection_Status;
			byte Advertising_mgr_timer_Id;// ID of the Advertising Timeout

		}BleApplicationContext_t;
		
		class ACI
		{
			struct WriteConfigDataCP
			{
				byte Offset;
				byte Length;
				byte Value[(BLE_CMD_MAX_PARAM_LEN - 2) / sizeof(byte)];
			} __attribute__((packed));
			struct setTxPowerCP
			{
				bool highPowerEn;
				byte power;
			} __attribute__((packed));
			struct GapInitCP
			{
				byte Role;
				byte privacy_enabled;
				byte device_name_char_len;
			} __attribute__((packed));
			struct GapInitRP
			{
				Status status;
				ushort Service_Handle;
				ushort Dev_Name_Char_Handle;
				ushort Appearance_Char_Handle;
			} __attribute__((packed));
			struct GattUpdateCharValueCP
			{
				ushort Service_Handle;
				ushort Char_Handle;
				byte Val_Offset;
				byte Char_Value_Length;
				byte Char_Value[(BLE_CMD_MAX_PARAM_LEN - 6) / sizeof(byte)];
			} __attribute__((packed));
			struct GapSetAuthenticationRequirementCP
			{
				byte Bonding_Mode;
				byte MITM_Mode;
				byte SC_Support;
				byte KeyPress_Notification_Support;
				byte Min_Encryption_Key_Size;
				byte Max_Encryption_Key_Size;
				byte Use_Fixed_Pin;
				uint Fixed_Pin;
				byte Identity_Address_Type;
			} __attribute__((packed));
			
		public:
			enum class Power : byte
			{
				_0dBm = 0x18
			};
			static Status gapConfigureWhitelist();
			static Status gapSetAuthenticationRequirement(	byte Bonding_Mode, byte MITM_Mode, byte SC_Support, byte KeyPress_Notification_Support, byte Min_Encryption_Key_Size,
															byte Max_Encryption_Key_Size, byte Use_Fixed_Pin, uint Fixed_Pin, byte Identity_Address_Type);
			static Status gapSetIOcapability(byte IO_Capability);
			static Status gattUpdateCharValue(ushort Service_Handle, ushort Char_Handle, byte Val_Offset, byte Char_Value_Length, byte Char_Value[]);
			static Status gapInit(byte role, bool privacy, byte device_name_char_len, ushort *Service_Handle, ushort *Dev_Name_Char_Handle, ushort *Appearance_Char_Handle);
			static Status gattInit();
			static Status setTxPower(Power power, bool highPowerEn);
			static Status writeConfigData(byte Offset, byte Length, byte Value[]);
			static Status sendReqPrepare(byte *cmd, ushort ogf, ushort ocf, int clen);
		};
		
		static TaskHandle_t eventHandlerHandle;
		static Packet packet;
		static List::Node evtQueue;
		static List::Node cmdEventQueue;
		static List::Node asynchEventQueue;
		static byte csBuffer[sizeof(PacketHeader) + TL_EVT_HDR_SIZE + sizeof(CsEvt)];
		static const byte configIRvalue[16];// Identity root key used to derive LTK and CSRK
		static const byte configERvalue[16];// Encryption root key used to derive LTK and CSRK
		static BleApplicationContext_t BleApplicationContext;

		static byte mac[6];
		static byte manufacturer[14];
		
		static void eventCallback();
		static void eventHandler(void *args);
		static void sendCommand(Opcode opcode, byte plen, void *param);
		static int sendRequest(Request *p_cmd, bool async = false);
		static void SVCCTLinit();
		static Status setDefaultPhy(byte ALL_PHYS, byte TX_PHYS, byte RX_PHYS);
		static void initMac(byte *buf);
		static Status reset();
		
	public:
		class Service
		{
		public:
			enum class EvtAckStatus : byte
			{
				NotAck,
				FlowEnable,
				FlowDisable,
			};
		
			static void thread();
			static void addService(EvtAckStatus(* evtHandler)(Event *));
			static void init();
		private:
			enum class UserEvtFlow : byte
			{
				Disable,
				Enable,
			};
			struct EvtHandler
			{
				EvtAckStatus(* ptr[BLE_CFG_SVCCTL_MAX])(Event *evt);
				byte count;
			};
			struct CltHandler
			{
				EvtAckStatus(* ptr[BLE_CFG_SVCCTL_MAX])(Event *evt);
				byte count;
			};
			struct DeviceInfoContext
			{
				ushort DeviceInformationSvcHdle; /**< Service handle */
#if (BLE_CFG_DIS_MANUFACTURER_NAME_STRING != 0)
				ushort ManufacturerNameStringCharHdle; /**< Characteristic handle */
#endif
#if (BLE_CFG_DIS_MODEL_NUMBER_STRING != 0)
				ushort ModelNumberStringCharHdle; /**< Characteristic handle */
#endif
#if (BLE_CFG_DIS_SERIAL_NUMBER_STRING != 0)
				ushort SerialNumberStringCharHdle; /**< Characteristic handle */
#endif
#if (BLE_CFG_DIS_HARDWARE_REVISION_STRING != 0)
				ushort HardwareRevisionStringCharHdle; /**< Characteristic handle */
#endif
#if (BLE_CFG_DIS_FIRMWARE_REVISION_STRING != 0)
				ushort FirmwareRevisionStringCharHdle; /**< Characteristic handle */
#endif
#if (BLE_CFG_DIS_SOFTWARE_REVISION_STRING != 0)
				ushort SoftwareRevisionStringCharHdle; /**< Characteristic handle */
#endif
#if (BLE_CFG_DIS_SYSTEM_ID != 0)
				ushort SystemIDCharHdle; /**< Characteristic handle */
#endif
#if (BLE_CFG_DIS_IEEE_CERTIFICATION != 0)
				ushort IEEECertificationCharHdle; /**< Characteristic handle */
#endif
#if (BLE_CFG_DIS_PNP_ID != 0)
				ushort PNPIDCharHdle; /**< Characteristic handle */
#endif
			};
		
			static EvtHandler evtHandlerList;
			static CltHandler cltHandlerList;
			static DeviceInfoContext context;
		};
		
		static void init(byte *_mac = nullptr, byte *_sra = nullptr);
//		static void preinit();
	};
private:	
	class MemoryManager
	{
		static List::Node freeBufQueue;
		static List::Node localFreeBufQueue;	
		static const uint poolSize = (CFG_TLBLE_EVT_QUEUE_LENGTH * 4 * DIVC((sizeof(TL::PacketHeader) + TL_BLE_EVENT_FRAME_SIZE), 4));
		static byte evtPool[poolSize];
		static byte systemSpareEvtBuffer[sizeof(PacketHeader) + TL_EVT_HDR_SIZE + 255U];
		static byte bleSpareEvtBuffer[sizeof(PacketHeader) + TL_EVT_HDR_SIZE + 255];
		
		static void sendFreeBuf();
		static void trace(EvtPacket * phcievt);
		static void callback();
		
	public:
		static void evtDone(EvtPacket * evt);
		static void init();
	};
	class Trace
	{
		static List::Node evtQueue;
		
		static void eventCallback();
	public:
		static void init();	
	};
	
	static Mailbox mailbox;
	static RefTable refTable;
	
	static void secondStageInit();
	
public:
	struct Config
	{
		void (* serviceCreationHandler)();
		char *name;
	};
	
	static void init(const Config *config);
};