#pragma once

#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <cstring>
#include "Types.hpp"
#include "Image.hpp"
#include "FrameBuffer.hpp"
#include "Camera.hpp"


class FrameBuffer;

void RenderRange(u8* spr_ptr, u8* fb_ptr, u32 x_count, u32 y_count, u32 offset, u32 fb_line_offset, bool alpha);

class Sprite
{
	public:
		// TODO: X and Y sprite values for grid based spritesheets
		Sprite(const Image& image, const vec2<f32>& origin, bool has_alpha = false, int x_frames = 1, int y_frames = 1) : image_(image), origin_(origin), has_alpha_(has_alpha), x_frames_(x_frames), y_frames_(y_frames),frame_rect_(image.GetWidth() / x_frames, image.GetHeight() / y_frames)
	    {
	    	
	    }
		// TODO: X and Y sprite values for grid based spritesheets
		Sprite(const char* filename, const vec2<f32>& origin, bool has_alpha = false, int x_frames = 1, int y_frames = 1) : image_(filename), origin_(origin), has_alpha_(has_alpha), x_frames_(x_frames), y_frames_(y_frames), frame_rect_(image_.GetWidth() / x_frames, image_.GetHeight() / y_frames)
		{
			
		}
		void Render(FrameBuffer& fb, int frame_num = 0, const Camera& camera = Camera()) const;
		void RenderThreaded(FrameBuffer& fb, int frame_num = 0, const Camera& camera = Camera()) const;
		void SetPosition(const vec2<f32>& new_pos);
		s32 GetWidth() const { return image_.GetWidth(); }
		s32 GetHeight() const { return image_.GetHeight(); }
	private:
		
	    Image image_;
	    vec2<f32> origin_;
		rect<s32> frame_rect_;
		
		int x_frames_{ 1 }, y_frames_{ 1 };
		bool has_alpha_;
};

#endif