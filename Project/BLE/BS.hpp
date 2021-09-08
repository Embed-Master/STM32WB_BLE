#pragma once

#include "HCI.hpp"

class BS
{
	struct Context
	{
		ushort service;
		ushort level;
	};
	
	static Context context;
	
public:
	static void setValue(float voltage);
	static void init();
};