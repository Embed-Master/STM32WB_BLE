#include "CPU2.h"
#include "utilities.h"
#include "TL.h"

const CPU2::GpioConfig CPU2::gpioConfigList[CPU2::GPIO_CFG_NBR_OF_FEATURES] =
{
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* BLE_ISR - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* BLE_STACK_TICK - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* BLE_CMD_PROCESS - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* BLE_ACL_DATA_PROCESS - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* SYS_CMD_PROCESS - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* RNG_PROCESS - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* NVM_PROCESS - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_GENERAL - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_BLE_CMD_RX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_BLE_EVT_TX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_BLE_ACL_DATA_RX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_SYS_CMD_RX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_SYS_EVT_TX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_CLI_CMD_RX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_OT_CMD_RX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_OT_ACK_TX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_CLI_ACK_TX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_MEM_MANAGER_RX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IPCC_TRACES_TX - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* HARD_FAULT - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* IP_CORE_LP_STATUS - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* END_OF_CONNECTION_EVENT - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* TIMER_SERVER_CALLBACK - Toggle on Entry */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* PES_ACTIVITY - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* MB_BLE_SEND_EVT - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* BLE_NO_DELAY - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* BLE_STACK_STORE_NVM_CB - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* NVMA_WRITE_ONGOING - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* NVMA_WRITE_COMPLETE - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* NVMA_CLEANUP - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* NVMA_START - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* FLASH_EOP - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* FLASH_WRITE - Set on Entry / Reset on Exit */
    { GPIOA, GPIO_BSRR_BS0, 0, 0},  /* FLASH_ERASE - Set on Entry / Reset on Exit */
};

PLACE_IN_SECTION("MB_MEM2") ALIGN(4) CPU2::TracesConfig CPU2::tracesConfig = { 0, 0, 0, 0 };
PLACE_IN_SECTION("MB_MEM2") ALIGN(4) CPU2::GeneralConfig CPU2::generalConfig = { 0, { 0, 0, 0 } };

void CPU2::enable()
{
	EXTI->C2EMR2 |= EXTI_IMR2_IM41;
	EXTI->RTSR2 |= EXTI_IMR2_IM41;
	__SEV(); /* Set the internal event flag and send an event to the CPU2 */
	__WFE(); /* Clear the internal event flag */
	PWR->CR4 |= PWR_CR4_C2BOOT;
}

void CPU2::setup()
{
//	DebugInitCmdPacket debugCmdPacket =
//	{
//		{ { 0, 0, 0 } },
//		{
//			(byte *)gpioConfigList,
//			(byte *)&tracesConfig,
//			(byte *)&generalConfig,
//			GPIO_CFG_NBR_OF_FEATURES,
//			NBR_OF_TRACES_CONFIG_PARAMETERS,
//			NBR_OF_GENERAL_CONFIG_PARAMETERS 
//		}
//	};
//
//	DebugInitCmdPacket *pCmdPacket = &debugCmdPacket;
//	byte local_buffer[TL_BLEEVT_CS_BUFFER_SIZE];
//	TL_EvtPacket_t * p_rsp;
//
//	p_rsp = (TL_EvtPacket_t *)local_buffer;
//
//	shci_send( SHCI_OPCODE_C2_DEBUG_INIT,
//		sizeof(SHCI_C2_DEBUG_init_Cmd_Param_t),
//		(uint8_t*)&pCmdPacket->Param,
//		p_rsp);
//
//	return (SHCI_CmdStatus_t)(((TL_CcEvt_t*)(p_rsp->evtserial.evt.payload))->payload[0]);
}