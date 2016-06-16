#ifndef ANIMATOR_H
#define ANIMATOR_H
#include "include.h"


class AnimatedObject;

class Animator 
{
public:
	Animator ();

	enum RepeatType
    {
        RT_CLAMP,
        RT_WRAP,
        RT_CYCLE
    };

	void SetObject (AnimatedObject* object);

	virtual bool Update (float appTime);
  
	RepeatType m_Repeat;
    double m_MinTime;     
    double m_MaxTime;    
    double m_Phase;       
    double m_Frequency;   
	bool m_Active;

protected:
	virtual ~Animator ();

	double GetControlTime(double appTime);

	AnimatedObject* m_Object;
	double m_AppTime;
};
#endif