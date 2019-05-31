#pragma once

#include "FrameBuffer.hpp"
#include "Types.hpp"
#ifndef LINE_HPP
#define LINE_HPP

class Line
{
public:
	Line(vec2 < u32 > start, vec2 < u32 > end, vec4 < u8 > colour) :start_(start), end_(end),
		colour_(colour)
	{
	}
	// implemented using bresenham's line algorithm using pseudocode from
	// wikipedia
	// TODO: thick lines
	void Render(FrameBuffer & fb);

private:
	vec2 < u32 > start_, end_;
	vec4 < u8 > colour_{0, 0, 0, 0 };

};
#endif