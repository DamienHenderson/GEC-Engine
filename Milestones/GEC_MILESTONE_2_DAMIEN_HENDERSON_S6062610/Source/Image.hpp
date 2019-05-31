#pragma once 

#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstring>
#include <fstream>

#include <HAPI_lib.h>

#include "Types.hpp"
#include "Utils.hpp"

class Image;
Image DefaultImage(u32 width, u32 height);

class Image
{
	public:
	
		Image() {}
	    Image(u8* pixels,u32 width,u32 height) : width_(width),height_(height)
	    {
	    	buffer_ = new u8[width * height * 4]();
	    	if (pixels != nullptr)
	    	{
	    	    memcpy (buffer_,pixels,width*height * 4);
	    	}
	    }
	    Image(const Image& other)
	    {
	    	width_  = other.width_;
	    	height_ = other.height_;
	    	
	    	buffer_ = new
	    	u8[other.width_*other.height_ * 4]();
	    	
	    	memcpy (buffer_,other.buffer_,
	    	other.width_ * other.height_ * 4);
	    }
	    
	    
		Image(const std::string& filename)
	    {
			if (!HAPI.LoadTexture(filename, &buffer_, (int&)width_, (int&)height_))
			{
				*this = DefaultImage(256, 256);
			}
	    }
	    
	    ~Image()
	    {
	    	SafeDeleteArray(buffer_);
	    }
		u32 GetPixel(u32 x, u32 y, bool wrap) const;
		void SetPixel(u32 packed, u32 x, u32 y);
		const u8* GetPixels() const;
	    
		bool LoadFromFile(const std::string& filename);
		void SaveToFile(const char* filename) const;
	    
		u32 GetWidth() const;
		u32 GetHeight() const;

		
	private:
        u8* buffer_;
        u32 width_,height_;
};



#endif