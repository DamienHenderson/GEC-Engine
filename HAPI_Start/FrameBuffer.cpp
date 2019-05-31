#include "FrameBuffer.hpp"






void FrameBuffer::RenderStar(f32 x, f32 y, f32 z, u32 packed, f32 eye_dist)
{
	

	f32 c_x = (f32)width_ / 2.0f;
	f32 c_y = (f32)height_ / 2.0f;
	s32 s_x = static_cast<s32>(((eye_dist * (x - c_x)) / (eye_dist + z)) + c_x);
	s32 s_y = static_cast<s32>(((eye_dist * (y - c_y)) / (eye_dist + z)) + c_y);
	u32 idx = (u32)(s_x + (s_y * width_));

	// clip non visible stars
	if (s_x >= width_ || s_y >= height_ || x < 0 || y < 0)
	{
		return;
	}


	 if (z >= 100.0f)
	 {
		SetPixel(packed, s_x, s_y, z);
	 }
	
	else if (z >= 50.0f)
	{


		// top row
		SetPixel(packed, s_x - 1, s_y - 1, z);
		SetPixel(packed, s_x, s_y - 1, z);
		SetPixel(packed, s_x + 1, s_y - 1, z);

		// middle row
		SetPixel(packed, s_x - 1, s_y, z);
		SetPixel(packed, s_x, s_y, z);
		SetPixel(packed, s_x + 1, s_y, z);

		// bottom row
		SetPixel(packed, s_x - 1, s_y + 1, z);
		SetPixel(packed, s_x, s_y + 1, z);
		SetPixel(packed, s_x + 1, s_y + 1, z);
	}
	else
	{


		// top row
		SetPixel(packed, s_x - 2, s_y - 2, z);
		SetPixel(packed, s_x - 1, s_y - 2, z);
		SetPixel(packed, s_x, s_y - 2, z);
		SetPixel(packed, s_x + 1, s_y - 2, z);
		SetPixel(packed, s_x + 2, s_y - 2, z);

		// upper middle row
		SetPixel(packed, s_x - 2, s_y - 1, z);
		SetPixel(packed, s_x - 1, s_y - 1, z);
		SetPixel(packed, s_x, s_y - 1, z);
		SetPixel(packed, s_x + 1, s_y - 1, z);
		SetPixel(packed, s_x + 2, s_y - 1, z);
		// middle row
		SetPixel(packed, s_x - 2, s_y, z);
		SetPixel(packed, s_x - 1, s_y, z);
		SetPixel(packed, s_x, s_y, z);
		SetPixel(packed, s_x + 1, s_y, z);
		SetPixel(packed, s_x + 2, s_y, z);

		// lower middle row
		SetPixel(packed, s_x - 2, s_y + 1, z);
		SetPixel(packed, s_x - 1, s_y + 1, z);
		SetPixel(packed, s_x, s_y + 1, z);
		SetPixel(packed, s_x + 1, s_y + 1, z);
		SetPixel(packed, s_x + 2, s_y + 1, z);

		// bottom row
		SetPixel(packed, s_x - 2, s_y + 1, z);
		SetPixel(packed, s_x - 1, s_y + 1, z);
		SetPixel(packed, s_x, s_y + 1, z);
		SetPixel(packed, s_x + 1, s_y + 1, z);
		SetPixel(packed, s_x + 2, s_y + 1, z);
	}
	

}

void FrameBuffer::RenderStar(f32 x, f32 y, f32 z, u32 packed, f32 eye_dist, s32 centre_x, s32 centre_y)
{
	f32 c_x = (f32)centre_x;
	f32 c_y = (f32)centre_y;
	s32 s_x = static_cast<s32>(((eye_dist * (x - c_x)) / (eye_dist + z)) + c_x);
	s32 s_y = static_cast<s32>(((eye_dist * (y - c_y)) / (eye_dist + z)) + c_y);
	u32 idx = (s_x + (s_y * width_));

	// clip non visible stars
	if (s_x >= width_ || s_y >= height_ || x < 0 || y < 0)
	{
		return;
	}


	if (z >= 100.0f)
	{
		SetPixel(packed, s_x, s_y, z);
	}
	
	else if (z >= 50.0f)
	{


		// top row
		SetPixel(packed, s_x - 1, s_y - 1, z);
		SetPixel(packed, s_x, s_y - 1, z);
		SetPixel(packed, s_x + 1, s_y - 1, z);

		// middle row
		SetPixel(packed, s_x - 1, s_y, z);
		SetPixel(packed, s_x, s_y, z);
		SetPixel(packed, s_x + 1, s_y, z);

		// bottom row
		SetPixel(packed, s_x - 1, s_y + 1, z);
		SetPixel(packed, s_x, s_y + 1, z);
		SetPixel(packed, s_x + 1, s_y + 1, z);
	}
	else
	{


		// top row
		SetPixel(packed, s_x - 2, s_y - 2, z);
		SetPixel(packed, s_x - 1, s_y - 2, z);
		SetPixel(packed, s_x, s_y - 2, z);
		SetPixel(packed, s_x + 1, s_y - 2, z);
		SetPixel(packed, s_x + 2, s_y - 2, z);

		// upper middle row
		SetPixel(packed, s_x - 2, s_y - 1, z);
		SetPixel(packed, s_x - 1, s_y - 1, z);
		SetPixel(packed, s_x, s_y - 1, z);
		SetPixel(packed, s_x + 1, s_y - 1, z);
		SetPixel(packed, s_x + 2, s_y - 1, z);
		// middle row
		SetPixel(packed, s_x - 2, s_y, z);
		SetPixel(packed, s_x - 1, s_y, z);
		SetPixel(packed, s_x, s_y, z);
		SetPixel(packed, s_x + 1, s_y, z);
		SetPixel(packed, s_x + 2, s_y, z);

		// lower middle row
		SetPixel(packed, s_x - 2, s_y + 1, z);
		SetPixel(packed, s_x - 1, s_y + 1, z);
		SetPixel(packed, s_x, s_y + 1, z);
		SetPixel(packed, s_x + 1, s_y + 1, z);
		SetPixel(packed, s_x + 2, s_y + 1, z);

		// bottom row
		SetPixel(packed, s_x - 2, s_y + 1, z);
		SetPixel(packed, s_x - 1, s_y + 1, z);
		SetPixel(packed, s_x, s_y + 1, z);
		SetPixel(packed, s_x + 1, s_y + 1, z);
		SetPixel(packed, s_x + 2, s_y + 1, z);
	}
	
}

void FrameBuffer::RenderTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, u32 colour)
{
	// TODO: colours per vertex
	// TODO: texture mapping
	// TODO: colour interpolation
	// TODO: perspective rendering
	// TODO: 3D transformation
	// TODO: Depth testing

	Vertex v_top = v1;
	Vertex v_mid = v2;
	Vertex v_bottom = v3;

	// ps_.Scale(v_top);
	// ps_.Scale(v_mid);
	// ps_.Scale(v_bottom);

	// Sort vertices into min, mid and max
	// on the y axis with 0 being the top of the
	// screen
	if (v_bottom.pos_.y < v_mid.pos_.y)
	{
		// DEBUG_ONLY( std::cout <<  "swapped mid/max\n";

		std::swap(v_bottom, v_mid);

	}
	if (v_mid.pos_.y < v_top.pos_.y)
	{
		// DEBUG_ONLY( std::cout <<  "swapped min/mid\n";

		std::swap(v_mid, v_top);

	}
	if (v_bottom.pos_.y < v_mid.pos_.y)
	{
		// DEBUG_ONLY( std::cout <<  "swapped mid/max\n";

		std::swap(v_bottom, v_mid);

	}


	if (v_top.pos_.y == v_mid.pos_.y)
	{
		// flat top triangle

		// sort top vertices by x
		if (v_top.pos_.x > v_mid.pos_.x)
		{
			std::swap(v_top, v_mid);
		}
		RenderFlatTopTriangle(v_top, v_mid, v_bottom, colour);
	}
	else if (v_mid.pos_.y == v_bottom.pos_.y)
	{
		// flat bottom triangle

		// sort bottom vertices by x
		if (v_mid.pos_.x > v_bottom.pos_.x)
		{
			std::swap(v_mid, v_bottom);
		}
		RenderFlatBottomTriangle(v_top, v_mid, v_bottom, colour);
	}
	else
	{
		// generic case
		// split into a flat bottom and
		// flat top triangle for rendering

		const f32 split = (v_mid.pos_.y - v_top.pos_.y) / (v_bottom.pos_.y - v_top.pos_.y);
		const f32 v_x = v_top.pos_.x + (v_bottom.pos_.x - v_top.pos_.x) * split;
		const f32 v_y = v_top.pos_.y + (v_bottom.pos_.y - v_top.pos_.y) * split;
		Vertex v_split;
		v_split.pos_.x = v_x;
		v_split.pos_.y = v_y;
		if (v_mid.pos_.x < v_x)	// right handed
		{
			RenderFlatBottomTriangle(v_top, v_mid, v_split, colour);
			RenderFlatTopTriangle(v_mid, v_split, v_bottom, colour);
		}
		else				//  left handed
		{
			RenderFlatBottomTriangle(v_top, v_split, v_mid, colour);
			RenderFlatTopTriangle(v_split, v_mid, v_bottom, colour);
		}
	}

}

void FrameBuffer::DrawScanline(s32 y, s32 x_min, s32 x_max, u32 packed_RGBA)
{
	for (s32 i = x_min; i <= x_max; i++)
	{
		SetPixel(packed_RGBA, i, y);
	}
}

void FrameBuffer::RenderFlatTopTriangle(const Vertex & v_top, const Vertex & v_mid, const Vertex & v_bottom, u32 packed)
{
	// delta x / delta y between bottom and top 
	// vertices
	const f32 bottom_to_top_delta = (v_bottom.pos_.x - v_top.pos_.x) / (v_bottom.pos_.y - v_top.pos_.y);

	// delta x / delta y between bottom
	// and middle vertices
	const f32 bottom_to_middle_delta = (v_bottom.pos_.x - v_mid.pos_.x) / (v_bottom.pos_.y - v_mid.pos_.y);

	// calculate start and end of scanlines
	// 
	const u32 y_start = (u32)ceil(v_top.pos_.y - 0.5f);
	const u32 y_end = (u32)ceil(v_bottom.pos_.y - 0.5f);

	for (u32 y = y_start; y < y_end; y++)
	{
		// calculate start and end points (x-coordinates)
		// add 0.5 to y value because calculation is based on pixel
		// centres

		const f32 x_start_decimal = bottom_to_top_delta    * (f32(y) + 0.5f - v_top.pos_.y) + v_top.pos_.x;
		const f32 x_end_decimal = bottom_to_middle_delta * (f32(y) + 0.5f - v_mid.pos_.y) + v_mid.pos_.x;

		// calculate start and end pixels
		// only fill if the pixel centre is within the triangle
		const u32 x_start = (u32)ceil(x_start_decimal - 0.5f);
		const u32 x_end = (u32)ceil(x_end_decimal - 0.5f);

		// TODO: interpolate per vertex colours
		DrawScanline(y, x_start, x_end, packed);

	}
}
void FrameBuffer::RenderFlatBottomTriangle(const Vertex & v_top, const Vertex & v_mid, const Vertex & v_bottom,
	u32 packed)
{
	// delta x / delta y between mid and top 
	// vertices
	const f32 middle_to_top_delta = (v_mid.pos_.x - v_top.pos_.x) / (v_mid.pos_.y - v_top.pos_.y);
	// delta x / delta y between bottom and top
	// vertices
	const f32 bottom_to_top_delta = (v_bottom.pos_.x - v_top.pos_.x) / (v_bottom.pos_.y - v_top.pos_.y);


	const u32 y_start = (u32)ceil(v_top.pos_.y - 0.5f);
	const u32 y_end = (u32)ceil(v_bottom.pos_.y - 0.5f);

	for (u32 y = y_start; y < y_end; y++)
	{

		const f32 x_start_decimal = middle_to_top_delta * (f32(y) + 0.5f - v_top.pos_.y) + v_top.pos_.x;
		const f32 x_end_decimal = bottom_to_top_delta * (f32(y) + 0.5f - v_top.pos_.y) + v_top.pos_.x;

		// only fill if the pixel centre is within the triangle
		const u32 x_start = (u32)ceil(x_start_decimal - 0.5f);
		const u32 x_end = (u32)ceil(x_end_decimal - 0.5f);

		DrawScanline(y, x_start, x_end, packed);
	}
}

void ClearRange(u8 * start, u32 pixel_count, u32 colour)
{
	for (int i = 0; i < (s32)pixel_count; i++)
	{
		memcpy(start, &colour, 4);
		start += 4;
	}
}

void ClearRangeGreyscale(u8 * start, u32 pixel_count, u8 value)
{
	memset(start, value, pixel_count * 4);
}
