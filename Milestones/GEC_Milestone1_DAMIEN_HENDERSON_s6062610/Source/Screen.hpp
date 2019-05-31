#pragma once
#include <HAPI_lib.h>

#include "Types.hpp"
#include "FrameBuffer.hpp"
class Screen
{
public:
	Screen(u32& width, u32& height,const char* title, bool fullscreen = false);
	~Screen();

	bool Update();
	void Blit(const FrameBuffer& fb);
private:
	u8* scr_buffer;
	u32 width_, height_;
};

