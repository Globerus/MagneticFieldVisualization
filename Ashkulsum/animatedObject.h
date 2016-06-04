#ifndef ANIMATED_OBJECT_H
#define ANIMATED_OBJECT_H

#include "animator.h"
#include "include.h"
#include <list>

class AnimatedObject 
{
public:	
	AnimatedObject ();
	void AttachAnimator ( std::shared_ptr<Animator> animator);

	bool UpdateAnimators (float appTime);
protected:
	~AnimatedObject ();
	std::list<std::shared_ptr<Animator>> m_AnimatorList;
};
#endif