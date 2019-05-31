#pragma once 

#ifndef UTILS_HPP
#define UTILS_HPP

#include <cstring>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <utility>
// useful for bit flags
// endianness?
#define BIT(n) 1 << n;

// TODO: replace all instances of std::cout and std::cerr with DEBUG_LOG and DEBUG_ERROR
// could i also add log and error which work in release as well?
#if defined(_DEBUG) | defined(DEBUG)
	#define DEBUG_ONLY(x) do { x } while(false)
	#define DEBUG_LOG(x) DEBUG_ONLY(std::cout << x << "\n";)
	#define DEBUG_ERROR(x) DEBUG_ONLY(std::cerr << x << "\n";)
#else 
	#define DEBUG_ONLY(x) do { } while(false)
	#define DEBUG_LOG(x) DEBUG_ONLY(x)
	#define DEBUG_ERROR(x) DEBUG_ONLY(x) 
#endif



#include "Types.hpp"


class TileMap;


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

template <typename T>
T Clamp(T lower, T upper, T value);

// sets a generic block of memory of len size in bytes to the value 0
void ZeroMem(void *ptr, u32 len);

u32 PackRGBA(u8 r, u8 g, u8 b, u8 a);

u32 PackRGBA(vec4 < u8 > colour);

vec4 < u8 > UnpackRGBA(u32 packed);

 // no templating because this should work on integers only
s32 ManhattanDist(vec2<s32> v1, vec2<s32> v2);

s32 AStarWeight(vec2<s32> v1, vec2<s32> v2, TileMap& tile_map);

// checks if a number is within a range around the value provided
bool IsWithin(float target, float variance, float val);
#endif

template<typename T>
inline T Clamp(T lower, T upper, T value)
{
	return std::min(upper,std::max(lower,value));
}
