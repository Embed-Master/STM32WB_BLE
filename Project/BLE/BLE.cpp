#include "BLE.h"
#include "TL.h"
#include "utilities.h"
#include "CoreSettings.h"

void BLE::createServiceList()
{
	
}

void BLE::init()
{
	__NVIC_SetPriorityGrouping(3);
	__NVIC_SetPriority(IRQn_Type::IPCC_C1_RX_IRQn, 5);
	
	static const TL::Config config = { createServiceList, (char *)"Indy" };
	TL::init(&config);
}

void BLE::thread(void *args)
{
//	else vTaskSuspend(nullptr);

	
//		BaseType_t yield;
//	vTaskNotifyGiveFromISR(threadHandle, &yield);
//	portYIELD_FROM_ISR(yield);

}