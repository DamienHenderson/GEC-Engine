#pragma once 

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <utility>
// useful for bit flags
#define BIT(n) 1 << n;

#include "Types.hpp"
template <typename T>
bool IsSafe(T* ptr)
{
	return ptr != nullptr;
}
template <typename T>
void SafeDelete(T* ptr)
{
	if(IsSafe(ptr))
	{
		delete ptr;
	}
}
template <typename T>
void SafeDeleteArray(T* ptr)
{
	if(IsSafe(ptr))
	{
		delete[] ptr;
	}
}

// sets a generic block of memory of len size in bytes to the value 0
void ZeroMem(void *ptr, u32 len);

u32 PackRGBA(u8 r, u8 g, u8 b, u8 a);

u32 PackRGBA(vec4 < u8 > colour);

vec4 < u8 > UnpackRGBA(u32 packed);
#endif