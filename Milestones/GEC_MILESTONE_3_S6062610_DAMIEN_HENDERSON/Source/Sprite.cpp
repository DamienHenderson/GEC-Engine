#include "Sprite.hpp"

void Sprite::Render(FrameBuffer& fb) const
{
	s32 x = (s32)ceil(origin_.x);
	s32 y = (s32)ceil(origin_.y);


	
	rect<s32> spr_rect(image_.GetWidth(),image_.GetHeight());
	spr_rect.Translate(x, y);
	if (spr_rect.IsOutside(fb.GetRect()))
	{
		return;
	}
	spr_rect.ClipTo(fb.GetRect());
	s32 clamped_x = spr_rect.left, clamped_y = spr_rect.top;
	assert(spr_rect.top >= 0);
	spr_rect.Translate(-x, -y);
	spr_rect.ClampPositive();


	
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
			memcpy(fb_ptr, spr_ptr,  spr_rect.GetWidth() * 4);
			fb_ptr += fb.GetWidth() * 4;
			
			spr_ptr += image_.GetWidth() * 4;
		}
	}

	
}

void Sprite::SetPosition(const vec2<f32>& new_pos)
{
	origin_ = new_pos;
}
