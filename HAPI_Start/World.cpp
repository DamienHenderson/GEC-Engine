#include "World.hpp"

#include "Player.hpp"

#include "Message.hpp"
#include "CreateEntityMessage.hpp"


using namespace HAPISPACE;
World::World()
{

}


World::~World()
{
	for (auto& it : entities_)
	{
		// allocated with object pool now so deallocation is automatic
		// delete it;
		// g_allocator.Deallocate(&it);
	}
}

bool World::Initialise(const std::string & file_path, s32& width, s32& height)
{
	bool fullscreen{ false };
	std::string title = "HAPI Game";
	HAPISPACE::CHapiXML xml_reader(file_path);
	DEBUG_ONLY(xml_reader.DebugOutputStructure(););

	HAPISPACE::CHapiXMLNode* root = xml_reader.GetRootNode();
	
	for (auto& i : root->GetChildren())
	{
		for (auto& it : i->GetChildren())
		{

			if (it->GetName() == "Window")
			{

				for (auto& attrib : it->GetAttributes())
				{


					if (attrib.GetName() == "screen_width")
					{
						width = attrib.AsInt();
					}
					if (attrib.GetName() == "screen_height")
					{
						height = attrib.AsInt();
					}
					if (attrib.GetName() == "fullscreen")
					{
						fullscreen = attrib.AsBool();
					}
					if (attrib.GetName() == "title")
					{
						title = attrib.AsString();
					}
				}
				DEBUG_ONLY(std::cout << "initialising" << "\n";);
				HAPISPACE::DWORD flags = (fullscreen) ? HAPISPACE::eFullscreen : HAPISPACE::eDefaults;

				initialised_ = vis_.Initialise(width, height, title, fullscreen);
				if (!initialised_)
				{

					return false;
				}
			}
			if (it->GetName() == "Input")
			{
				g_input.LoadMappings(*it);
			}

		}

	}



	return true;
}
void World::LoadFromFile(const std::string& directory, const std::string& filename)
{
	// List of features for level files
	// Load Entities from file
	// Load Sprites defined in file - Done
	// Entity Types defined in file? (health, team, behaviour, etc)
	// Game Rules?
	
	std::string file_path = directory + filename;
	HAPISPACE::CHapiXML xml_reader(file_path);
	DEBUG_ONLY(xml_reader.DebugOutputStructure(););

	HAPISPACE::CHapiXMLNode* root = xml_reader.GetRootNode();
	for (auto& i : root->GetChildren())
	{
		for (auto& it : i->GetChildren())
		{

			if (it->GetName() == "Assets")
			{
				// load asset definition file
				std::string asset_def_path{ "" };
				bool relative_path{ true };

				for (auto& attrib : it->GetAttributes())
				{
					if (attrib.GetName() == "filepath")
					{
						asset_def_path = attrib.AsString();
					}
					if (attrib.GetName() == "relative")
					{
						relative_path = attrib.AsBool();
					}
				}
				if (asset_def_path != "")
				{
					
					if (relative_path)
					{
						
						
						HAPISPACE::CHapiXML asset_def_reader(directory + asset_def_path);

						DEBUG_ONLY(asset_def_reader.DebugOutputStructure(););

						LoadAssetDefinition(asset_def_reader);
					}
					else
					{
						HAPISPACE::CHapiXML asset_def_reader(asset_def_path);

						DEBUG_ONLY(asset_def_reader.DebugOutputStructure(););

						LoadAssetDefinition(asset_def_reader);
					}

				}
			}
			/*
			if (it->GetName() == "Sprites")
			{
				for (auto& sprite : it->GetChildren())
				{
					std::string name{ "" }, path{ "" };
					bool alpha{ false };
					int x_frames{ 1 }, y_frames{ 1 };
					for (auto& attrib : sprite->GetAttributes())
					{
						if (attrib.GetName() == "name")
						{
							name = attrib.AsString();
						}
						if (attrib.GetName() == "path")
						{
							path = attrib.AsString();
						}
						if (attrib.GetName() == "alpha")
						{
							alpha = attrib.AsBool();
						}
						if (attrib.GetName() == "x_frames")
						{
							x_frames = attrib.AsInt();
						}
						if (attrib.GetName() == "y_frames")
						{
							y_frames = attrib.AsInt();
						}

					}
					if (path != "" && name != "" && initialised_)
					{
						DEBUG_ONLY( std::cout <<  "Attempting to load: " << path << "\n";
						if (!vis_.LoadSprite(path, name, alpha, x_frames,y_frames))
						{
						
							assert(false);
						}
						DEBUG_ONLY( std::cout <<  "loaded " << path << " successfully\n";
					}
				}
			}
			*/
			if (it->GetName() == "TileMap")
			{
				tile_map_.Load(*it, vis_);
			}
		}

	}
}
void World::ReceiveMessage(Message * msg)
{
	if (msg != nullptr)
	{
		if (msg->GetType() == MessageType::CreateEntity)
		{
			CreateEntityMessage* cem = (CreateEntityMessage*)msg;
			Entity* entity = cem->GetEntity();
			if (entity != nullptr)
			{
				entities_.push_back(entity);
			}
			
		}
	}
}
bool World::Run()
{
	

	// ObjectPool<Player>& player_pool = GetPool<Player>(1);
	
	// Player* player = player_pool.GetObject(1);
	// player->SetSpriteID("TileSet");
	// entities_.push_back(player);


	unit.SetPosition({ 0.f,0.f });

	// TODO: only do this if a setting is enabled in config.xml
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);
	// TODO: enable or disable based on an option in config.xml 
	// HAPI.SetShowCursor(false);
	while (vis_.Update())
	{
		s64 delta_time = HAPI.GetTime() - last_time_;
		cumulative_update_time_ += delta_time;
		// fixed timestep
		if (cumulative_update_time_ >= update_interval)
		{
			Update(update_interval);
			cumulative_update_time_ -= update_interval;
		}
		
		Render((s32)delta_time);
		last_time_ = HAPI.GetTime();
	}
	return true;
}

void World::LoadAssetDefinition(HAPISPACE::CHapiXML & asset_def_file)
{
	HAPISPACE::CHapiXMLNode* root = asset_def_file.GetRootNode();
	for (auto& i : root->GetChildren())
	{

		DEBUG_ONLY(std::cout << i->GetName() << "\n";);
		for (auto& it : i->GetChildren())
		{

			DEBUG_ONLY(std::cout << it->GetName() << "\n";);
			if (it->GetName() == "Sprites")
			{
				for (auto& sprite : it->GetChildren())
				{
					std::string name{ "" }, path{ "" };
					bool alpha{ false };
					int x_frames{ 1 }, y_frames{ 1 };
					for (auto& attrib : sprite->GetAttributes())
					{
						if (attrib.GetName() == "name")
						{
							name = attrib.AsString();
						}
						if (attrib.GetName() == "path")
						{
							path = attrib.AsString();
						}
						if (attrib.GetName() == "alpha")
						{
							alpha = attrib.AsBool();
						}
						if (attrib.GetName() == "x_frames")
						{
							x_frames = attrib.AsInt();
						}
						if (attrib.GetName() == "y_frames")
						{
							y_frames = attrib.AsInt();
						}

					}
					if (path != "" && name != "" && initialised_)
					{
						DEBUG_ONLY(std::cout << "Attempting to load: " << path << "\n";);
						if (!vis_.LoadSprite(path, name, alpha, x_frames, y_frames))
						{

							assert(false);
						}
						DEBUG_ONLY(std::cout << "loaded " << path << " successfully" << "\n";);
					}
				}
			}
			if (it->GetName() == "TileDefs")
			{
				g_tile_defs.LoadDefinitions(*it);
			}
		}
	}
}

void World::Update(s32 delta_time)
{


	for (auto& it : entities_)
	{
		it->Update(delta_time);
	}
	unit.Update(delta_time);

	vec2<f32> cursor_pos = vec2<f32>{ (float)g_input.GetMousePosition().x, (float)g_input.GetMousePosition().y };
	if (cursor_pos.x <= 100.f)
	{
		vis_.MoveCamera({ -1.f, 0.f });
	}
	if (cursor_pos.x >= (f32)vis_.GetScreenDimensions().GetWidth() - 100.f)
	{
		vis_.MoveCamera({ 1.f, 0.f });
	}
	if (cursor_pos.y <= 100.f)
	{
		vis_.MoveCamera({ 0.f, -1.f });
	}
	if (cursor_pos.y >= (f32)vis_.GetScreenDimensions().GetHeight() - 100.f)
	{
		vis_.MoveCamera({ 0.f, 1.f });
	}



	if (g_input.GetKeyState("quit"))
	{
		HAPI.Close();
	}

	if (g_input.GetMouseButtonState(MouseButton::left))
	{
		unit.Pathfind(vis_.GetCamera().ScreenToWorld({ (f32)g_input.GetMousePosition().x, (f32)g_input.GetMousePosition().y }), tile_map_);
		selected_tile_ = tile_map_.GetTileDefinition(vis_.GetCamera().ScreenToWorld({ (f32)g_input.GetMousePosition().x, (f32)g_input.GetMousePosition().y }));
	}
	


	g_input.SetControllerRumble(0, 0, 0);



}

void World::Render(s32 delta_time)
{
	
	vis_.ClearGreyscale(0);
	
	tile_map_.Render(vis_);
	
	
	for (auto& it : entities_)
	{
		it->Render(vis_, delta_time);
	}
	unit.Render(vis_, 0);
	vec2<f32> cursor_pos = vec2<f32>{ (float)g_input.GetMousePosition().x, (float)g_input.GetMousePosition().y };
	cursor_pos = vis_.GetCamera().ScreenToWorld(cursor_pos);
	vis_.RenderSprite("Cursor", cursor_pos, 5);

	// HAPI.RenderText(200, 200, HAPISPACE::HAPI_TColour(0, 255, 255), selected_tile_.ToString());
	vis_.SwapBuffer();
}
