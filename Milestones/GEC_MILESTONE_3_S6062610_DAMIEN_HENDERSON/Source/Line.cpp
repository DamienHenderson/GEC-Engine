#include "Line.hpp"

void Line::Render(FrameBuffer & fb)
{
	f32 delta_x = (f32)end_.x - (f32)start_.x;
	f32 delta_y = (f32)end_.y - (f32)start_.y;
	if (delta_x == 0.0f)
	{
		// Vertical Line
		for (u32 i = start_.y; i <= end_.y; i++)
		{
			fb.SetPixel(PackRGBA(colour_), start_.x, i);
		}
		return;
	}

	f32 delta_err = fabs(delta_y / delta_x);
	f32 error = 0.0f;
	if (delta_y == 0.0f)
	{
		// Horizontal Line
		fb.DrawScanline(start_.y, start_.x, end_.x, PackRGBA(colour_));
		return;
	}


	u32 y = start_.y;
	// <= end_.x so the last pixel is rendered at the end of the line
	for (u32 x = start_.x; x <= end_.x; x++)
	{
		fb.SetPixel(PackRGBA(colour_), x, y);
		error += delta_err;
		if (error >= 0.5f)
		{
			y++;
			error -= 1.0f;
		}
	}
}