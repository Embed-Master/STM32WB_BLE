#include "IPCC.hpp"
#include "CoreSettings.h"

void (*IPCCm::callback[12])();

bool IPCCm::expected(Direction direction, byte channel)
{
	if (channel > 5) return false;
	return (~IPCC->C1MR >> 16 * (byte)direction) & (1 << channel);
}

bool IPCCm::pending(Direction direction, byte channel)
{
	if (channel > 5) return false;
 	return (direction == Direction::Rx ? IPCC->C2TOC1SR : IPCC->C1TOC2SR) & (1 << channel);
}

void IPCCm::interrupt(Direction direction)
{
	if (direction == Direction::Rx)
	{
		for (byte i = 0; i < 6; i++)
		{
			if (pending(Direction::Rx, i) && expected(Direction::Rx, i))
			{
				if (callback[i]) callback[i]();
				IPCC->C1SCR = 1 << i;
			}
		}
	}
	else
	{
		for (byte i = 0; i < 6; i++)
		{
			if (!pending(Direction::Tx, i) && expected(Direction::Tx, i))
			{
				IPCC->C1MR |= 1 << (i + 16);
				if (callback[i + 6]) callback[i + 6]();
			}
		}
	}
}

void IPCC_C1_RX_IRQHandler()
{
	IPCCm::interrupt(IPCCm::Direction::Rx);
}

void IPCC_C1_TX_IRQHandler()
{
	IPCCm::interrupt(IPCCm::Direction::Tx);
}

void IPCCm::unExpect(Direction direction, byte channel)
{
	if (channel > 5) return;
	IPCC->C1MR |= (1 << channel) << (16 * (byte)direction);
}

void IPCCm::expect(Direction direction, byte channel)
{
	if (channel > 5) return;
	IPCC->C1MR &= ~((1 << channel) << (16 * (byte)direction));
}

void IPCCm::occupy(byte channel, bool expect)
{
	if (channel > 5) return;
	IPCC->C1SCR = (1 << 16) << channel;
	if (expect) IPCCm::expect(Direction::Tx, channel);
}

void IPCCm::setCallBack(void (*callback)(), Direction direction, byte channel)
{
	if (channel > 5) return;
	IPCCm::callback[(byte)direction * 6 + channel] = callback;
}

void IPCCm::init()
{
	RCC->AHB3ENR |= RCC_AHB3ENR_IPCCEN;
	IPCC->C1CR |= IPCC_C1CR_RXOIE | IPCC_C1CR_TXFIE;// Enable Transmit channel free and Receive channel occupied interrupt for CPU_1
	__NVIC_EnableIRQ(IPCC_C1_RX_IRQn);
	__NVIC_EnableIRQ(IPCC_C1_TX_IRQn);
}