#pragma once

#include "TL.h"

class HRS
{
public:
	static TL::HCI::Service::EvtAckStatus handler(TL::Event *evt);
	static void init();
};