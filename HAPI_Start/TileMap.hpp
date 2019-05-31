#pragma once

#include <vector>

#include <HAPI_lib.h>
#include <HAPI_Types.h>


#include "TileChunk.hpp"

class Visualisation;

class TileMap
{
public:
	TileMap()
	{

	}
	TileMap(const HAPISPACE::CHapiXMLNode& node);
	~TileMap();

	void Load(const HAPISPACE::CHapiXMLNode& node, Visualisation& vis);
	
	void Render(Visualisation& vis);

	TileDefinition GetTileDefinition(const vec2<f32>& pos) const;

	bool PointIsInTileMap(const vec2<f32>& point) const
	{
		for (auto& row : chunks_)
		{
			for (auto& column : row)
			{
				if (column.Contains(point))
				{
					return true;
				}
			}
		}
		return false;
	}
private: 
	std::vector<std::vector<TileChunk>> chunks_;
};

