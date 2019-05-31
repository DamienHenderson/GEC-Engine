#include "TileDefinition.hpp"

TileDefinitions g_tile_defs;

TileDefinitions::TileDefinitions()
{
	AddDefinition("Default", TileDefinition());
}

TileDefinitions::~TileDefinitions()
{
}

void TileDefinitions::LoadDefinitions(const HAPISPACE::CHapiXMLNode & node)
{
	if (node.GetName() == "TileDefs")
	{
		for (auto& it : node.GetChildren())
		{
			// load name, move cost, frame, passable and tile set here
			std::string name{ "" };
			TileDefinition def;
			def.valid = true;
			HAPISPACE::CHapiXMLAttribute attrib;
			if (it->GetAttributeWithName("name", attrib))
			{
				name = attrib.AsString();
			}
			if (it->GetAttributeWithName("passable", attrib))
			{
				def.passable = attrib.AsBool();
			}
			if (it->GetAttributeWithName("move_cost", attrib))
			{
				def.movement_cost = attrib.AsInt();
			}
			if (it->GetAttributeWithName("tileset", attrib))
			{
				def.tileset = attrib.AsString();
			}
			if (it->GetAttributeWithName("frame", attrib))
			{
				def.frame_num = attrib.AsInt();
			}

			tile_defs_.emplace(name, def);
		}
	}
}

void TileDefinitions::AddDefinition(const std::string & id, const TileDefinition & tile_def)
{
	tile_defs_.emplace(id, tile_def);
}

TileDefinition TileDefinitions::GetDefinition(const std::string & id) const
{
	const auto& iter = tile_defs_.find(id);

	if (iter != tile_defs_.cend())
	{
		return iter->second;
	}
	return TileDefinition();
}
