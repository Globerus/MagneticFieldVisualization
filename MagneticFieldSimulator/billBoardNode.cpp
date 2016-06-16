#include "stdafx.h"
#include "billBoardNode.h"


BillBoardNode::~BillBoardNode ()
{

}

BillBoardNode::BillBoardNode (std::shared_ptr<Camera> camera)
	:	m_Camera (camera)
{

}

void BillBoardNode::UpdateWorldData (float appTime)
{
	Node::UpdateWorldData (appTime);

	if (m_Camera)
	{
		glm::vec3 translation = m_LocalT.GetTranslation ();
		glm::vec3 position = glm::vec3(m_Camera->GetPosition ());
		
		glm::vec3 up = (glm::vec3) m_Camera->GetUpVector ();

		glm::vec3 depthAxis = glm::normalize (translation - position);
		glm::vec3 upAxis = glm::normalize (up);
		glm::vec3 rightAxis = glm::normalize (glm::cross (depthAxis, upAxis));

		glm::vec3 perpUpDir = glm::normalize (glm::cross(rightAxis, depthAxis));

		glm::mat4 mat (1.0f);

		mat[0].x = rightAxis.x;
		mat[0].y = rightAxis.y;
		mat[0].z = rightAxis.z;
		
		mat[1].x = perpUpDir.x;
		mat[1].y = perpUpDir.y;
		mat[1].z = perpUpDir.z;
		
		mat[2].x = -depthAxis.x;
		mat[2].y = -depthAxis.y;
		mat[2].z = -depthAxis.z;
		
		m_WorldT.SetRotation (m_WorldT.GetRotation ()*mat);
		

		std::vector <std::shared_ptr<Node>>::iterator iter;

		for (iter = m_Children.begin (); iter != m_Children.end (); iter ++)
		{
		 
			 if (iter->get ())
			 {
				 iter->get ()->Update ();
			 }
		 }
	}
}