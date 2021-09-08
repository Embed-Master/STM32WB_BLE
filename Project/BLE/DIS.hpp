#pragma once

#include "HCI.hpp"
#include "StackConfig.hpp"
#include "string.h"

class DIS
{
	struct Context
	{
		ushort service;
		ushort manufacturer;
		ushort model;
		ushort serial;
		ushort hardware;
		ushort software;
		ushort firmware;
	};
	
	static Context context;
	
public:
	struct Settings
	{
	public:
		char manufacturer[16];
		char model[16];
		byte serial[6];
		char hardware[16];
		char firmware[16];
		void setSerial(byte *serial) { memcpy(this->serial, serial, 6); }
	};
	static void init(Settings &settings);
};