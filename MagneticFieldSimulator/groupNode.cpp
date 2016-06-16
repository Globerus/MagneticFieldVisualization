#include "stdafx.h"
#include "groupNode.h"

GroupNode::~GroupNode ()
{
	std::vector<std::shared_ptr<Node>>::iterator it;
	for (it = m_Children.begin (); it != m_Children.end (); it++)
    {
        if (*it)
        {
            (*it)->SetParent(nullptr);
            (*it) = nullptr;
        }
    }
}

GroupNode::GroupNode ()
{

}

int GroupNode::AttachChild (std::shared_ptr<Node> const &child)
{
	if (!child.get ())
		fprintf (stderr, "The attachChild method in GroupNode failed, because the child is corupted.\n");

	if (child->GetParent ())
		fprintf (stderr, "The attachChild method in GroupNode failed, because the child has already a parent.\n");

	child->SetParent (this);

	std::vector<std::shared_ptr<Node>>::iterator it;

	int i = 0;
	for (it = m_Children.begin (); it != m_Children.end (); it++)
	{
		if (!(*it).get ())
		{
			(*it) = child;
			return i;
		}
		++i;
	}

	int const size = m_Children.size ();
	m_Children.push_back (child);
	return size;
}

int GroupNode::DetachChild (std::shared_ptr<Node> const &child)
{
	
	if (child.get ())
	{
		int i = 0;
		std::vector<std::shared_ptr<Node>>::iterator it;
		for (it = m_Children.begin (); it != m_Children.end (); it ++)
		{
			if((*it).get() == child.get())
			{
				(*it)->SetParent (nullptr);
				(*it).reset ();
				return i;
			}
			++i;
		}
	}
	return -1;
}

std::shared_ptr<Node> GroupNode::DetachChildAt (int i)
{
	if (0 <= i && i < (int)m_Children.size ())
	{
		std::shared_ptr<Node> child = m_Children[i];
		if (child)
		{
			child->SetParent (nullptr);
			m_Children[i].reset ();
		}
		return child;
	}
	return nullptr;
}

std::shared_ptr<Node> GroupNode::SetChild (int i, std::shared_ptr<Node> const &child)
{
	if (child)
		if (child->GetParent())
			fprintf (stderr, "The setChild method in GroupNode failed, because the child has already a parent.\n");

	if (0 <= i && i < (int)m_Children.size ())
	{
		std::shared_ptr<Node> prevChild = m_Children[i];
		if (prevChild)
			prevChild->SetParent (nullptr);

		child->SetParent (this);
		
		m_Children[i] = child;
		return prevChild;
	}
	
	if (child)
	{
		child->SetParent (this);
	}

	m_Children.push_back (child);
	return nullptr;
}

std::shared_ptr<Node> GroupNode::GetChild (int i)
{
	if (0 <= i && i < (int)m_Children.size ())
	{
		std::shared_ptr<Node> child = m_Children[i];
		
		if (child)
		{
			return child;
		}
	}

	return nullptr;
}

void GroupNode::UpdateWorldData (float appTime)
{
	 Node::UpdateWorldData(appTime);

	 std::vector <std::shared_ptr<Node>>::iterator iter;

	 for (iter = m_Children.begin (); iter != m_Children.end (); iter ++)
	 {
		 
		 if (iter->get ())
		 {
			 iter->get ()->Update (appTime);
		 }
	 }
}
