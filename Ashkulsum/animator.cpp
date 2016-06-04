#include "stdafx.h"
#include "animator.h"
#include "animatedObject.h"

Animator::~Animator ()
{

}

Animator::Animator ()
	:	m_AppTime(0.0),
		m_Repeat (RT_CLAMP),
		m_Phase (0.0),
		m_Frequency (1.0),
		m_MinTime (0.0),
		m_MaxTime (0.0),
		m_Object (nullptr),
		m_Active (true)
{
	
}

void Animator::SetObject (AnimatedObject* object)
{
	m_Object = object;
}

bool Animator::Update (float appTime)
{
	if (m_Active)
	{
		m_AppTime = appTime;
		return true;
	}

	return false;
}

double Animator::GetControlTime(double appTime)
{
    double controlTime = m_Frequency * appTime + m_Phase;

    if (m_Repeat == RT_CLAMP)
    {
        // Clamp the time to the [min,max] interval.
        if (controlTime < m_MinTime)
        {
            return m_MinTime;
        }
        if (controlTime > m_MaxTime)
        {
            return m_MaxTime;
        }
        return controlTime;
    }

    double timeRange = m_MaxTime - m_MinTime;
    if (timeRange > 0.0)
    {
        double multiples = (controlTime - m_MinTime) / timeRange;
        double integerTime = floor(multiples);
        double fractionTime = multiples - integerTime;
        if (m_Repeat == RT_WRAP)
        {
            return m_MinTime + fractionTime*timeRange;
        }

        // repeat == RT_CYCLE
        if (static_cast<int>(integerTime) & 1)
        {
            // Go backward in time.
            return m_MaxTime - fractionTime * timeRange;
        }
        else
        {
            // Go forward in time.
            return m_MinTime + fractionTime * timeRange;
        }
    }

    // The minimum and maximum times are the same, so return the minimum.
    return m_MinTime;
}