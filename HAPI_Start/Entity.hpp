#pragma once

#include <string>

#include <HAPI_lib.h>
#include <HAPI_Types.h>
#include <HAPI_InputCodes.h>

#include "Types.hpp"
// only put this in controllable entities?
#include "Input.hpp"
#include "Sound.hpp"

#include "Visualisation.hpp"

enum class EntityType
{
	Player
};
/// used for collisions 
enum class Team
{
	Player,
	Enemy,
	Neutral
};
class Entity
{
public:
	Entity(){}
	Entity(const vec2<f32>& pos, s32 health, Team team, const std::string& sprite_id);
	virtual ~Entity();

	virtual void Update(s32 delta_ms) = 0;
	virtual void Render(Visualisation& vis, s32 delta_ms) = 0;
	
	virtual void OnCollide(Entity& other) = 0;
	/// for identifying the type of entity this is
	/// useful for polymorphic storage to allow casting
	virtual EntityType Type() const = 0;

	
	const vec2<f32>& GetPosition() const { return position_; }
	void SetPosition(const vec2<f32>& pos) { position_ = pos; }

	s32 GetHealth() const { return health_; }
	void SetHealth(s32 health) { health_ = health; }


	Team GetTeam() const { return team_; }
	void SetTeam(Team team) { team_ = team; }

	const std::string& GetSpriteID() const { return sprite_id_; }
	void SetSpriteID(const std::string& id) { sprite_id_ = id; }

	int GetAnimationFrame() const { return anim_frame_; }
	void SetAnimationFrame(int frame) { anim_frame_ = frame; }
protected:
	vec2<f32> position_{ 0.f,0.f };
	s32 health_{ 100 };
	Team team_{ Team::Player };

	std::string sprite_id_;
	int anim_frame_{ 0 };
};

