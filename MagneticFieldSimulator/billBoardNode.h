#ifndef BILLBOARD_NODE_H
#define BILLBOARD_NODE_H

#include "groupNode.h"
#include "camera.h"
#include "transformation.h"
#include "glm\glm.hpp"

class BillBoardNode : public GroupNode
{
public:
	
	virtual ~BillBoardNode ();
	BillBoardNode (std::shared_ptr<Camera> camera);

	virtual void UpdateWorldData (float appTime);

	

protected:
	std::shared_ptr<Camera> m_Camera;

};
#endif