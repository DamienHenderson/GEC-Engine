#pragma once

#include <vector>

#include <HAPI_lib.h>
#include <HAPI_Types.h>

#include "Types.hpp"
#include "Tile.hpp"

#include "FrameBuffer.hpp"
class Visualisation;

constexpr s32 chunk_width = 32;
constexpr s32 chunk_height = 32;

constexpr s32 tile_width = 32;
constexpr s32 tile_height = 32;

constexpr s32 chunk_width_pixels = chunk_width * tile_width;
constexpr s32 chunk_height_pixels = chunk_height * tile_height;

class TileChunk
{
public:
	TileChunk();
	~TileChunk();

	void Load(const HAPISPACE::CHapiXMLNode& node);
	void GenerateChunkSprite(Visualisation& vis, const std::string& name);

	void Render(Visualisation& vis);

	bool Contains(const vec2<f32>& point) const;

	TileDefinition GetTileDefinition(const vec2<f32>& pos) const;
private:
	std::vector < std::vector<Tile>> tiles_;

	std::string sprite_name_;

	vec2<f32> position_{ 0.f,0.f };

	FrameBuffer fb_;
};

