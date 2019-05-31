#pragma once

#include "FrameBuffer.hpp"
#include "Types.hpp"
#include "Utils.hpp"
#ifndef QUAD_HPP
#define QUAD_HPP

class Quad
{
public:



	Quad(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Vertex& v4, vec4 < u8 > colour) : v1_(v1), v2_(v2), v3_(v3), v4_(v4), colour_(colour)
	{



	}
	void Render(FrameBuffer & fb) const;
private:

	vec4 < u8 > colour_;
	Vertex v1_, v2_, v3_, v4_;
};
#endif // !QUAD_HPP
