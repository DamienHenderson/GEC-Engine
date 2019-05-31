#include "Screen.hpp"



Screen::Screen(u32& width, u32& height, const char* title, bool fullscreen) : width_(width), height_(height)
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
		std::cerr << "Screen Pointer is null\n";
	}
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
