#pragma once
#include <string>

#include "Message.hpp"
#include "Types.hpp"

class RenderSpriteMessage : public Message
{
public:
	RenderSpriteMessage(const std::string& sprite_id, const vec2<f32>& pos, int frame);
	~RenderSpriteMessage();

	virtual MessageType GetType() const override { return MessageType::RenderSprite; }

	const std::string& GetSpriteID() const { return sprite_id_; }
	const vec2<f32>& GetPosition() const { return pos_; }
	int GetFrameNum() const { return frame_num_; }
private:
	std::string sprite_id_;
	vec2<f32> pos_{ 0.f,0.f };
	int frame_num_{ 0 };

};

