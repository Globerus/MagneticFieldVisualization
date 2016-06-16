#ifndef LIGHT_CAMERA_INFO_H
#define LIGHT_CAMERA_INFO_H

#include "include.h"

class LightCameraInfo
{
public:
	LightCameraInfo ();

	glm::vec4 m_LightPosition;
	glm::vec4 m_LightDirection;
	glm::vec4 m_LightUp;
	glm::vec4 m_LightRight;

	glm::vec4 m_CameraPosition;
	glm::vec4 m_CameraDirection;
	glm::vec4 m_CameraUp;
	glm::vec4 m_CameraRight;
};
#endif