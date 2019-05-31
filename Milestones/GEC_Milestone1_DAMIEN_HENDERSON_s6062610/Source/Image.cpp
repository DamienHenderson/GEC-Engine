#include "Image.hpp"

u32 Image::GetPixel(u32 x, u32 y, bool wrap) const
{
	u32 x_wrap = x, y_wrap = y;
	if ((x >= width_ || y >= height_) && wrap)
	{
		// wrap texture here?
		x_wrap = x % width_;
		y_wrap = y % height_;

	}

	
	u32 idx = (x_wrap + (y_wrap * width_));

	u32* buff = (u32*)buffer_;
	return buff[idx];
}

void Image::SetPixel(u32 packed, u32 x, u32 y)
{
	if (x > width_ || y > height_)
	{
		return;
	}
	u32 idx = (x + (y * width_));

	u32* buff = (u32*)buffer_;

	buff[idx] = packed;
}

const u8* Image::GetPixels() const
{
	return buffer_;
}

void Image::LoadFromFile(const char* filename)
{
	SafeDeleteArray(buffer_);
	HAPI.LoadTexture(filename, &buffer_, (int&)width_, (int&)height_);
}

void Image::SaveToFile(const char* filename) const
{
	HAPI.SaveImage(buffer_, width_, height_, filename);
}

u32 Image::GetWidth() const
{
	return width_;
}
u32 Image::GetHeight() const
{
	return height_;
}

Image DefaultImage(u32 width, u32 height)
{
	u8* buff = new u8[width * height * 4]();
	for (u32 i = 0; i < width * height * 4; i += 4)
	{
		buff[i] = 255;
		buff[i + 1] = 20;
		buff[i + 2] = 147;
		buff[i + 3] = 255;
	}
	
	Image img(buff, width, height);
	SafeDeleteArray(buff);
	return img;


}