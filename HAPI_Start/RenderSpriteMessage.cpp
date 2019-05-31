#include "RenderSpriteMessage.hpp"



RenderSpriteMessage::RenderSpriteMessage(const std::string& sprite_id, const vec2<f32>& pos, int frame) : sprite_id_(sprite_id), pos_(pos), frame_num_(frame)
{
}


RenderSpriteMessage::~RenderSpriteMessage()
{
}
