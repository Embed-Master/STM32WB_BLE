#pragma once

#include "FreeRTOS.h"
#include "task.h"
#include "Types.h"
#include "TL.hpp"
#include "timers.h"
#include "string.h"
#include "DIS.hpp"

class BLE
{
public:
	class Settings
	{
	public:
		char name[32];
		DIS::Settings dis;
		/*
			Time interval = 0.625ms * value
			Min = 20ms = 0x20
			Max = 10240ms = 0x4000
		*/
		struct AdvertiseInterval
		{
			ushort min;
			ushort max;
		} advInterval;
		Settings();
	};
	enum class Status
	{
		Success,
		EmptyParameters,
		InvalidParameters,
		InitalizeError
	};
	enum class Notification : byte
	{
		Connection,
		Disconnection
	};
	enum class Connection : byte
	{
		Idle,
		Advertasing,
		Scan,
		LowPowerConnecting,
		ConnectedServer,
		ConnectedClient
	};
	private:
	static constexpr char connectionName[][20] = 
	{ 
		{"Idle"},
		{"Advertasing"},
		{"Scan"},
		{"Connecting"},
		{"ConnectedServer"},
		{"ConnectedClient"}
	};
	struct Context
	{
		struct Settings
		{
			struct Security
			{
				byte ioCapability;// IO capability of the device
				byte mitmMode;// Authentication requirement of the device; Man In the Middle protection required?
				byte bondingMode;// bonding mode of the device
				byte OOBdataPresent;// Flag to tell whether OOB data has to be used during the pairing process
				byte OOBdata[16];// OOB data to be used in the pairing process if OOB_Data_Present is set to TRUE
				/**
				 * this variable indicates whether to use a fixed pin
				 * during the pairing process or a passkey has to be
				 * requested to the application during the pairing process
				 * 0 implies use fixed pin and 1 implies request for passkey
				 */
				byte useFixedPin; 
				byte keySizeMin;// minimum encryption key size requirement
				byte keySizeMax;// maximum encryption key size requirement
				uint fixedPin;// fixed pin to be used in the pairing process if Use_Fixed_Pin is set to 1
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
				byte initSecurity;
			} security;// security requirements of the host
			ushort GAP;// gap service handle
			ushort name;// device name characteristic handle
			ushort appearance;// appearance characteristic handle
			ushort handle;// connection handle of the current active connection; When not in connection, the handle is set to 0xFFFF
			byte UUIDlen;// length of the UUID list to be used while advertising
			byte UUID[100];// the UUID list to be used while advertising
		}settings;
		Connection connection;
	};
	
	static byte manufacturer[14];
	static const byte configIRvalue[16];// Identity root key used to derive LTK and CSRK
	static const byte configERvalue[16];// Encryption root key used to derive LTK and CSRK
	static Context context;
	static Settings settings;
	static Status status;
	static void (*appNotificationCallback[BLE_APP_NOTIFICATION_CALLBACK_CNT])(Notification notification);
	
	static void secondStage(TaskHandle_t thread);
	static void advRequest(Connection status, char *name, ushort advTimeMin, ushort advTimeMax, byte uuidLen = 0, byte *uuid = nullptr);
	
public:
	static void appNotification(TL::Event *evt);
	static Status init(Settings &settings);
	static Status getStatus() { return status; }
	static Connection getConnection() { return context.connection; }
	static ushort getConnectionHandle() { return context.settings.handle; }
	static bool addNotificationCallback(void (ptr)(Notification));
};