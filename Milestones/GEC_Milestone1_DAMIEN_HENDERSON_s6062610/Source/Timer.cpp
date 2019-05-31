#include "Timer.hpp"

u64 Timer::GetElapsed()
{
	return std::chrono::duration_cast < std::chrono::microseconds >
		(std::chrono::steady_clock::now() - start_).count();
}