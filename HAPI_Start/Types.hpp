#pragma once


#include <cstdint>
#include <iostream>
#include <functional>
#include <cassert>

#ifndef TYPES_HPP
#define TYPES_HPP
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

using s8 = int8_t;
using s16 = int16_t;
using s32 = int32_t;
using s64 = int64_t;

using f32 = float;
using f64 = double;




constexpr size_t hash_constant{ 0x45d9f3b };


size_t terrible_hash(size_t value);


template < typename T > struct vec4
{
	union
	{
		struct
		{
			T x, y, z, w;
		};
		struct
		{
			T r, g, b, a;
		};
		T v_[4];

	};
	vec4 < T >(T x_in, T y_in, T z_in, T w_in) : x(x_in), y(y_in), z(z_in), w(w_in)
	{

	}
	bool operator<(const vec4 < T > &other)
	{
		return (x < other.x && y < other.y && z < other.z && w < other.w);
	}
	bool operator==(const vec4 < T > &other)
	{
		return (x == other.x && y == other.y && z == other.z && w == other.w);
	}
	bool operator<=(const vec4 < T > other)
	{
		return ((*this) < other || (*this) == other);
	}
	vec4 < T > &operator+(const vec4 < T > &other)
	{
		vec4 < T > res
		{
		x, y, z, w };
		res.x = x + other.x;
		res.y = y + other.y;
		res.z = z + other.z;
		res.w = w + other.w;

		return res;
	}
	vec4 < T > &operator+=(const vec4 < T > &other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	vec4 < T > &operator*(const T & scalar)
	{
		vec4 < T > res
		{
		x, y, z, w };
		res.x = x * scalar;
		res.y = y * scalar;
		res.z = z * scalar;
		res.w = w * scalar;

		return res;
	}
	vec4 < T > &operator*=(const T & scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return (*this);
	}

	vec4 < T > &operator-(const vec4 < T > &other)
	{
		vec4 < T > res
		{
		x, y, z, w };
		res.x = x - other.x;
		res.y = y - other.y;
		res.z = z - other.z;
		res.w = w - other.w;
		return res;

	}
	vec4 < T > &operator-=(const vec4 < T > &other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	vec4 < T > &operator /(const T & scalar)
	{
		vec4 < T > res
		{
		x, y, z, w };
		res.x = x / scalar;
		res.y = y / scalar;
		res.z = z / scalar;
		res.w = w / scalar;
		return res;
	}
	vec4 < T > &operator/=(const T & scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}

	void PerspectiveDivide()
	{
		if (w == 0)
		{
			return;
		}
		x /= w;
		y /= w;
		z /= w;
		w /= w;
	}

	T Length()
	{
		return sqrt((x * x) + (y * y) + (z * z) + (w * w));
	}
	void Normalise()
	{
		T l = Length();
		x /= l;
		y /= l;
		z /= l;
		w /= l;
	}

	T Dot(const vec4 < T > &other)
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}


};

struct Vertex
{
	vec4 < f32 > pos_;
	Vertex(const vec4 < f32 > &pos) :pos_(pos)
	{
	}
	Vertex(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 1.0f) :pos_(vec4 < f32 >
		(x, y, z, w))
	{
	}
	bool operator<(const Vertex & other)
	{
		return pos_ < other.pos_;
	}

	f32 TriangleArea(const Vertex & b, const Vertex c)
	{
		f32 x1 = b.pos_.x - pos_.x;
		f32 y1 = b.pos_.y - pos_.y;

		f32 x2 = c.pos_.x - pos_.x;
		f32 y2 = c.pos_.y - pos_.y;

		return (((x1 * y2) - (x2 * y1)) / 2.0f);
	}

	void PerspectiveDivide()
	{
		pos_.PerspectiveDivide();
	}
};

template < typename T > struct vec2
{
	T x, y;

	f32 TriangleArea(vec2 < T > b, vec2 < T > c)
	{
		T x1 = b.x - x;
		T y1 = b.y - y;

		T x2 = c.x - x;
		T y2 = c.y - y;

		return ((x1 * y2 - x2 * y1) / 2.0f);
	}

	vec2<T> operator +(const vec2<T>& other)
	{
		vec2<f32> out;
		out.x = x + other.x;
		out.y = y + other.y;
		return out;
	}

	vec2<T>& operator +=(const vec2<T>& other)
	{
		*this = *this + other;
		return *this;
	}

	vec2<T> operator -(const vec2<T>& other)
	{
		vec2<f32> out;
		out.x = x - other.x;
		out.y = y - other.y;
		return out;
	}
	vec2<T>& operator -=(const vec2<T>& other)
	{
		*this = *this - other;
		return *this;
	}

	vec2<T> operator *(T scalar)
	{
		vec2<f32> out;
		out.x = x * scalar;
		out.y = y * scalar;
		return out;
	}

	vec2<T>& operator *=(const T scalar)
	{
		*this = *this * scalar;
		return *this;
	}

	bool operator == (const vec2<T>& other) const
	{
		return x == other.x && y == other.y;
	}

	bool operator != (const vec2<T>& other) const
	{
		return !(*this == other);
	}

	T Length()
	{
		return sqrt((x * x) + (y * y));
	}

	void Unit()
	{
		T len = Length();

		assert(len != T(0));

		x /= len;
		y /= len;
	}
	template <typename U> operator vec2<U>()
	{
		return vec2<U> {static_cast<U>(x), static_cast<U>(x)};
	}
	friend std::ostream& operator <<(std::ostream& os, const vec2<T>& vec)
	{
		os << vec.x << " " << vec.y;
		return os;
	}

	
};

template <typename T>
struct vec2_hash
{
	std::size_t operator()(vec2<T> const& v) const noexcept
	{
		size_t h1 = terrible_hash((size_t)v.x);
		size_t h2 = terrible_hash((size_t)v.y);
		return h1 ^ (h2 << 1);
	}
};

template < typename T > struct rect
{
	T top, left, bottom, right;
	rect(T t, T l, T b, T r) : top(t), left(l), bottom(b), right(r)
	{

	}
	/// Creates a rect with top left 0,0 and bottom right w,h
	rect(T w, T h) : top(0), left(0), bottom(h), right(w)
	{

	}
	void ClipTo(const rect<T>& other)
	{
		top = std::max(top, other.top);
		bottom = std::max(0, std::min(bottom, other.bottom));
		left = std::max(left, other.left);
		right = std::max(0, std::min(right, other.right));
	}
	/// checks if this rect is completely outside another rect
	bool IsOutside(const rect<T>& other) const
	{
		return (left > other.right || top > other.bottom || bottom < other.top || right < other.left);
	}
	T GetWidth() const
	{
		return right - left;
	}
	T GetHeight() const
	{
		return bottom - top;
	}

	void Translate(T x, T y)
	{
		left += x;
		right += x;
		top += y;
		bottom += y;
	}
	bool Contains(const vec2<T>& point)
	{
		return point.x >= left && point.x <= right && point.y >= top && point.y <= bottom;
	}
	void ClampPositive()
	{
		// negative numbers completely break sprite rendering so stop at nothing to avoid them
		left = std::max(left, 0);
		right = std::max(right, 0);
		top = std::max(top, 0);
		bottom = std::max(bottom, 0);

	}
};



#endif