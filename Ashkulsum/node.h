#ifndef NODE_H
#define NODE_H

#include "animatedObject.h"
#include "transformation.h"
//#include "glm\glm.hpp"
//#include "boost\shared_ptr.hpp"

class Node : public AnimatedObject
{
public:
	
	virtual ~Node ();
	
	Node* GetParent ();

	inline void SetParent (Node* parent);

	void Update (float appTime = 0.0);

	Transformation m_LocalT; 
	Transformation m_WorldT;

	std::string name;

	virtual void UpdateWorldData (float appTime);

	bool m_IsDrawable;
	
protected:
	Node ();

private:
	Node* m_Parent;

};

inline void Node::SetParent (Node* parent)
{
	m_Parent = parent;
}
#endif