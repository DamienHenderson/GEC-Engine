#pragma once
#include "Entity.hpp"

class Player : public Entity
{
public:
	Player() : Entity() {}
	Player(const vec2 <f32>& pos, s32 health, Team team, const std::string& sprite_id);
	~Player();

	virtual void Update(s32 delta_ms) override;
	virtual void Render(Visualisation& vis, s32 delta_ms) override;

	virtual void OnCollide(Entity& other) override;

	virtual EntityType Type() const override;

};

