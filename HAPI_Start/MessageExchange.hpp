#pragma once

#include "Message.hpp"

class World;
class Visualisation;
class Sound;
enum class Destination
{
	World,
	Visualisation,
	Sound
};
class MessageExchange
{
public:
	MessageExchange();
	~MessageExchange();

	void DispatchMessage(Message* msg, Destination dest);

	void SetWorld(World* world) { world_ = world; }
	void SetVisualisation(Visualisation* vis) { vis_ = vis; }
	void SetSound(Sound* sound) { sound_ = sound; }

private:
	World* world_{ nullptr };
	Visualisation* vis_{ nullptr };
	Sound* sound_{ nullptr };
};

extern MessageExchange g_message_exchange;