#include "Serial.h"
#include "GPIOLib.h"

#define WE_EN		settings.wePort->BSRR = 1 << settings.wePin
#define WE_DIS		settings.wePort->BSRR = 1 << (settings.wePin + 16)
#define TX_HIGHZ	settings.txPort->MODER &= ~(3 << settings.txPin * 2)
#define TX_AF		settings.txPort->MODER |= (2 << settings.txPin * 2)

static SerialSettings settings =
{
	USART1,
	0,
	0
};

static void(*transmit)();
static void(*receive)(byte data);
static ushort remain;
static byte * buf;
static byte protocolCallback;
static byte lastByte;

void serialInterrupt()
{
	uint status = settings.module->ISR;
	if (status & USART_ISR_TC)
	{
		settings.module->ICR = USART_ISR_TC;
		if (remain > 0)
		{
			settings.module->TDR = *buf++;
			if (remain-- == 1) lastByte = 1;
			return;
		}
		if (lastByte)
		{
			lastByte = 0;
			settings.module->CR1 &= ~USART_CR1_TCIE; // clear TC interrupt
			if (settings.wePort) WE_DIS;
			if (settings.txPort) TX_HIGHZ;
			else if (transmit) transmit();
		}
	}
	else if (status & USART_ISR_RXNE)
	{
		if (receive) receive(settings.module->RDR);
		else settings.module->RQR = USART_RQR_RXFRQ;  // clear RXNE flag. Ass style;
	}
	else if (status & (USART_ISR_NE | USART_ISR_FE | USART_ISR_PE | USART_ISR_ORE))
	{
		settings.module->ICR = USART_ICR_NECF | USART_ICR_FECF | USART_ICR_PECF | USART_ICR_ORECF;
		settings.module->RQR = USART_RQR_RXFRQ;
	}
	else settings.module->ICR = USART_ICR_PECF | USART_ICR_FECF | USART_ICR_NECF | USART_ICR_ORECF | USART_ICR_IDLECF | USART_ICR_TCCF | USART_ICR_CTSCF | USART_ICR_CMCF | USART_ICR_WUCF;  // clear all flags
}

void serialSend(byte data)
{
	while (serialIsBusy()) ;
	if (settings.wePort || settings.txPort)
	{
		if (settings.wePort) WE_EN;
		if (settings.txPort) TX_AF;
		lastByte = 1;
		settings.module->ICR = USART_ICR_TCCF;  // clear TC flag
		settings.module->CR1 |= USART_CR1_TCIE;  // enable TC interrupt
	}
	settings.module->TDR = data;
}

byte serialSendBuf(byte *data, ushort len)
{
	if (!len) return 0;
	while (serialIsBusy()) ;
	if (settings.wePort) WE_EN;
	if (settings.txPort) TX_AF;
	while (len-- > 0)
	{
		while (!(settings.module->ISR & USART_ISR_TXE)) ;
		settings.module->TDR = *data++;
	}
	if (settings.wePort || settings.txPort)
	{
		lastByte = 1;
		settings.module->ICR = USART_ICR_TCCF; // clear TC flag
		settings.module->CR1 |= USART_CR1_TCIE; // enable TC interrupt
	}
	return 1;
}

byte serialSendBufAsync(byte *data, ushort len)
{
	if (!len) return 0;
	while (serialIsBusy()) ;
	buf = &data[1];
	remain = len - 1;
	if (settings.wePort) WE_EN;
	if (settings.txPort) TX_AF;
	settings.module->TDR = data[0];
	settings.module->ICR = USART_ICR_TCCF; // clear TC flag
	settings.module->CR1 |= USART_CR1_TCIE; // enable TC interrupt
	if(!remain) lastByte = 1;
	return 1;
}

void serialSendStr(char *str)
{
	while (serialIsBusy()) ;
	if (settings.wePort) WE_EN;
	if (settings.txPort) TX_AF;
	while (*str != 0)
	{
		while (!(settings.module->ISR & USART_ISR_TXE)) ;
		settings.module->TDR = *str++;
	}
	if (settings.wePort || settings.txPort)
	{
		lastByte = 1;
		settings.module->ICR = USART_ICR_TCCF;  // clear TC flag
		settings.module->CR1 |= USART_CR1_TCIE;  // enable TC interrupt
	}
}

void serialSendLine(char *str)
{
	serialSendStr(str);
	serialSendStr((char *)"\r\n");
}

void serialClearScreen()
{
	serialSendStr("\033[;H\033[2J");
}

void serialClearLine()
{
	serialSendStr("\r\033[2K");
}

byte serialSetCallbackRx(void(*link)(byte data))
{
	if (!link) return 0;
	receive = link;
	protocolCallback = 0;
	return 1;
}

byte serialSetCallbackTx(void(*link)())
{
	if (!link) return 0;
	transmit = link;
	protocolCallback = 0;
	return 1;
}

byte serialIsBusy()
{
	if (remain > 0 || lastByte) return 1;
	else return !(settings.module->ISR & USART_ISR_TXE);
}

void serialFlush()
{
	if (settings.module->ISR & USART_ISR_RXNE) settings.module->RQR = USART_RQR_RXFRQ;  // clear RXNE flag. Ass style;
}

byte serialEnableTxInt()
{
	if (remain || lastByte) return 0;
	settings.module->CR1 |= USART_CR1_TCIE;
	settings.module->ICR = USART_ICR_TCCF;   // clear TC flag
	return 1;
}

byte serialEnableRxInt()
{
	if (remain || lastByte) return 0;
	settings.module->CR1 = USART_CR1_RXNEIE;
	settings.module->RQR = USART_RQR_RXFRQ;    // clear RXNE flag. Ass style
	return 1;
}

byte serialDisableTxInt()
{
	if (remain || lastByte) return 0;
	settings.module->CR1 &= ~USART_CR1_TCIE;
	settings.module->ICR = USART_ICR_TCCF;    // clear TC flag
	return 1;
}

byte serialDisableRxInt()
{
	if (remain || lastByte) return 0;
	settings.module->CR1 &= ~USART_CR1_RXNEIE;
	settings.module->RQR = USART_RQR_RXFRQ;    // clear RXNE flag. Ass style
	return 1;
}

byte serialEnableTx()
{
	if (remain || lastByte) return 0;
	settings.module->CR1 |= USART_CR1_TE;
	settings.module->ICR = USART_ICR_TCCF;  // clear TC flag
	return 1;
}

byte serialEnableRx()
{
	if (remain || lastByte) return 0;
	settings.module->CR1 = USART_CR1_RE;
	settings.module->RQR = USART_RQR_RXFRQ;   // clear RXNE flag. Ass style
	return 1;
}

byte serialDisableTx()
{
	if (remain || lastByte) return 0;
	settings.module->CR1 &= ~(USART_CR1_TE | USART_CR1_TCIE);
	settings.module->ICR = USART_ICR_TCCF;   // clear TC flag
	return 1;
}

byte serialDisableRx()
{
	if (remain || lastByte) return 0;
	settings.module->CR1 &= ~(USART_CR1_RE | USART_CR1_RXNEIE);
	settings.module->RQR = USART_RQR_RXFRQ;   // clear RXNE flag. Ass style
	return 1;
}

void USART1_IRQHandler()
{
	serialInterrupt();
}

void serialInit()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	GPIOB->MODER &= MODERreset(6) & MODERreset(7);
	GPIOB->MODER |= MODERset(6, ModeAf) | MODERset(7, ModeAf);
	AFreg(GPIOB) |= AFset(6, 7) | AFset(7, 7);
	
	RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
	settings.module->BRR = 277; // Reg = 256 * fck / Baud / PRESC; fck = 32M
	settings.module->CR1 = USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
	protocolCallback = 0;
	transmit = 0;
	receive = 0;
	remain = 0;
	lastByte = 0;

	settings.module->ICR = USART_ICR_TCCF;  // clear TC flag
	settings.module->RQR = USART_RQR_RXFRQ;  // clear RXNE flag. Ass style
	settings.module->CR1 |= USART_CR1_TCIE | USART_CR1_RXNEIE;
	NVIC_EnableIRQ(USART1_IRQn);
	__enable_irq();
}