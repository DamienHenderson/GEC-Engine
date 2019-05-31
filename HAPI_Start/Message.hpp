#pragma once

enum class MessageType
{
	CreateEntity,
	RenderSprite
};
class Message
{
public:
	Message();
	virtual ~Message();

	virtual MessageType GetType() const = 0;
};

