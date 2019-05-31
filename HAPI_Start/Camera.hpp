#pragma once

#include "Types.hpp"
class Camera
{
public:
	Camera();
	~Camera();

	vec2<f32> GetPosition() const 
	{ 
		return position_; 
	}

	void SetPosition(vec2<f32> pos)
	{ 
		position_ = pos;
	}

	void Move(const vec2<f32>& delta)
	{
		position_ += delta;
	}
	
	vec2<f32> ScreenToWorld(vec2<f32> screen_pos) const
	{
		return screen_pos + position_;
	}
	vec2<f32> WorldToScreen(vec2<f32> world_pos) const
	{
		return world_pos - position_;
	}
private:
	vec2<f32> position_{ 0.f,0.f };
};

