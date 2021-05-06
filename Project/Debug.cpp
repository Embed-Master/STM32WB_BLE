#include "Debug.h"
#include "GPIOLib.h"
#include "stdio.h"

Serial serial({ USART1 }, 32000000 / 115200, []()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &= MODERreset(6) & MODERreset(7);
	GPIOB->MODER |= MODERset(6, ModeAf) | MODERset(7, ModeAf);
	AFreg(GPIOB) |= AFset(6, 7) | AFset(7, 7);
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
},	[](){ NVIC_EnableIRQ(USART1_IRQn); }, 0);

void Debug::enterToFunction(const char *name)
{
	serial.send("Enter to: ");
	serial.sendLine(name);
}

extern "C" int _write(int fd, char* ptr, int len)
{
	serial.sendBuf(ptr, len);
	return len;
}