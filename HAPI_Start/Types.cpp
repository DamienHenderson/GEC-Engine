#include "Types.hpp"

size_t terrible_hash(size_t value)
{
	value = ((value >> 16) ^ value) * hash_constant;
	value = ((value >> 16) ^ value) * hash_constant;
	value = (value >> 16) ^ value;
	return value;
}