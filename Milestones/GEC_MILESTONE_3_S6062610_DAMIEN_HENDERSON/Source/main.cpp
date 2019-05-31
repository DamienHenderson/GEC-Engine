/*
	HAPI Start
	----------
	This solution contains an already set up HAPI project and this main file

	The directory structure and main files are:

	HAPI_Start - contains the Visual Studio solution file (.sln)
		HAPI_Start - contains the Visual Studio HAPI_APP project file (.vcxproj) and source code
			HAPI - the directory with all the HAPI library files
			Data - a place to put your data files with a few sample ones provided

	Additionally in the top directory there are two batch files for creating a redistributable Demo folder
*/


// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <HAPI_InputCodes.h>

#include <cmath>
#include <array>
#include <fstream>

#include "FrameBuffer.hpp"
#include "Sprite.hpp"
#include "Line.hpp"
#include "Screen.hpp"
#include "Visualisation.hpp"

#include "PoolAllocator.hpp"
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

struct Star
{
	f32 x_, y_, z_;
	u32 colour_;
	Star()
	{
		x_ = (f32)(std::rand() % 2000);
		y_ = (f32)(std::rand() % 1200);
		z_ = (f32)(std::rand() % 500);
		u8 r = std::rand() % 256;
		u8 g = std::rand() % 256;
		u8 b = std::rand() % 256;
		colour_ = PackRGBA(r, g, b, 255);
	}
	Star(f32 x, f32 y, f32 z, u32 packed) : x_(x), y_(y), z_(z), colour_(packed)
	{

	}
	void Render(FrameBuffer& fb, f32 eye_dist, u32 centre_x, u32 centre_y)
	{

		fb.RenderStar(x_, y_, z_, colour_, eye_dist, centre_x, centre_y);


	}
	void Update(FrameBuffer& fb)
	{
		z_ -= 1; // (float)(std::rand() / RAND_MAX);
		if (z_ <= 0.0f)
		{
			z_ = 500.0f;
			x_ = (f32)(std::rand() % fb.GetWidth());
			y_ = (f32)(std::rand() % fb.GetHeight());
		}

	}
};
constexpr u32 star_count = 100000;
// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	// TODO: think about how can i make this pool allocator more useful?
	
	
	
	
	
	// ensure the destructors have been called before leak check
	{
		// eye dist of - 20.0f looks quite good for stars
		s32 width = 1280, height = 720;

		Visualisation vis(width, height, "Damien Henderson");

		rect<s32> screen_centre_rect{ (height / 2) - 32, (width / 2) - 32, (height / 2) + 32, (width / 2) + 32 };

		HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);



		FrameBuffer const_colour_fb(width, height);
		const_colour_fb.ClearGreyscale(0);

		f32 sprite_x{ 600.0f }, sprite_y{ 600.0f };

		bool res = vis.LoadSprite("Data/background.tga", true);
		if (!res)
		{
			return;
		}

		Line ln(vec2<u32>{ 100, 200 }, vec2<u32>{ 300, 200 }, vec4<u8>{ 0, 255, 133, 255 });
		Line ln2(vec2<u32>{ 100, 200 }, vec2<u32>{ 600, 500 }, vec4<u8>{ 0, 255, 133, 255 });

		res = vis.LoadSprite("Data/alphaThing.tga", true);
		if (!res)
		{
			return;
		}

		res = vis.LoadSprite("Data/playerSprite.tga", true);
		if (!res)
		{
			return;
		}

		f32 eye_dist = 100.0f;
		u32 centre_x = width / 2;
		u32 centre_y = height / 2;
		u32 num_frames = 0;

		const HAPI_TKeyboardData& keyboard = HAPI.GetKeyboardData();
		const HAPI_TMouseData& mouse = HAPI.GetMouseData();

		vec2<f32> player_pos{ 640.0f,360.0f };
		vec2<f32> alpha_thing_pos{ 100.0f,300.0f };
		while (vis.Update())
		{

			vis.SwapBuffer();

			// vis.ClearGreyscale(0);
			// vis.Clear(const_colour_fb);
			vis.Clear(0);
			vis.RenderSprite("Data/background.tga", { 0.f,0.f });
			vis.RenderSprite("Data/alphaThing.tga", alpha_thing_pos);
			vis.RenderSprite("Data/playerSprite.tga", player_pos);





			HAPI.RenderText(mouse.x, mouse.y, HAPI_TColour::GREEN, "Mouse is here");

			const HAPI_TControllerData& controller = HAPI.GetControllerData(0);
			if (controller.isAttached)
			{
				
				if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					player_pos.x += 1.0f;
				}
				if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					player_pos.x -= 1.0f;
				}
				if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					player_pos.y -= 1.0f;
				}
				if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					player_pos.y += 1.0f; 
				}

				vec2<s32> player_pos_integer{ (s32)ceil(player_pos.x), (s32)ceil(player_pos.y) };
				if (screen_centre_rect.Contains(player_pos_integer))
				{
					HAPI.SetControllerRumble(0, 65535, 65535);
				}
				else
				{
					HAPI.SetControllerRumble(0, 0, 0);
				}
				
				
			}

			if (keyboard.scanCode[HK_UP])
			{
				player_pos.y -= 1.0f;
			}
			if (keyboard.scanCode[HK_DOWN])
			{
				player_pos.y += 1.0f;
			}
			if (keyboard.scanCode[HK_LEFT])
			{
				player_pos.x -= 1.0f;
			}
			if (keyboard.scanCode[HK_RIGHT])
			{
				player_pos.x += 1.0f;
			}
			if (keyboard.scanCode['W'])
			{
				alpha_thing_pos.y -= 1.0f;
			}
			if (keyboard.scanCode['S'])
			{
				alpha_thing_pos.y += 1.0f;
			}
			if (keyboard.scanCode['A'])
			{
				alpha_thing_pos.x -= 1.0f;
			}
			if (keyboard.scanCode['D'])
			{
				alpha_thing_pos.x += 1.0f;
			}

			if (keyboard.scanCode[HK_ESCAPE])
			{
				HAPI.Close();
			}


			num_frames++;
			// HAPI.SetControllerRumble(0, std::rand() % 65536, std::rand() % 65536);

		}

		HAPI.SetControllerRumble(0, 0, 0);
		// g_allocator.MemDump("memdump.bin");
	}
	g_allocator.LeakCheck("Leak_Check.txt");
}
