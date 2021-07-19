#include "Debug.h"
#include "GPIOLib.h"
#include "stdio.h"

Serial serial({ LPUART1 }, (32000000 / 115200) * 256, []()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &= MODERreset(10) & MODERreset(11);
	GPIOB->MODER |= MODERset(10, ModeAf) | MODERset(11, ModeAf);
	AFreg(GPIOB) |= AFset(10, 8) | AFset(11, 8);
	RCC->APB1ENR2 |= RCC_APB1ENR2_LPUART1EN;
},	[](){ NVIC_EnableIRQ(LPUART1_IRQn); }, 0);

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