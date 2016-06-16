#ifndef GROUP_NODE_H
#define GROUP_NODE_H

#include "node.h"
#include <vector>

class GroupNode : public Node
{
public:
	GroupNode ();
	virtual ~GroupNode ();

	int GetUsed () const;
	int AttachChild (std::shared_ptr<Node> const &child);
	int DetachChild (std::shared_ptr<Node> const &child);


	std::shared_ptr<Node> DetachChildAt (int i);
	std::shared_ptr<Node> SetChild (int i, std::shared_ptr<Node> const &child);
	std::shared_ptr<Node> GetChild (int i);

	virtual void UpdateWorldData (float appTime);
	
protected:
	std::vector <std::shared_ptr<Node>> m_Children;
	
};
#endif