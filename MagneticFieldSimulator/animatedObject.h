#ifndef ANIMATED_OBJECT_H
#define ANIMATED_OBJECT_H

#include "animator.h"
#include "include.h"
#include <list>

class AnimatedObject 
{
public:	
	AnimatedObject ();

	typedef std::list<std::shared_ptr<Animator>> List;
    
	List const& GetAnimatorList() const;
	void AttachAnimator (std::shared_ptr<Animator> animator);
	void DetachAnimator (std::shared_ptr<Animator> animator);
	void DetachAllAnimators ();

	bool UpdateAnimators (float appTime);
protected:
	~AnimatedObject ();
	List m_AnimatorList;
};
#endif