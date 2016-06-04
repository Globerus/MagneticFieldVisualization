#include "stdafx.h"
#include "timer.h"
#include <Windows.h>
#include <cmath>

Timer::Timer (int64_t frequency)
	:	m_Frequency (frequency > 0 ? frequency : 1)
{
	 Reset();
}


int64_t Timer::GetMilliseconds()
{
    int64_t ticks = GetTicks();
    double seconds = (1.0 / m_PerformanceFrequency) * static_cast<double>(ticks);
    int64_t milliseconds = static_cast<int64_t>(ceil(1000.0 * seconds));
    return milliseconds;
}

void Timer::Reset()
{
    LARGE_INTEGER counter = { 0 }, frequency = { 1 };
    QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&counter);
    m_PerformanceFrequency = static_cast<int64_t>(frequency.QuadPart);  
    m_Time0 = static_cast<int64_t>(counter.QuadPart);
	m_Time1 = m_Time0;
	m_CallCount = m_Frequency;
    m_FrameCount = 0;
    m_AccumulatedFrameCount = 0;
    m_AccumulatedTime = 0;
}

void Timer::Measure()
{
    if (--m_CallCount == 0)
    {
        int64_t delta = GetMilliseconds();
        m_Time0 = m_Time1;
        m_AccumulatedFrameCount += m_FrameCount;
        m_AccumulatedTime += delta;
        m_FrameCount = 0;
        m_CallCount = m_Frequency;
    }
}
int64_t Timer::GetTicks()
{
    LARGE_INTEGER counter = { 0 };
    QueryPerformanceCounter(&counter);
	m_Time1 = static_cast<int64_t>(counter.QuadPart);
    return m_Time1 - m_Time0;
}


double Timer::GetFramesPerSecond() const
{
    if (m_AccumulatedTime > 0)
    {
        double numFrames = static_cast<double>(m_AccumulatedFrameCount);
        double numMilliseconds = static_cast<double>(m_AccumulatedTime);
        return 1000.0 * numFrames / numMilliseconds;
    }
    else
    {
        return 0.0;
    }
}

double Timer::GetSecondsPerFrame() const
{
    if (m_AccumulatedFrameCount > 0)
    {
        double numFrames = static_cast<double>(m_AccumulatedFrameCount);
        double numMilliseconds = static_cast<double>(m_AccumulatedTime);
        return 1000.0 * numMilliseconds / numFrames;
    }
    else
    {
        return 0.0;
    }
}

int64_t Timer::GetMillisecondsPerFrame() const
{
    if (m_AccumulatedFrameCount > 0)
    {
        double numFrames = static_cast<double>(m_AccumulatedFrameCount);
        double numMilliseconds = static_cast<double>(m_AccumulatedTime);
        double rate = numMilliseconds / numFrames;
        return static_cast<int64_t>(floor(rate + 0.5));
    }
    else
    {
        return 0;
    }
}