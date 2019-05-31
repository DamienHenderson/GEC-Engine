#include "Visualisation.hpp"



Visualisation::Visualisation(s32& width, s32& height, const std::string& title) : scr_(width,height,title), fb_(width,height)
{
}


Visualisation::~Visualisation()
{
	for (auto& iter : sprites_)
	{
		SafeDelete(iter.second);
	}
}

bool Visualisation::LoadSprite(const std::string & filename, bool has_alpha)
{
	auto& iter = sprites_.find(filename);
	if (iter != sprites_.end())
	{
		// sprite has already been loaded
		return true;
	}
	Image img;
	bool res = img.LoadFromFile(filename);

	if (res)
	{
		Sprite* spr = new Sprite(img, { 0.0f,0.0f }, img.GetWidth(), img.GetHeight(), has_alpha);
		sprites_.emplace(std::make_pair(filename, spr));
		return true;
	}
	HAPI.UserMessage("Could not load texture at path: " + filename, "Missing Texture");
	return false;
}

bool Visualisation::RenderSprite(const std::string & id, const vec2<f32>& position)
{
	auto& iter = sprites_.find(id);

	if (iter == sprites_.end())
	{
		/// sprite not found
		/// show message here?
		HAPI.UserMessage("Texture " + id + " has not been loaded", "Missing Texture");
		return false;
	}
	vec2<f32> clamped_pos;
	clamped_pos.x = Clamp(0.0f, (float)fb_.GetWidth() - (float)iter->second->GetWidth(), position.x);
	clamped_pos.y = Clamp(0.0f, (float)fb_.GetHeight() - (float)iter->second->GetHeight(), position.y);
	iter->second->SetPosition(clamped_pos);
	iter->second->Render(fb_);

	return true;
}
