#include "Sprite.hpp"

void Sprite::Render(FrameBuffer& fb) const
{
	s32 x = (u32)ceil(origin_.x);
	s32 y = (u32)ceil(origin_.y);

	s32 x_end = x + width_;
	s32 y_end = y + height_;
	
	rect<s32> spr_rect(y, x, y_end, x_end);
	if (spr_rect.IsOutside(fb.GetRect()))
	{
		return;
	}
	spr_rect.ClipTo(fb.GetRect());
	assert(spr_rect.top >= 0);
	rect<s32> normalised_rect(spr_rect.GetWidth(), spr_rect.GetHeight());

	
	if (has_alpha_)
	{
		u8* fb_ptr = fb.GetPixelsUnsafe();
		fb_ptr += (spr_rect.left + (spr_rect.top * fb.GetWidth())) * 4;
		u8* spr_ptr = (u8*)image_.GetPixels();
		if (y < 0)
		{
			spr_ptr += (image_.GetWidth() + ((image_.GetHeight() - normalised_rect.GetHeight()) * image_.GetWidth())) * 4;
		}
		if (x < 0)
		{
			spr_ptr += (image_.GetWidth() - normalised_rect.GetWidth()) * 4;
		}
		
		// new bug due to clipping
		// textures which clip off the top left of the screen have green dots at the bottom of them 
		for (s32 y_iter = spr_rect.top; y_iter < spr_rect.bottom; y_iter++)
		{
			for (s32 x_iter = spr_rect.left; x_iter < spr_rect.right; x_iter++)
			{
				u8 alpha = spr_ptr[3];
				if (alpha == 0)
				{
					
				}
				else if(alpha == 255)
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
			/*
			if (x < 0)
			{
				spr_ptr += (image_.GetWidth() - normalised_rect.GetWidth()) * 4;
			}
			else
			{
				spr_ptr += (image_.GetWidth() - spr_rect.GetWidth()) * 4;
			}
			*/
			
		}
	}
	else
	{
		u32* fb_ptr = (u32*)fb.GetPixelsUnsafe();
		fb_ptr += spr_rect.left + (spr_rect.top * fb.GetWidth());
		u32* spr_ptr = (u32*)image_.GetPixels();
		spr_ptr += image_.GetWidth() - spr_rect.GetWidth();
		for (s32 y_iter = spr_rect.top; y_iter < spr_rect.bottom; y_iter++)
		{
			memcpy(fb_ptr, spr_ptr,  spr_rect.GetWidth() * sizeof(u32));
			fb_ptr += fb.GetWidth();
			spr_ptr += image_.GetWidth();
			spr_ptr += (image_.GetWidth() - spr_rect.GetWidth());
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
