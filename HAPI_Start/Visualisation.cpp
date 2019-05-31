#include "Visualisation.hpp"

#include "Message.hpp"
#include "RenderSpriteMessage.hpp"
#include "Sprite.hpp"

Visualisation::Visualisation(s32& width, s32& height, const std::string& title, bool fullscreen) : scr_(width, height, title, fullscreen), fb_(width, height)
{
}


Visualisation::~Visualisation()
{
	for (auto& iter : sprites_)
	{
		SafeDelete(iter.second);
	}
}

bool Visualisation::Initialise(s32 & width, s32 & height, const std::string & title, bool fullscreen)
{
	if (scr_.Initialise(width, height, title, fullscreen))
	{
		fb_.Initialise(width, height);
		return true;
	}
	return false;
}

bool Visualisation::CreateSprite(const Image & img, const std::string & name, bool has_alpha, int x_frames, int y_frames)
{
	auto& iter = sprites_.find(name);
	if (iter != sprites_.end())
	{
		// sprite has already been loaded
		return true;
	}



	Sprite* spr = new Sprite(img, { 0.0f,0.0f }, has_alpha, x_frames, y_frames);
	sprites_.emplace(std::make_pair(name, spr));
	return true;

}

bool Visualisation::LoadSprite(const std::string & filename, bool has_alpha, int x_frames, int y_frames)
{
	return LoadSprite(filename, filename, has_alpha, x_frames, y_frames);
}

bool Visualisation::LoadSprite(const std::string & filename, const std::string & identifier, bool has_alpha, int x_frames, int y_frames)
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
		Sprite* spr = new Sprite(img, { 0.0f,0.0f }, has_alpha, x_frames, y_frames);
		sprites_.emplace(std::make_pair(identifier, spr));
		return true;
	}
	HAPI.UserMessage("Could not load texture at path: " + filename, "Missing Texture");
	return false;
}

bool Visualisation::RenderSprite(const std::string & id, const vec2<f32>& position, int frame)
{
	auto& iter = sprites_.find(id);

	if (iter == sprites_.end())
	{
		/// sprite not found
		/// show message here?
		HAPI.UserMessage("Texture " + id + " has not been loaded", "Missing Texture");
		return false;
	}

	iter->second->SetPosition(position);
	iter->second->RenderThreaded(fb_, frame, camera_);

	return true;

}

bool Visualisation::RenderSpriteToFrameBuffer(const std::string & id, const vec2<f32>& position, int frame, FrameBuffer & fb)
{
	auto& iter = sprites_.find(id);

	if (iter == sprites_.end())
	{
		/// sprite not found
		/// show message here?
		HAPI.UserMessage("Texture " + id + " has not been loaded", "Missing Texture");
		return false;
	}

	iter->second->SetPosition(position);
	iter->second->RenderThreaded(fb, frame, camera_);

	return true;
}

void Visualisation::MoveCamera(const vec2<f32>& delta)
{
	camera_.Move(delta);
}

void Visualisation::ReceiveMessage(Message * msg)
{
	if (msg != nullptr)
	{
		if (msg->GetType() == MessageType::RenderSprite)
		{
			RenderSpriteMessage* rsm = (RenderSpriteMessage*)msg;
			RenderSprite(rsm->GetSpriteID(), rsm->GetPosition(), rsm->GetFrameNum());

		}
	}
}
