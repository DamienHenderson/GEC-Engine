#include "TileMap.hpp"



TileMap::TileMap(const HAPISPACE::CHapiXMLNode& node)
{
}


TileMap::~TileMap()
{
}

void TileMap::Load(const HAPISPACE::CHapiXMLNode & node, Visualisation& vis)
{
	int x_chunks{ 0 }, y_chunks{ 0 };
	for (auto& attrib : node.GetAttributes())
	{
		if (attrib.GetName() == "x_chunks")
		{
			x_chunks = attrib.AsInt();
		}
		else if (attrib.GetName() == "y_chunks")
		{
			y_chunks = attrib.AsInt();
		}
	}
	chunks_.resize(y_chunks);
	for (auto& row : chunks_)
	{
		row.resize(x_chunks);
	}
	
	for (auto& iter : node.GetChildren())
	{
		if (iter->GetName() == "TileDefs")
		{
			// g_tile_defs.LoadDefinitions(*iter);
		}
		if (iter->GetName() == "Chunk")
		{
			s32 x{ 0 }, y{ 0 };

			for (auto& attrib : iter->GetAttributes())
			{
				if (attrib.GetName() == "x")
				{
					x = attrib.AsInt();
				}
				if (attrib.GetName() == "y")
				{
					y = attrib.AsInt();
				}
			}

			chunks_[y][x].Load(*iter);
			std::stringstream ss;
			ss << "Chunk_" << x << "_" << y;
			chunks_[y][x].GenerateChunkSprite(vis, ss.str());
		}
	}
}

void TileMap::Render(Visualisation & vis)
{
	for (auto& row : chunks_)
	{
		for (auto& column : row)
		{
			column.Render(vis);
		}
	}
}

TileDefinition TileMap::GetTileDefinition(const vec2<f32>& pos) const
{
	for (auto& row : chunks_)
	{
		for (auto& column : row)
		{
			if (column.Contains(pos))
			{
				return column.GetTileDefinition(pos);
			}
		}
	}
	return TileDefinition();
}
