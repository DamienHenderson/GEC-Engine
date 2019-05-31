#pragma once

#include <chrono>

#include "Types.hpp"
#ifndef TIMER_HPP
#define TIMER_HPP

class Timer
{
public:
	Timer()
	{
		start_ = std::chrono::steady_clock::now();
	}
	~Timer()
	{
	}
	// Get Elapsed time in microseconds
	u64 GetElapsed();
private:
	std::chrono::steady_clock::time_point start_;

};
#endif