#pragma once

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <cstring>
#include "Types.hpp"
#include "Image.hpp"
#include "FrameBuffer.hpp"

class FrameBuffer;

class Sprite
{
	public:
		
	    Sprite(const Image& image,const vec2<f32>& origin,u32 width,u32 height) : image_(image), origin_(origin), width_(width),height_(height)
	    {
	    	
	    }
		Sprite(const char* filename, const vec2<f32>& origin) : image_(filename), origin_(origin)
		{
			width_ = image_.GetWidth();
			height_ = image_.GetHeight();
		}
		void Render(FrameBuffer& fb,bool alpha = false) const;
		void SetPosition(const vec2<f32>& new_pos);
	
	private:
	    Image image_;
	    vec2<f32> origin_;
	    u32 width_,height_;
};

#endif