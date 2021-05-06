#pragma once

#include "FreeRTOS.h"
#include "task.h"

class BLE
{
//	static TaskHandle_t threadHandle;
	static void createServiceList();
	static void thread(void *args);
	
public:
	static void init();
};