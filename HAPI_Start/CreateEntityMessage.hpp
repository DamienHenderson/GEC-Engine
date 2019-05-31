#pragma once
#include "Message.hpp"

class Entity;

class CreateEntityMessage : public Message
{
public:
	CreateEntityMessage(Entity* entity);
	virtual ~CreateEntityMessage();

	virtual MessageType GetType() const override { return MessageType::CreateEntity; }

	Entity* GetEntity() { return entity_; }

private:
	Entity* entity_{ nullptr };
};

