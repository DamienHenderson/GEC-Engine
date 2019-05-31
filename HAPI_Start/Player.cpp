#include "Player.hpp"

#include <HAPI_lib.h>
#include <HAPI_Types.h>
#include <HAPI_InputCodes.h>

Player::Player(const vec2 <f32>& pos, s32 health, Team team, const std::string& sprite_id) : Entity(pos, health, team, sprite_id)
{
}


Player::~Player()
{
}

void Player::Update(s32 delta_ms)
{
	anim_frame_++;


	if (g_input.GetControllerAnalogue("horizontal", 0) > HK_GAMEPAD_LEFT_THUMB_DEADZONE /*|| g_input.GetKeyState("right")*/)
	{
		position_.x += 1.0f;
	}
	if (g_input.GetControllerAnalogue("horizontal", 0) < -HK_GAMEPAD_LEFT_THUMB_DEADZONE /*|| g_input.GetKeyState("left")*/)
	{
		position_.x -= 1.0f;
	}
	if (g_input.GetControllerAnalogue("vertical", 0) > HK_GAMEPAD_LEFT_THUMB_DEADZONE /*|| g_input.GetKeyState("up")*/)
	{
		position_.y -= 1.0f;
	}
	if (g_input.GetControllerAnalogue("vertical", 0) < -HK_GAMEPAD_LEFT_THUMB_DEADZONE /*|| g_input.GetKeyState("down")*/)
	{
		position_.y += 1.0f;
	}
	
	if (g_input.GetControllerDigital(HK_DIGITAL_A, 0))
	{
		sprite_id_ = "HealthOK";
	}
	if (g_input.GetControllerDigital(HK_DIGITAL_B, 0))
	{
		sprite_id_ = "HealthCAUTION";
	}
	if (g_input.GetControllerDigital(HK_DIGITAL_X, 0))
	{
		sprite_id_ = "HealthDANGER";
	}
	if (g_input.GetControllerDigital(HK_DIGITAL_Y, 0))
	{
		sprite_id_ = "TileSet";
	}
}

void Player::Render(Visualisation& vis, s32 delta_ms)
{

	vis.RenderSprite(sprite_id_, position_, anim_frame_);
}

void Player::OnCollide(Entity & other)
{
	if (other.GetTeam() == team_)
	{
		// No need to collide with units on the same team
		return;
	}
}

EntityType Player::Type() const
{
	return EntityType::Player;
}
