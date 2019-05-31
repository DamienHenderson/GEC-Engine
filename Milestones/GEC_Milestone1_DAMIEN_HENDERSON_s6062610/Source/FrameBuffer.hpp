#pragma once

#include <stdio.h>
#include <cmath>
#include <limits>
#include <vector>

#include <HAPI_lib.h>

#include "Types.hpp"
#include "Utils.hpp"


#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

constexpr u32 cell_width  = 128;
constexpr u32 cell_height = 128;
struct FrameBufferCell
{
	FrameBufferCell(vec2<u32> start = { 0, 0 }, vec2<u32> end = {cell_width, cell_height}) : start_(start), end_(end)
	{

	}

	vec2<u32> start_, end_;
	bool is_dirty{ true };
};
class FrameBuffer
{
public:

	
	// Creates an RGBA 32bpp FrameBuffer of size width * height pixels
	// This FrameBuffer will be initialised to all zeroes 
	FrameBuffer(u32 width, u32 height) : width_(width), height_(height)
	{
		buffer_ = new u8[width * height * 4]();
		depth_ = new f32[width * height]();
		stencil_ = new u8[width * height]();
		ZeroMem(buffer_, width * height * 4);

		static constexpr f32 inf = std::numeric_limits<f32>::infinity();
		for (u32 i = 0; i < width_ * height_; i++)
		{
			depth_[i] = inf;
		}

		ZeroMem(stencil_, width * height);

		// populate cells

		fb_cells.resize(ceil(width_ / cell_width));
		for (u32 i = 0; i < ceil(width_ / cell_width ); i++)
		{
			fb_cells[i].resize(height_ / cell_height);
		}

		for (u32 j = 0; j < ceil(height_ / cell_height); j++)
		{
			for (u32 i = 0; i < ceil(width_ / cell_width); i++)
			{
				vec2<u32> top_left = { i * cell_width, j * cell_height };
				vec2<u32> bottom_right = { (i + 1) * cell_width, (j + 1) * cell_height };
				if (bottom_right.x > width_)
				{
					bottom_right.x = width;
				}
				if (bottom_right.y > height_)
				{
					bottom_right.y = height_;
				}
				fb_cells[i][j] = { top_left, bottom_right };
				std::cout << "Created FrameBuffer Cell at: " << i << " , " << j << "\n";
			}
		}

	}
	FrameBuffer(const FrameBuffer& other)
	{
		buffer_ = new u8[other.width_ * other.height_ * 4]();
		width_ = other.width_;
		height_ = other.height_;
		memcpy(buffer_, other.buffer_, other.width_ * other.height_ * 4);
	}
	~FrameBuffer()
	{
		SafeDeleteArray(buffer_);
		SafeDeleteArray(depth_);
		SafeDeleteArray(stencil_);
	}
	void Clear(u32 packed)
	{

		u32* pix = (u32*)buffer_;
		for (u32 i = 0; i < width_ * height_; i++)
		{
			
			// pix[i] = packed;
			// seems to be slightly faster
			pix += 1;
		 	memcpy(pix, &packed, 4);
		}
		/*
		for (auto& cell_row : fb_cells)
		{
		for (auto& cell : cell_row)
		{
		if (cell.is_dirty)
		{
		for (u32 y = cell.start_.y; y < cell.end_.y; y++)
		{
		for (u32 x = cell.start_.x; y < cell.end_.x; x++)
		{
		SetPixel(packed, x, y);
		}
		}
		cell.is_dirty = false;
		}

		}
		}
		*/



		f32 inf = std::numeric_limits<f32>::infinity();
		for (u32 i = 0; i < width_ * height_; i++)
		{
			depth_[i] = inf;
		}
		ZeroMem(stencil_, width_ * height_);
	}
	void ClearGreyscale(u8 greyscale)
	{
		memset(buffer_, greyscale, width_ * height_ * 4);
		ZeroMem(stencil_, width_ * height_);
		f32 inf = std::numeric_limits<f32>::infinity();
		for (u32 i = 0; i < width_ * height_; i++)
		{
			depth_[i] = inf;
		}
	}
	void Clear(const FrameBuffer & other)
	{
		memcpy(buffer_, other.buffer_, other.width_ * other.height_ * 4);
		// memcpy(depth_, other.depth_, other.width_ * other.height_ * sizeof(f32));

		ZeroMem(stencil_, width_ * height_);
		f32 inf = std::numeric_limits<f32>::infinity();
		for (u32 i = 0; i < width_ * height_; i++)
		{
			depth_[i] = inf;
		}
	}

	void SetPixel(u32 packed, u32 x, u32 y)
	{
		if (x >= width_ || y >= height_)
		{
			return;
		}

		u32 idx = (x + (y * width_));
		if (stencil_[idx])
		{
			return;
		}
		u32 *ptr = (u32 *)buffer_;
		// std::cout << "set pixel at: (" << x << "," << y << ")\n";
		ptr[idx] = packed;
		stencil_[idx]++;
		// memset(&(ptr[idx]),packed,sizeof(u32));
	}
	void SetPixel(u32 packed, u32 x, u32 y, f32 z)
	{
		if (x >= width_ || y >= height_ || x < 0 || y < 0)
		{
			return;
		}

		
		u32 idx = (x + (y * width_));
		
		 if (z >= depth_[idx])
		 {
		 	return;
		 }
		
		u32 *ptr = (u32 *)buffer_;
		// std::cout << "set pixel at: (" << x << "," << y << ")\n";
		
		 if (stencil_[idx])
		 {
		 	return;
		 }
		
		ptr[idx] = packed;
		stencil_[idx]++;
		depth_[idx] = z;
		// memset(&(ptr[idx]),packed,sizeof(u32));
	}
	// returns the packed RGBA value of a pixel at (x,y)
	u32 GetPixel(u32 x, u32 y)
	{
		u32 idx = (x + (y * width_));
		u32 *ptr = (u32 *)buffer_;
		return ptr[idx];
	}

	const u8 *GetPixels() const
	{
		return buffer_;
	}
	u8* GetPixelsUnsafe()
	{
		return buffer_;
	}
	
	void RenderStar(f32 x, f32 y, f32 z, u32 packed, f32 eye_dist);
	void RenderStar(f32 x, f32 y, f32 z, u32 packed,f32 eye_dist, u32 centre_x, u32 centre_y);

	u32 GetWidth() const { return width_; }
	u32 GetHeight() const { return height_; }
	void RenderTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, u32 colour);


	void DrawScanline(u32 y, u32 x_min, u32 x_max, u32 packed_RGBA);

private:

	void RenderFlatTopTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, u32 packed);
	void RenderFlatBottomTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3,
		u32 packed);


	// pixel buffer containing colours for each pixel in RGBA 32 bpp format
	u8 *buffer_ = nullptr;
	// stores the z value for a pixel to allow depth testing to prevent
	// overdraw
	// depth buffers also known as z buffers are generally used for 3D but can 
	// also be useful for 2D
	// zeroed out on clear
	f32 *depth_ = nullptr;
	// stores the number of write operations that have been done on a pixel
	// since the last clear up to 255
	// useful for profiling overdraw
	// could be expanded to 16 bits to allow for 
	// tracking of 65535 write operations
	u8 *stencil_ = nullptr;
	u32 width_, height_;


	std::vector<std::vector<FrameBufferCell>> fb_cells;



};

#endif