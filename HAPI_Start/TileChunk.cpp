#include "TileChunk.hpp"

#include "Visualisation.hpp"
#include "FrameBuffer.hpp"


TileChunk::TileChunk()
{
	// TODO: load chunk from xml node
}


TileChunk::~TileChunk()
{
}

void TileChunk::Load(const HAPISPACE::CHapiXMLNode & node)
{
	s32 x{ 0 }, y{ 0 };
	for (auto& attrib : node.GetAttributes())
	{
		if (attrib.GetName() == "x")
		{
			x = attrib.AsInt();
		}
		else if (attrib.GetName() == "y")
		{
			y = attrib.AsInt();
		}
	}
	position_ = { (f32)x * (tile_width * chunk_width), (f32)y * (tile_height * chunk_height) };

	tiles_.resize(chunk_height);
	for (auto& row : tiles_)
	{
		row.resize(chunk_width, Tile("desert"));
	}

	
	for (auto& child : node.GetChildren())
	{
		if (child->GetName() == "Tile")
		{
			s32 x{ 0 }, y{ 0 };
			std::string tiledef{ "" };
			for (auto& attrib : child->GetAttributes())
			{
				if (attrib.GetName() == "x")
				{
					x = attrib.AsInt();
				}
				if (attrib.GetName() == "y")
				{
					y = attrib.AsInt();
				}
				if (attrib.GetName() == "tile_def")
				{
					tiledef = attrib.AsString();
				}

			}
			if (tiledef != "" && x >= 0 && x < chunk_width && y >= 0 && y < chunk_height)
			{
				tiles_[y][x] = Tile(tiledef);
			}
			
			

			
		}
	}
	


}

void TileChunk::GenerateChunkSprite(Visualisation & vis, const std::string& name)
{
	
	fb_.Initialise(chunk_width_pixels, chunk_height_pixels);

	 //fb.Initialise(chunk_width_pixels, chunk_height_pixels);

	
	 for (int y = 0; y < tiles_.size(); y++)
	 {
	 	for (int x = 0; x < tiles_[y].size(); x++)
	 	{
	 		auto& tile_def = g_tile_defs.GetDefinition(tiles_[y][x].GetDefinitionID());
	 		vec2<f32> pos = { (f32)x * tile_width, (f32)y * tile_height };
	 		vis.RenderSpriteToFrameBuffer(tile_def.tileset, pos, tile_def.frame_num, fb_);
	 	}
	 }
	

	 Image img(fb_.GetPixelsUnsafe(), fb_.GetWidth(), fb_.GetHeight());

	 vis.CreateSprite(img, name, false, 1, 1);

	 sprite_name_ = name;

	
}

void TileChunk::Render(Visualisation & vis)
{
	/*for (int y = 0; y < tiles_.size(); y++)
	{
		for (int x = 0; x < tiles_[y].size(); x++)
		{
			auto& tile_def = g_tile_defs.GetDefinition(tiles_[y][x].GetDefinitionID());
			vec2<f32> pos = { (f32)x * tile_width, (f32)y * tile_height };
			vis.RenderSprite(tile_def.tileset, position_ + pos, tile_def.frame_num);
		}
	}*/
	vis.RenderSprite(sprite_name_, position_);
}

bool TileChunk::Contains(const vec2<f32>& point) const
{
	
	rect<s32> chunk_bounds{ chunk_width_pixels, chunk_height_pixels };

	chunk_bounds.Translate((s32)position_.x, (s32)position_.y);

	return chunk_bounds.Contains({ (s32)point.x, (s32)point.y });
}

TileDefinition TileChunk::GetTileDefinition(const vec2<f32>& pos) const
{
	// make sure the point is in the chunk
	if (!Contains(pos))
	{
		return TileDefinition();
	}

	vec2<s32> int_vec{ (s32)pos.x, (s32)pos.y };

	// convert from world space to chunk space then convert to tile index
	int x_tile = (int_vec.x - (int)position_.x) / tile_width;
	int y_tile = (int_vec.y - (int)position_.y) / tile_height;

	if (y_tile >= chunk_height || y_tile < 0 || x_tile >= chunk_width || x_tile < 0)
	{
		return TileDefinition();
	}
	return g_tile_defs.GetDefinition(tiles_[y_tile][x_tile].GetDefinitionID());
}
