#ifndef CAMERA_CONTROLLER_H
#define CAMERA_CONTROLLER_H

#include "CameraNode.h"
#include "glm\glm.hpp"
#include <math.h>
#include <limits.h>

class CameraControllerNode
{
public:
	CameraControllerNode (std::shared_ptr<CameraNode> cameraNode);

	//void RecalculatePositionAlternative ();
	//void RecalculatePosition ();

	//std::shared_ptr<CameraNode> GetCameraNode () const;

	void SetDragging (bool value);
	void SetMouseCoordinates (glm::vec2 const& prevPos);
	void SetMouseDelta (glm::vec2 const& delta);

	bool GetDragging () const;
	glm::vec2 const& GetMouseCoordinates () const;
	glm::vec2 const& GetMouseDelta () const;

private:
	std::shared_ptr<CameraNode> m_CameraNode;
	glm::vec2 m_PrevPos, m_Delta;

	bool m_IsDragging;
};
#endif