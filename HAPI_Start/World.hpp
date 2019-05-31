#pragma once

#include <string>
#include <memory>

#include <HAPI_lib.h>
#include <HAPI_Types.h>
#include <HAPI_InputCodes.h>

#include "Types.hpp"
#include "Visualisation.hpp"
#include "Entity.hpp"
#include "Input.hpp"
#include "TileMap.hpp"

#include "ObjectPool.hpp"

#include "LandUnit.hpp"

constexpr s64 update_interval = 1000 / 60;

class Message;
class World
{
public:
	World();
	~World();
	// Initialise from an XML Config file
	bool Initialise(const std::string& file_path, s32& width, s32& height);
	// Load a level from an XML Level file
	void LoadFromFile(const std::string& directory, const std::string& filename);
	
	void ReceiveMessage(Message* msg);

	bool Run();
	
private:

	void LoadAssetDefinition(HAPISPACE::CHapiXML& asset_def_file);
	bool initialised_{ false };
	void Update(s32 delta_time);
	void Render(s32 delta_time);

	s64 cumulative_update_time_;
	s64 last_time_{ 0 };
	Visualisation vis_;

	TileMap tile_map_;

	std::vector<Entity*> entities_;

	TileDefinition selected_tile_;

	LandUnit unit;
};

