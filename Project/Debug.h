#pragma once

#include "Serial.h"

class Debug
{
public:
	static void traceBuf(const void *ptr, uint length, const char *format, ...);
	static void enterToFunction(const char *name);
};

extern Serial serial;