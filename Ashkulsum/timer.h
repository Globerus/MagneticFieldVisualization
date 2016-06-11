#ifndef TIMER_H
#define TIMER_H

#include <cstdint>

class Timer
{
public:
	Timer ();

	void Reset();
   
	int64_t GetMilliseconds();
	double GetSeconds();

private:
	int64_t GetTicks();

	int64_t m_Frequency;
	double m_InverseFrequency;
	int64_t m_InitialTicks;
};

#endif