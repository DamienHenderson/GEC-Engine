#include "Screen.hpp"



Screen::Screen(s32& width, s32& height, const std::string& title, bool fullscreen) : width_(width), height_(height)
{
	bool res = false;
	 if (fullscreen)
	 {
		res = HAPI.Initialise((int&)width, (int&)height, title, HAPISPACE::eFullscreen);
	 }
	 else
	 {
		res = HAPI.Initialise((int&)width, (int&)height, title);
	 }
	 
	
	assert(res);

	scr_buffer = HAPI.GetScreenPointer();

	if (scr_buffer == nullptr)
	{
		DEBUG_ONLY(std::cerr << "Screen Pointer is null\n";);
	}
}

bool Screen::Initialise(s32 & width, s32 & height, const std::string & title, bool fullscreen)
{
	
	bool res = false;
	if (fullscreen)
	{
		res = HAPI.Initialise((int&)width, (int&)height, title, HAPISPACE::eFullscreen);
	}
	else
	{
		res = HAPI.Initialise((int&)width, (int&)height, title);
	}


	assert(res);

	scr_buffer = HAPI.GetScreenPointer();

	if (scr_buffer == nullptr)
	{
		DEBUG_ONLY(std::cerr << "Screen Pointer is null\n";);
	}
	width_ = width;
	height_ = height;
	return res;
}

bool Screen::Update()
{
	return HAPI.Update();
}

void Screen::Blit(const FrameBuffer & fb)
{
	// should i check for cases where the framebuffer passed in is smaller or larger than the screen?
	// or should i assume that the framebuffer is of the correct size
	
	memcpy(scr_buffer, fb.GetPixels(), width_* height_ * 4);
}


Screen::~Screen()
{
}
