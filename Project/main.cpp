#include "SMPS.h"
#include "FreeRTOS.h"
#include "task.h"
#include "BLE.h"
#include "Debug.h"

int main(void)
{
	SMPS::init(SMPS::Voltage::_1V40, SMPS::Current::_80MA, SMPS::Source::HSE);
	BLE::init();
	
	vTaskStartScheduler();
	
	while (true) ;
}

extern "C" void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
	static bool once = true;
	while (true)
	{
		if (once)
		{
			once = false;
			serial.sendLine("Stack overflow");
		}
	}
}
/*
	auto pt = xTimerCreate("Send", 1000, pdTRUE, 0, send);
	xTimerStart(pt, 0);
	
	if (xTaskCreate(thread, "MyTask", configMINIMAL_STACK_SIZE, nullptr, 0, &task) == pdPASS) serial.sendLine("Task MyTask created");
	else serial.sendLine("Task MyTask creation failed");
*/