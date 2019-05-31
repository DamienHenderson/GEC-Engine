#pragma once
#include <HAPI_lib.h>

#include <string>

#include "Types.hpp"
#include "FrameBuffer.hpp"
class Screen
{
public:
	Screen() {}
	Screen(s32& width, s32& height, const std::string& title, bool fullscreen = false);
	~Screen();

	bool Initialise(s32& width, s32& height, const std::string& title, bool fullscreen = false);
	bool Update();
	void Blit(const FrameBuffer& fb);
private:
	u8* scr_buffer;
	s32 width_{ 0 }, height_{ 0 };
};

