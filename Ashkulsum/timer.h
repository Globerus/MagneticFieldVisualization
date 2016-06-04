#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

class Timer
{
public:
	Timer (int64_t frequency = 30);

    int64_t GetMilliseconds();

	void Reset();
	void Measure();

	inline void UpdateFrameCount();

    // Report the rates.
    double GetFramesPerSecond() const;
    double GetSecondsPerFrame() const;
    int64_t GetMillisecondsPerFrame() const;

private:
	int64_t GetTicks();

	int64_t m_Frequency, m_CallCount, m_PerformanceFrequency;
	int64_t m_FrameCount, m_AccumulatedFrameCount, m_AccumulatedTime;
	int64_t m_Time0, m_Time1;
};

void Timer::UpdateFrameCount ()
{
    ++m_FrameCount;
}

#endif