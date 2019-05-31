#pragma once
#include "Unit.hpp"

#include <queue>

class TileMap;
/// Interface for units which go on land which therfore have pathfinding
class LandUnit : public Unit
{
public:
	LandUnit();
	virtual ~LandUnit();



	void Pathfind(vec2<f32> destination, TileMap& tilemap);

	virtual void Update(s32 delta_ms) override
	{

		if (!waypoints_.empty())
		{
			vec2<f32> waypoint = waypoints_.front();

			vec2<f32> dir = waypoint - position_;

			dir.Unit();

			f32 delta_decimal = delta_ms / 1000.f;

			position_ += dir * (delta_decimal * speed_);

			if (IsWithin(waypoint.x, 0.1f, position_.x) && IsWithin(waypoint.y, 0.1f, position_.y))
			{
				waypoints_.pop_front();
			}
			// position_ = waypoints_.front();
			
		}
	}
	virtual void Render(Visualisation& vis, s32 delta_ms) override
	{
		vis.RenderSprite("Blue_Soldier", position_ - vec2<f32>{24.f, 20.f});
	}

	virtual void OnCollide(Entity& other) override
	{

	}
	/// for identifying the type of entity this is
	/// useful for polymorphic storage to allow casting
	virtual EntityType Type() const override
	{
		return EntityType::Player;
	}
private:

	
	vec2<f32> goal{ 0.f,0.f };
	vec2<f32> next_position{ 0.f,0.f };

	std::list<vec2<f32>> waypoints_;

	f32 speed_{ 15.f };
};

