#include "HRS.h"

TL::HCI::Service::EvtAckStatus HRS::handler(TL::Event *evt)
{
	return TL::HCI::Service::EvtAckStatus::NotAck;
}

void HRS::init()
{
	TL::HCI::Service::addService(handler);
}