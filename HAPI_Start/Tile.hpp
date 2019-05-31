#pragma once

#include <string>

#include "TileDefinition.hpp"

class Tile
{
public:
	Tile(const std::string& definition_id);
	~Tile();

	const std::string& GetDefinitionID() const
	{
		return definition_id_;
	}
	
private:
	std::string definition_id_;
	
};

