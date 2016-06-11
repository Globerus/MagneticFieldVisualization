#include "stdafx.h"
#include "node.h"

Node::~Node ()
{

}

Node::Node ()	
	:
	m_Parent (nullptr),
	m_IsDrawable (false),
	name ("")
{

}

void Node::Update (float appTime)
{
	
	UpdateWorldData (appTime);
}

void Node::UpdateWorldData (float appTime)
{
	UpdateAnimators (appTime);

	if (m_Parent)
	{
		m_WorldT = m_Parent->m_WorldT * m_LocalT;
	}
	else
		m_WorldT = m_LocalT;
}

Node* Node::GetParent ()
{
	return m_Parent;
}
