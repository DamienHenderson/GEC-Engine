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
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#endif

// Include the HAPI header to get access to all of HAPIs interfaces
#include <HAPI_lib.h>
#include <HAPI_Types.h>
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

#include "World.hpp"
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
	

	s32 width{ 1280 }, height{720};
	World world;
	bool res = world.Initialise("Data/config.xml", width, height);
	world.LoadFromFile("Data/", "level.xml");
	res = world.Run();

	//DEBUG_ONLY(g_allocator.MemDump("memdump.bin"););



	DEBUG_ONLY(g_allocator.LeakCheck("Leak_Check.txt"););

	
}

