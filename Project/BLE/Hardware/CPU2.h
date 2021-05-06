#pragma once

#include "Types.h"
#include "CoreSettings.h"

class CPU2
{
	struct GpioConfig
	{
		GPIO_TypeDef* port;
		ushort pin;
		byte enable;
		byte reserved;
	} __attribute__((packed));
	struct TracesConfig
	{
		byte thread_config;
		byte ble_config;
		byte mac_802_15_4_config;
		byte zigbee_config;
	} __attribute__((packed));
	struct GeneralConfig
	{
		byte ble_dtb_cfg;
		byte reserved[3];
	} __attribute__((packed));
	struct Header
	{
		uint MetaData[3];
	} __attribute__((packed));
	struct DebugInitCmdParam
	{
		byte *pGpioConfig;
		byte *pTracesConfig;
		byte *pGeneralConfig;
		byte GpioConfigSize;
		byte TracesConfigSize;
		byte GeneralConfigSize;
	} __attribute__((packed));
	struct DebugInitCmdPacket
	{
		Header header;
		DebugInitCmdParam param;
	} __attribute__((packed));
	
	static const byte GPIO_NBR_OF_RF_SIGNALS = 9;
	static const byte GPIO_CFG_NBR_OF_FEATURES = 34;
	static const byte NBR_OF_TRACES_CONFIG_PARAMETERS = 4;
	static const byte NBR_OF_GENERAL_CONFIG_PARAMETERS = 4;
	static const GpioConfig gpioConfigList[GPIO_CFG_NBR_OF_FEATURES];
	static TracesConfig tracesConfig;
	static GeneralConfig generalConfig;
	
public:
	static void enable();
	static void setup();
};