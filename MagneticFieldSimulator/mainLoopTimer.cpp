#include "stdafx.h"
#include "mainLoopTimer.h"
#include <Windows.h>
#include <cmath>

MainLoopTimer::MainLoopTimer (int64_t frequency)
	:	m_Frequency (frequency),
		m_InverseFrequency (0),
		m_InversePerformanceFrequency (0),
		m_InitialTicks (0)
{
	Reset ();
}

void MainLoopTimer::Reset()
{
    m_CallCount = m_Frequency;
    m_NumFrames = 0;
    m_AccumulatedNumFrames = 0;
    m_AccumulatedTime = 0;

	LARGE_INTEGER counter = { 0 }, frequency = { 1 };
	QueryPerformanceCounter(&counter);
    QueryPerformanceFrequency(&frequency);
	m_InitialTicks = static_cast<int64_t>(counter.QuadPart);
	m_InverseFrequency = 1.0 / static_cast<double>(m_Frequency);
	m_InversePerformanceFrequency = 1.0/static_cast<double>(frequency.QuadPart);

	m_Time0 = GetMilliseconds ();
	m_Time1 = m_Time0;
}

void MainLoopTimer::Measure()
{
    if (--m_CallCount == 0)
    {
		m_Time1 = GetMilliseconds ();
        int64_t delta = m_Time1 - m_Time0;
        m_Time0 = m_Time1;
        m_AccumulatedNumFrames += m_NumFrames;
        m_AccumulatedTime += delta;
        m_NumFrames = 0;
        m_CallCount = m_Frequency;
    }
}

double MainLoopTimer::GetSeconds()
{
    int64_t ticks = GetTicks();
	double seconds = m_InversePerformanceFrequency * static_cast<double>(ticks);
    return seconds;
}

int64_t MainLoopTimer::GetMilliseconds()
{
    int64_t ticks = GetTicks();
    double seconds = m_InverseFrequency * static_cast<double>(ticks);
    int64_t milliseconds = static_cast<int64_t>(ceil(1000.0 * seconds));
    return milliseconds;
}

double MainLoopTimer::GetFramesPerSecond() const
{
    if (m_AccumulatedTime > 0)
    {
        double numFrames = static_cast<double>(m_AccumulatedNumFrames);
        double numMilliseconds = static_cast<double>(m_AccumulatedTime);
        return 1000.0 * numFrames / numMilliseconds;
    }
    else
    {
        return 0.0;
    }
}

int64_t MainLoopTimer::GetTicks()
{
    LARGE_INTEGER counter = { 0 };
    QueryPerformanceCounter(&counter);
	return static_cast<int64_t>(counter.QuadPart) - m_InitialTicks;
}

std::string MainLoopTimer::GetSecondsString()
{
    std::ostringstream stream;
    stream.setf(std::ios::fixed | std::ios::showpoint);
    stream.precision(1);
    stream << "Elapsed time: " << GetSeconds() << " sec";
    return stream.str();
}

std::string MainLoopTimer::GetFPS () 
{
	std::ostringstream stream;
    stream.setf(std::ios::fixed | std::ios::showpoint);
    stream.precision(1);
    stream << "fps: " << GetFramesPerSecond();
    return stream.str();
}

void MainLoopTimer::UpdateNumFrames()
{
    ++m_NumFrames;
}