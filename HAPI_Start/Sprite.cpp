#include "Sprite.hpp"

void Sprite::Render(FrameBuffer& fb, int frame_num, const Camera& camera) const
{
	frame_num %= (x_frames_ * y_frames_);
	s32 x_frame = frame_num % x_frames_;
	s32 y_frame = frame_num / x_frames_;
	s32 x = (s32)ceil(origin_.x);
	s32 y = (s32)ceil(origin_.y);



	rect<s32> spr_rect(frame_rect_), fb_rect(fb.GetRect());
	spr_rect.Translate(x, y);
	spr_rect.Translate(-(s32)floorf(camera.GetPosition().x), -(s32)floorf(camera.GetPosition().y));
	if (spr_rect.IsOutside(fb_rect))
	{
		return;
	}
	
	spr_rect.ClipTo(fb_rect);
	s32 clamped_x = spr_rect.left, clamped_y = spr_rect.top;
	assert(spr_rect.top >= 0);
	spr_rect.Translate((s32)floorf(camera.GetPosition().x), (s32)floorf(camera.GetPosition().y));
	spr_rect.Translate(-x, -y);
	spr_rect.ClampPositive();

	spr_rect.Translate(frame_rect_.GetWidth() * x_frame, frame_rect_.GetHeight() * y_frame);

	if (has_alpha_)
	{
		u8* fb_ptr = fb.GetPixelsUnsafe();
		fb_ptr += (clamped_x + (clamped_y * fb.GetWidth())) * 4;
		u8* spr_ptr = (u8*)image_.GetPixels();
		spr_ptr += (spr_rect.left + (spr_rect.top * image_.GetWidth())) * 4;

		// new bug due to clipping
		// textures which clip off the top left of the screen have green dots at the bottom of them 
		for (s32 y_iter = 0; y_iter < spr_rect.GetHeight(); y_iter++)
		{
			for (s32 x_iter = 0; x_iter < spr_rect.GetWidth(); x_iter++)
			{
				u8 alpha = spr_ptr[3];
				if (alpha == 0)
				{

				}
				else if (alpha == 255)
				{
					fb_ptr[0] = spr_ptr[0];
					fb_ptr[1] = spr_ptr[1];
					fb_ptr[2] = spr_ptr[2];
					// fb_ptr[3] = spr_ptr[3];
				}
				else
				{


					fb_ptr[0] = fb_ptr[0] + ((alpha*(spr_ptr[2] - fb_ptr[0])) >> 8);
					fb_ptr[1] = fb_ptr[1] + ((alpha*(spr_ptr[1] - fb_ptr[1])) >> 8);
					fb_ptr[2] = fb_ptr[2] + ((alpha*(spr_ptr[0] - fb_ptr[2])) >> 8);

				}
				spr_ptr += 4;
				fb_ptr += 4;

			}

			fb_ptr += (fb.GetWidth() - spr_rect.GetWidth()) * 4;
			spr_ptr += (image_.GetWidth() - spr_rect.GetWidth()) * 4;


		}
	}
	else
	{
		u8* fb_ptr = fb.GetPixelsUnsafe();
		fb_ptr += (clamped_x + (clamped_y * fb.GetWidth())) * 4;
		u8* spr_ptr = (u8*)image_.GetPixels();
		spr_ptr += (spr_rect.left + (spr_rect.top * image_.GetWidth())) * 4;
		for (s32 y_iter = spr_rect.top; y_iter < spr_rect.bottom; y_iter++)
		{
			memcpy(fb_ptr, spr_ptr, spr_rect.GetWidth() * 4);
			fb_ptr += fb.GetWidth() * 4;

			spr_ptr += image_.GetWidth() * 4;
		}
	}


}

void Sprite::RenderThreaded(FrameBuffer & fb, int frame_num, const Camera& camera) const
{
	frame_num %= (x_frames_ * y_frames_);
	s32 x_frame = frame_num % x_frames_;
	s32 y_frame = frame_num / x_frames_;
	s32 x = (s32)ceil(origin_.x);
	s32 y = (s32)ceil(origin_.y);

	// vec2<f32> screen_space_float = camera.WorldToScreen({ (f32)x,(f32)y });
	// vec2<s32> screen_space{ (s32)screen_space_float.x,(s32)screen_space_float.y };

	rect<s32> spr_rect(frame_rect_), fb_rect(fb.GetRect());
	spr_rect.Translate(x, y);
	spr_rect.Translate(-(s32)floorf(camera.GetPosition().x), -(s32)floorf(camera.GetPosition().y));

	if (spr_rect.IsOutside(fb_rect))
	{
		return;
	}
	

	spr_rect.ClipTo(fb_rect);
	s32 clamped_x = spr_rect.left, clamped_y = spr_rect.top;
	assert(spr_rect.top >= 0);
	spr_rect.Translate((s32)floorf(camera.GetPosition().x), (s32)floorf(camera.GetPosition().y));
	spr_rect.Translate(-x, -y);
	spr_rect.ClampPositive();

	spr_rect.Translate(frame_rect_.GetWidth() * x_frame, frame_rect_.GetHeight() * y_frame);

	u8* fb_ptr = fb.GetPixelsUnsafe();
	fb_ptr += (clamped_x + (clamped_y * fb.GetWidth())) * 4;
	u8* spr_ptr = (u8*)image_.GetPixels();
	spr_ptr += (spr_rect.left + (spr_rect.top * image_.GetWidth())) * 4;


	const int thread_count = 4;

	std::future<void> threads[thread_count];


	// split into 4 corners for rendering
	/*
	for (int i = 0; i < thread_count; i++)
	{
		// if there is a remainder from 2 then offset in the x
		bool offset_x = i % 2;
		// if the value is 2 or higher then offset in the y
		bool offset_y = std::max(0,i - 1);
		u32 spr_offset{ 0 };
		u32 fb_offset{ 0 };
		if (offset_x && offset_y)
		{
			spr_offset = (spr_rect.GetWidth() / 2 + (spr_rect.GetHeight() / 2 * image_.GetWidth())) * 4;
			fb_offset = (spr_rect.GetWidth() / 2 + (spr_rect.GetHeight() / 2 * fb.GetWidth())) * 4;
		}
		else if (offset_x)
		{
			spr_offset = (spr_rect.GetWidth() / 2) * 4;
			fb_offset = (spr_rect.GetWidth() / 2) * 4;
		}
		else if (offset_y)
		{
			spr_offset = ((spr_rect.GetHeight() / 2) * image_.GetWidth()) * 4;
			fb_offset = ((spr_rect.GetHeight() / 2) * fb.GetWidth()) * 4;
		}
		u8* spr_start = spr_ptr + spr_offset;
		u8* fb_start = fb_ptr + fb_offset;
		u32 spr_line_offset{ 0 };
		u32 fb_line_offset{ 0 };
		if (has_alpha_)
		{
			fb_line_offset = (fb.GetWidth() - (spr_rect.GetWidth() / 2)) * 4;
			spr_line_offset = (image_.GetWidth() - (spr_rect.GetWidth() / 2)) * 4;
		}
		else
		{
			fb_line_offset = fb.GetWidth() * 4;
			spr_line_offset = image_.GetWidth() * 4;
		}

		threads[i] = std::async(std::launch::async, RenderRange, spr_start, fb_start, spr_rect.GetWidth() / 2, spr_rect.GetHeight() / 2, spr_line_offset, fb_line_offset, has_alpha_);
	}
	*/

	// split into 4 horizontal sections along the y axis

	for (int i = 0; i < thread_count; i++)
	{
		u32 x_count = spr_rect.GetWidth();
		u32 y_count = spr_rect.GetHeight() / 4;
		u32 spr_offset = ((y_count * image_.GetWidth()) * 4) * i;
		u32 fb_offset = ((y_count * fb.GetWidth()) * 4) * i;

		u32 spr_line_offset{ 0 };
		u32 fb_line_offset{ 0 };
		if (has_alpha_)
		{
			fb_line_offset = (fb.GetWidth() - (spr_rect.GetWidth())) * 4;
			spr_line_offset = (image_.GetWidth() - (spr_rect.GetWidth())) * 4;
		}
		else
		{
			fb_line_offset = fb.GetWidth() * 4;
			spr_line_offset = image_.GetWidth() * 4;
		}
		threads[i] = std::async(std::launch::async, RenderRange, spr_ptr + spr_offset, fb_ptr + fb_offset, x_count, y_count, spr_line_offset, fb_line_offset, has_alpha_);
	}

	for (int i = 0; i < thread_count; i++)
	{
		threads[i].get();
	}

	// threads[thread_count - 1] = std::async(std::launch::async, RenderRange);
}
void RenderRange(u8 * spr_ptr, u8 * fb_ptr, u32 x_count, u32 y_count, u32 line_offset, u32 fb_line_offset, bool alpha)
{
	if (alpha)
	{


		// new bug due to clipping
		// textures which clip off the top left of the screen have green dots at the bottom of them 
		for (u32 y_iter = 0; y_iter < y_count; y_iter++)
		{
			for (u32 x_iter = 0; x_iter < x_count; x_iter++)
			{
				u8 alpha = spr_ptr[3];
				if (alpha == 0)
				{

				}
				else if (alpha == 255)
				{
					fb_ptr[0] = spr_ptr[0];
					fb_ptr[1] = spr_ptr[1];
					fb_ptr[2] = spr_ptr[2];
					// fb_ptr[3] = spr_ptr[3];
				}
				else
				{


					fb_ptr[0] = fb_ptr[0] + ((alpha*(spr_ptr[2] - fb_ptr[0])) >> 8);
					fb_ptr[1] = fb_ptr[1] + ((alpha*(spr_ptr[1] - fb_ptr[1])) >> 8);
					fb_ptr[2] = fb_ptr[2] + ((alpha*(spr_ptr[0] - fb_ptr[2])) >> 8);

				}
				spr_ptr += 4;
				fb_ptr += 4;

			}

			fb_ptr += fb_line_offset;
			spr_ptr += line_offset;


		}
	}
	else
	{

		for (s32 y_iter = 0; y_iter < (s32)y_count; y_iter++)
		{
			memcpy(fb_ptr, spr_ptr, x_count * 4);
			fb_ptr += fb_line_offset;
			spr_ptr += line_offset;

		}
	}
}
void Sprite::SetPosition(const vec2<f32>& new_pos)
{
	origin_ = new_pos;
}


