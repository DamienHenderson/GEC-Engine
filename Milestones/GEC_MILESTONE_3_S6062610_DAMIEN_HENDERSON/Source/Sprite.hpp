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
		
	    Sprite(const Image& image,const vec2<f32>& origin, bool has_alpha = false) : image_(image), origin_(origin), has_alpha_(has_alpha)
	    {
	    	
	    }
		Sprite(const char* filename, const vec2<f32>& origin, bool has_alpha = false) : image_(filename), origin_(origin), has_alpha_(has_alpha)
		{
			
		}
		void Render(FrameBuffer& fb) const;
		void SetPosition(const vec2<f32>& new_pos);
		s32 GetWidth() const { return image_.GetWidth(); }
		s32 GetHeight() const { return image_.GetHeight(); }
	private:
	    Image image_;
	    vec2<f32> origin_;
	    
		
		bool has_alpha_;
};

#endif