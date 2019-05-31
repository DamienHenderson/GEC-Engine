#pragma once

#include <stdio.h>
#include <cmath>
#include <limits>
#include <vector>

#include <algorithm>
#include <future>
#include <thread>

#include <HAPI_lib.h>

#include "Types.hpp"
#include "Utils.hpp"
#include "PoolAllocator.hpp"


#ifndef FRAMEBUFFER_HPP
#define FRAMEBUFFER_HPP

void ClearRange(u8* start, u32 pixel_count, u32 colour);
void ClearRangeGreyscale(u8* start, u32 pixel_count, u8 value);

class FrameBuffer
{
public:

	FrameBuffer() {}
	// Creates an RGBA 32bpp FrameBuffer of size width * height pixels
	// This FrameBuffer will be initialised to all zeroes 
	FrameBuffer(s32 width, s32 height) : width_(width), height_(height)
	{
		// buffer_ = new u8[width * height * 4]();
		buffer_ = g_allocator.Allocate<u8>(width * height * 4, "Framebuffer");
		
		
		
		DEBUG_ONLY(std::cerr << std::hex << (void*)buffer_ << std::dec << "\n";);
		assert(buffer_ != nullptr);

		// ZeroMem(stencil_, width * height);

	

	}
	void Initialise(s32 width, s32 height)
	{
		// deallocate buffers just in case this was called on an already initialised framebuffer
		g_allocator.Deallocate(&buffer_);
		

		width_ = width;
		height_ = height;
		// buffer_ = new u8[width * height * 4]();
		buffer_ = g_allocator.Allocate<u8>(width * height * 4, "Framebuffer");

		assert(buffer_ != nullptr);


		
	}
	FrameBuffer(const FrameBuffer& other)
	{
		buffer_ = g_allocator.Allocate<u8>(other.width_ * other.height_ * 4, "Framebuffer");
		
		width_ = other.width_;
		height_ = other.height_;
		memcpy(buffer_, other.buffer_, other.width_ * other.height_ * 4);
	}
	~FrameBuffer()
	{
		g_allocator.Deallocate(&buffer_);
		


		// SafeDeleteArray(buffer_);
		// SafeDeleteArray(depth_);
		// SafeDeleteArray(stencil_);
	}
	void Clear(u32 packed)
	{

		u32* pix = (u32*)buffer_;
		for (s32 i = 0; i < width_ * height_; i++)
		{
			
			// pix[i] = packed;
			// seems to be slightly faster
			pix += 1;
		 	memcpy(pix, &packed, 4);
		}
		



		
	}
	void ClearThreaded(u32 colour)
	{
		const int thread_count = 4;

		std::future<void> threads[thread_count];

		u32 pixels_per_thread = (width_ * height_) / (thread_count - 1);

		for (int i = 0; i < thread_count - 1; i++)
		{
			u8* ptr = buffer_ + (i * pixels_per_thread) * 4;
			threads[i] = std::async(std::launch::async, ClearRange, ptr, pixels_per_thread, colour);
		}
		u32 leftover_pixels = (width_ * height_) % ((thread_count - 1) * pixels_per_thread);
		threads[thread_count - 1] = std::async(std::launch::async, ClearRange, buffer_ + (pixels_per_thread * (thread_count - 1)), leftover_pixels, colour);

		for (int i = 0; i < thread_count; i++)
		{
			threads[i].get();
		}
	}
	void ClearGreyscaleThreaded(u8 colour)
	{
		const int thread_count = 4;

		std::future<void> threads[thread_count];

		u32 pixels_per_thread = (width_ * height_) / (thread_count - 1);

		for (int i = 0; i < thread_count - 1; i++)
		{
			u8* ptr = buffer_ + (i * pixels_per_thread) * 4;
			threads[i] = std::async(std::launch::async, ClearRangeGreyscale, ptr, pixels_per_thread, colour);
		}
		u32 leftover_pixels = (width_ * height_) % ((thread_count - 1) * pixels_per_thread);
		threads[thread_count - 1] = std::async(std::launch::async, ClearRangeGreyscale, buffer_ + (pixels_per_thread * (thread_count - 1)), leftover_pixels, colour);

		for (int i = 0; i < thread_count; i++)
		{
			threads[i].get();
		}
	}
	void ClearGreyscale(u8 greyscale)
	{
		 memset(buffer_, greyscale, width_ * height_ * 4);
		
		
	}
	void Clear(const FrameBuffer & other)
	{
		memcpy(buffer_, other.buffer_, other.width_ * other.height_ * 4);
		// memcpy(depth_, other.depth_, other.width_ * other.height_ * sizeof(f32));

		
		
	}

	void SetPixel(u32 packed, s32 x, s32 y)
	{
		if (x >= width_ || y >= height_)
		{
			return;
		}

		u32 idx = (x + (y * width_));
		
		u32 *ptr = (u32 *)buffer_;
		// DEBUG_ONLY( std::cout <<  "set pixel at: (" << x << "," << y << ")\n";
		ptr[idx] = packed;
		
		// memset(&(ptr[idx]),packed,sizeof(u32));
	}
	void SetPixel(u32 packed, s32 x, s32 y, f32 z)
	{
		if (x >= width_ || y >= height_ || x < 0 || y < 0)
		{
			return;
		}

		
		u32 idx = (x + (y * width_));
		
		
		u32 *ptr = (u32 *)buffer_;
		
		
		ptr[idx] = packed;
		
		// memset(&(ptr[idx]),packed,sizeof(u32));
	}
	rect<s32> GetRect() const
	{
		return rect<s32>(width_, height_);
	}
	// returns the packed RGBA value of a pixel at (x,y)
	u32 GetPixel(s32 x, s32 y)
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
	void RenderStar(f32 x, f32 y, f32 z, u32 packed,f32 eye_dist, s32 centre_x, s32 centre_y);

	s32 GetWidth() const { return width_; }
	s32 GetHeight() const { return height_; }
	void RenderTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, u32 colour);


	void DrawScanline(s32 y, s32 x_min, s32 x_max, u32 packed_RGBA);

private:

	void RenderFlatTopTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, u32 packed);
	void RenderFlatBottomTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3,
		u32 packed);

	

	// pixel buffer containing colours for each pixel in RGBA 32 bpp format
	u8 *buffer_ = nullptr;
	
	s32 width_, height_;


	



};

#endif