#ifndef MAIN_LOOP_TIMER_H
#define MAIN_LOOP_TIMER_H

#include <cstdint>
#include <sstream>

class MainLoopTimer 
{
public:
	MainLoopTimer (int64_t frequency = 30);

	void Reset ();
   
	void Measure ();

	int64_t GetMilliseconds();
	double GetSeconds();
	std::string GetSecondsString();

	double GetFramesPerSecond() const;

	std::string GetFPS ();

	void UpdateNumFrames();

private:
	int64_t GetTicks();

	int64_t m_CallCount;
	int64_t m_NumFrames;
	int64_t m_AccumulatedNumFrames;
	int64_t m_AccumulatedTime;
	int64_t m_Frequency;
	double m_InverseFrequency;
	double m_InversePerformanceFrequency;
	int64_t m_InitialTicks;
	int64_t m_Time0, m_Time1;
};
#endif