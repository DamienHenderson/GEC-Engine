#include "Sprite.hpp"

void Sprite::Render(FrameBuffer& fb, bool alpha) const
{
	u32 x = (u32)ceil(origin_.x);
	u32 y = (u32)ceil(origin_.y);

	u32 x_end = x + width_;
	u32 y_end = y + height_;
	/*
	if (x == 0 && y == 0 && x_end == fb.GetWidth() && y_end == fb.GetHeight())
	{
		memcpy(fb.GetPixelsUnsafe(), image_.GetPixels(), image_.GetWidth() * image_.GetHeight() * 4);
		return;
	}
	*/
	if (x_end > fb.GetWidth())
	{
		x_end = fb.GetWidth();
	}
	if (y_end > fb.GetHeight())
	{
		y_end = fb.GetHeight();
	}


	if (alpha)
	{
		u8* fb_ptr = fb.GetPixelsUnsafe();
		fb_ptr += (x + (y * fb.GetWidth())) * 4;
		u8* spr_ptr = (u8*)image_.GetPixels();
		for (u32 y_iter = y; y_iter < y_end; y_iter++)
		{
			for (u32 x_iter = x; x_iter < x_end; x_iter++)
			{
				f32 alpha = spr_ptr[3] / 255.0f;

				fb_ptr[0] = ((f32)spr_ptr[0] * alpha) + ((1.0f - alpha) * (f32)fb_ptr[0]);
				fb_ptr[1] = ((f32)spr_ptr[1] * alpha) + ((1.0f - alpha) * (f32)fb_ptr[1]);
				fb_ptr[2] = ((f32)spr_ptr[2] * alpha) + ((1.0f - alpha) * (f32)fb_ptr[2]);

				spr_ptr += 4;
				fb_ptr += 4;

			}
			fb_ptr += (fb.GetWidth() - width_) * 4;
		}
	}
	else
	{
		u32* fb_ptr = (u32*)fb.GetPixelsUnsafe();
		fb_ptr += x + (y * fb.GetWidth());
		u32* spr_ptr = (u32*)image_.GetPixels();
		for (u32 y_iter = y; y_iter < y_end; y_iter++)
		{
			memcpy(fb_ptr, spr_ptr, (x_end - x) * sizeof(u32));
			fb_ptr += fb.GetWidth();
			spr_ptr += width_;
		}
	}

	/*
	for (u32 j = y; j < y_end; j++)
	{
		for (u32 i = x; i < x_end; i++)
		{
			u32 col = image_.GetPixel(i, j,true);
			fb.SetPixel(col, i, j);
		}
	}
	*/
}

void Sprite::SetPosition(const vec2<f32>& new_pos)
{
	origin_ = new_pos;
}
