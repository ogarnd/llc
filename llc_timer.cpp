#include "llc_timer.h"

#ifdef LLC_WINDOWS
#	include <Windows.h>
#elif defined(LLC_ARDUINO)
#	include <Arduino.h>
#elif defined(LLC_CMSIS)
#endif

stacxpr	double			MICROSECOND_SCALE		= 0.000001;

void					llc::STimer::Reset		()				noexcept				{
	LastTimeSeconds			= double(LastTimeMicroseconds = 0);
#if defined(LLC_WINDOWS) || defined(LLC_CMSIS) 
#	ifdef LLC_WINDOWS
	QueryPerformanceFrequency((::LARGE_INTEGER*)&CountsPerSecond);
	QueryPerformanceCounter((::LARGE_INTEGER*)&PrevTimeStamp);
#	elif defined(LLC_CMSIS)
	CountsPerSecond			= osKernelGetTickFreq();
	PrevTimeStamp			= osKernelGetTickCount();
#	endif
	SecondsPerCount			= 1.0 / CountsPerSecond;
	MicrosecondsPerCount	= 1.0 / (CountsPerSecond * MICROSECOND_SCALE);
#else
#	ifdef LLC_ARDUINO
	PrevTimeStamp			= micros();
#	else
	PrevTimeStamp			= ::std::chrono::high_resolution_clock::now();
#	endif
#endif
}

double			llc::STimer::Frame		()				noexcept				{
#if defined(LLC_WINDOWS) || defined(LLC_CMSIS) 
#	ifdef LLC_WINDOWS
	int64_t				currentTimeStamp		= 0;
	QueryPerformanceCounter((::LARGE_INTEGER*)&currentTimeStamp);
#	elif defined(LLC_CMSIS)
	int64_t				currentTimeStamp		= osKernelGetTickCount();
#	endif
	LastTimeSeconds			= (currentTimeStamp - PrevTimeStamp) * SecondsPerCount;
	LastTimeMicroseconds	= uint64_t((currentTimeStamp - PrevTimeStamp) * MicrosecondsPerCount);
	PrevTimeStamp			= currentTimeStamp;
	return LastTimeSeconds;
#else
#	ifdef LLC_ARDUINO
	int64_t		currentTimeStamp	= (int64_t)micros();
	LastTimeMicroseconds	= currentTimeStamp - PrevTimeStamp;
#	else
	auto		currentTimeStamp		= ::std::chrono::high_resolution_clock::now();
	LastTimeMicroseconds	= (int64_t)::std::chrono::duration_cast<std::chrono::microseconds>(currentTimeStamp - PrevTimeStamp).count();
#	endif
	PrevTimeStamp			= currentTimeStamp;
	return LastTimeSeconds	= LastTimeMicroseconds * MICROSECOND_SCALE;
#endif
}
