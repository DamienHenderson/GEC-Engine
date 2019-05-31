#include "Entity.hpp"



Entity::Entity(const vec2<f32>& pos, s32 health, Team team, const std::string& sprite_id) : position_(pos), health_(health), team_(team), sprite_id_(sprite_id)
{
}


Entity::~Entity()
{
}
