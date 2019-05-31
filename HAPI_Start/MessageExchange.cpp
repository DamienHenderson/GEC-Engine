#include "MessageExchange.hpp"

#include "World.hpp"
#include "Visualisation.hpp"
#include "Sound.hpp"

MessageExchange g_message_exchange;

MessageExchange::MessageExchange()
{
}


MessageExchange::~MessageExchange()
{
}

void MessageExchange::DispatchMessage(Message * msg, Destination dest)
{
	if (msg == nullptr)
	{
		return;
	}
	switch(dest)
	{
	case Destination::World:
		world_->ReceiveMessage(msg);
		break;
	case Destination::Visualisation:
		vis_->ReceiveMessage(msg);
		break;
	case Destination::Sound:
		sound_->ReceiveMessage(msg);
		break;
	}
}
