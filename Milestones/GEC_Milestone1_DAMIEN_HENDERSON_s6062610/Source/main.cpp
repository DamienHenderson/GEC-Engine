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

#include "FrameBuffer.hpp"
#include "Sprite.hpp"
#include "Line.hpp"
#include "Screen.hpp"
// HAPI itself is wrapped in the HAPISPACE namespace
using namespace HAPISPACE;

struct Star
{
	f32 x_, y_, z_;
	u32 colour_;
	Star()
	{
		x_ = std::rand() % 2000;
		y_ = std::rand() % 1200;
		z_ = std::rand() % 500;
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
			x_ = std::rand() % fb.GetWidth();
			y_ = std::rand() % fb.GetHeight();
		}
		
	}
};
constexpr u32 star_count = 100000;
// Every HAPI program has a HAPI_Main as an entry point
// When this function exits the program will close down
void HAPI_Main()
{
	// eye dist of - 20.0f looks quite good
	u32 width = 1920, height = 1080;
	Screen scr(width, height,"Damien Henderson", false);
	/*
	if (!HAPI.Initialise(width, height, "Damien Henderson", eDefaults))
	{
		assert("HAPI Initialise failed" && false);
		return;
	}
	*/
	Star* stars = new Star[star_count];
	// std::array<Star, star_count> stars;
	HAPI.SetShowFPS(true, 0, 0, HAPI_TColour::GREEN);
	
	FrameBuffer fb(width, height);
	FrameBuffer const_colour_fb{ width,height };
	FrameBuffer bg_framebuffer{ width,height };
	const_colour_fb.Clear(PackRGBA(100, 149, 237, 255));
	fb.Clear(const_colour_fb);
	bg_framebuffer.ClearGreyscale(0);
	f32 sprite_x{ 600.0f }, sprite_y{ 600.0f };
	
	Sprite spr("Data/background.tga", {0.0f, 0.0f});
	spr.Render(const_colour_fb);
	Line ln(vec2<u32>{ 100,200 }, vec2<u32>{ 300,200 }, vec4<u8>{ 0,255,133,255 });
	Line ln2(vec2<u32>{ 100, 200 }, vec2<u32>{ 600, 500 }, vec4<u8>{ 0, 255, 133, 255 });
	
	Sprite alpha_sprite("Data/alphaThing.tga", { 500.0f, 500.0f });

	
	Sprite player_sprite("Data/playerSprite.tga", { 700.0f, 300.0f });

	f32 eye_dist = 100.0f;
	u32 centre_x = width / 2;
	u32 centre_y = height / 2;
	u32 num_frames = 0;

	const HAPI_TKeyboardData& keyboard = HAPI.GetKeyboardData();
	const HAPI_TMouseData& mouse = HAPI.GetMouseData();
	
	while (scr.Update())
	{
		
		scr.Blit(fb);
		fb.Clear(bg_framebuffer);
		// fb.Clear(PackRGBA(100, 149, 237, 255));
		// fb.Clear(const_colour_fb);
		// spr.Render(fb);
		//alpha_sprite.Render(fb, true);
		//player_sprite.Render(fb, true);
		//ln.Render(fb);
		//ln2.Render(fb);
		
		/*
		for (int i = 0; i < 20; i++)
		{
			float x0 = std::rand() % width;
			float y0 = std::rand() % height;

			float x1 = std::rand() % width;
			float y1 = std::rand() % height;

			float x2 = std::rand() % width;
			float y2 = std::rand() % height;

			Vertex a(x0, y0,1.0f), b(x1, y1,1.0f), c(x2, y2,1.0f);
			u8 red = std::rand() % 256;
			u8 green = std::rand() % 256;
			u8 blue = std::rand() % 256;
			u8 alpha = 255;
			fb.RenderTriangle(a, b, c, PackRGBA(red, green, blue, alpha));
		}
		*/

		
		HAPI.RenderText(mouse.x, mouse.y, HAPI_TColour::GREEN, "Mouse is here");

		const HAPI_TControllerData& controller = HAPI.GetControllerData(0);
		if (controller.isAttached)
		{
			if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				centre_x -= 5;
			}
			if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_X] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				centre_x += 5;
			}
			if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] > HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				centre_y += 5;
			}
			if (controller.analogueButtons[HK_ANALOGUE_LEFT_THUMB_Y] < -HK_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				centre_y -= 5;
			}
		}
		
		if (keyboard.scanCode[HK_UP])
		{
			eye_dist += 5.0f;
		}
		if (keyboard.scanCode[HK_DOWN])
		{
			eye_dist -= 5.0f;
		}
		if (keyboard.scanCode[HK_ESCAPE])
		{
			HAPI.Close();
		}
		
		
		// spr.SetPosition({(f32)mouse.x,(f32)mouse.y });
	
		for (u32 i = 0; i < star_count; i++)
		{
			//if (num_frames % 5 == 0)
			//{
				stars[i].Update(fb);
			//}
			

				stars[i].Render(fb, eye_dist,centre_x,centre_y);
		}
		num_frames++;
		// HAPI.SetControllerRumble(0, std::rand() % 65536, std::rand() % 65536);
		
	}
	SafeDeleteArray(stars);
	HAPI.SetControllerRumble(0, 0, 0);
	
}

