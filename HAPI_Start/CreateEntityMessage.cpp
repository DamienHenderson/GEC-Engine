#include "CreateEntityMessage.hpp"
#include "Entity.hpp"


CreateEntityMessage::CreateEntityMessage(Entity* entity) : entity_(entity)
{
	
}


CreateEntityMessage::~CreateEntityMessage()
{
}
