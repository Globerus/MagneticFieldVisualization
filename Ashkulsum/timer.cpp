#include "stdafx.h"
#include "timer.h"
#include <Windows.h>
#include <cmath>

Timer::Timer ()
	:	m_Frequency (0),
		m_InverseFrequency (0),
		m_InitialTicks (0.0)
{
	LARGE_INTEGER counter = { 0 }, frequency = { 1 };
    QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter);
	m_InitialTicks = static_cast<int64_t>(counter.QuadPart);
    m_Frequency = static_cast<int64_t>(frequency.QuadPart);
	m_InverseFrequency = 1.0 / static_cast<double>(m_Frequency);
}


int64_t Timer::GetMilliseconds()
{
    int64_t ticks = GetTicks();
    double seconds = m_InverseFrequency * static_cast<double>(ticks);
    int64_t milliseconds = static_cast<int64_t>(ceil(1000.0 * seconds));
    return milliseconds;
}

double Timer::GetSeconds()
{
    int64_t ticks = GetTicks();
    double seconds = m_InverseFrequency * static_cast<double>(ticks);
    return seconds;
}

void Timer::Reset()
{
    LARGE_INTEGER counter = { 0 };
	QueryPerformanceCounter(&counter);
	m_InitialTicks = static_cast<int64_t>(counter.QuadPart);
}

int64_t Timer::GetTicks()
{
    LARGE_INTEGER counter = { 0 };
    QueryPerformanceCounter(&counter);
	return static_cast<int64_t>(counter.QuadPart) - m_InitialTicks;
}

