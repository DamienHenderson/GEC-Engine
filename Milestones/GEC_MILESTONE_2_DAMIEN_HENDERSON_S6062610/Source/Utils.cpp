#include "Utils.hpp"

void ZeroMem(void *ptr, u32 len)
{
	memset(ptr, 0, len);
}

u32 PackRGBA(u8 r, u8 g, u8 b, u8 a)
{
	// benchmark this to see if the memcpy version is faster than the bitshift 
	// and OR version
	u32 colour{ 0 };
	//u8 col_ptr[4];				// = new u8[4]();
	//col_ptr[0] = r;
	//col_ptr[1] = g;
	//col_ptr[2] = b;
	// col_ptr[3] = a;
	// memcpy(&colour, col_ptr, sizeof(u32));
	colour |= (u32)(r);
	colour |= (u32)(g << 8);
	colour |= (u32)(b << 16);
	colour |= (u32)(a << 24);
	// delete[] col_ptr;
	return colour;
}

u32 PackRGBA(vec4 < u8 > colour)
{
	return PackRGBA(colour.r, colour.g, colour.b, colour.a);
}

vec4 < u8 > UnpackRGBA(u32 packed)
{
	vec4 < u8 > col{ 0,0,0,0 };
	// memcpy(&col, &packed, sizeof(u32));
	col.r = (packed >> 24);
	col.g = (packed >> 16);
	col.b = (packed >> 8);
	col.a = (u8)packed;
	return col;
}