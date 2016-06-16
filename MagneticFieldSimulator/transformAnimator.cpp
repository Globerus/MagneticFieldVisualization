#include "stdafx.h"
#include "transformAnimator.h"
#include "node.h"

TransformAnimator::TransformAnimator (Transformation const& transform)
	:	m_Transformation (transform)
{

}

void TransformAnimator::SetTransform (Transformation const& transform)
{
	m_Transformation = transform;
}

Transformation const& TransformAnimator::GetTransformation () const
{
	return m_Transformation;
}

bool TransformAnimator::Update (float appTime)
{
	if (!Animator::Update (appTime))
		return false;

	Node* node = static_cast<Node*> (m_Object);
	node->m_LocalT = m_Transformation;
	return true;
}