#pragma once

#include <unordered_map>
#include <string>

#include <HAPI_lib.h>
#include <HAPI_Types.h>

#include "Types.hpp"


struct TileDefinition
{
	TileDefinition()
	{
		
	}
	s32 movement_cost{ 1 };
	std::string tileset{ "TileSet" };
	int frame_num{ 0 };

	bool passable{ false }, valid{ false };

	std::string ToString()
	{
		std::stringstream ss;
		ss << "TileDef MoveCost = " << movement_cost << " TileSet = " << tileset << " FrameNum = " << frame_num << " ";
		if (passable)
		{
			ss << "passable";
		}
		else
		{
			ss << "impassable";
		}
		ss << "\n";
		return ss.str();
	}

};

class TileDefinitions
{
public:
	TileDefinitions();
	~TileDefinitions();
	
	void LoadDefinitions(const HAPISPACE::CHapiXMLNode& node);
	void AddDefinition(const std::string& id, const TileDefinition& tile_def);

	TileDefinition GetDefinition(const std::string& id) const;
private:
	std::unordered_map<std::string, TileDefinition> tile_defs_;
};


extern TileDefinitions g_tile_defs;