#ifndef TRANSFORM_ANIMATOR_H
#define TRANSFORM_ANIMATOR_H

#include "animator.h"
#include "transformation.h"

class TransformAnimator : public Animator
{
public:
	TransformAnimator (Transformation const& transform);
	
	void SetTransform (Transformation const& transform);
	Transformation const& GetTransformation () const;

	virtual bool Update (float appTime);

protected:
	Transformation m_Transformation;
};
#endif