#include "stdafx.h"
#include "animatedObject.h"

AnimatedObject::~AnimatedObject ()
{

}

AnimatedObject::AnimatedObject ()
{

}

void AnimatedObject::AttachAnimator (std::shared_ptr<Animator> animator)
{
	if (animator)
	{
		std::list<std::shared_ptr<Animator>> iter;

		for (auto & iter = m_AnimatorList.begin (); iter != m_AnimatorList.end(); iter ++)
		{
			if (*iter == animator)
			{
				return;
			}
		}

		animator.get ()->SetObject (this);
		m_AnimatorList.push_back (animator);
	}
}

bool AnimatedObject::UpdateAnimators (float appTime)
{
	bool updated = false;
	std::list<std::shared_ptr<Animator>> iter;

	for (auto & iter = m_AnimatorList.begin (); iter != m_AnimatorList.end(); iter ++)
	{
		if (iter->get ()->Update (appTime))
			updated = true;	
	}

	return updated;
}