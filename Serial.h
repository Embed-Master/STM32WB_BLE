#pragma once

#include "CoreSettings.h"
#include "Types.h"

typedef struct
{
	USART_TypeDef * module;
	GPIO_TypeDef * wePort;  // != nullptr if Write enable mode used
	byte wePin;
	GPIO_TypeDef * txPort;  // != nullptr if Tx High-Z mode used
	byte txPin;
} SerialSettings;

void serialInit();
byte serialIsBusy();
byte serialSetCallbackRx(void(*link)(byte data));
byte serialDisableTxInt();

void serialSend(byte data);
byte serialSendBuf(byte *data, ushort len);
byte serialSendBufAsync(byte *data, ushort len);
void serialSendStr(char *str);
void serialSendLine(char *str);
void serialClearScreen();
void serialClearLine();