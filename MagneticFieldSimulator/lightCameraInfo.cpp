#include "stdafx.h"
#include "lightCameraInfo.h"

LightCameraInfo::LightCameraInfo ()
	:	m_LightPosition (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_LightDirection (glm::vec4 (0.0f, 0.0f, -1.0f, 0.0f)),
		m_LightUp (glm::vec4 (0.0f, 1.0f, 0.0f, 0.0f)),
		m_LightRight (glm::vec4 (1.0f, 0.0f, 0.0f, 0.0f)),

		m_CameraPosition (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_CameraDirection (glm::vec4 (0.0f, 0.0f, -1.0f, 0.0f)),
		m_CameraUp (glm::vec4 (0.0f, 1.0f, 0.0f, 0.0f)),
		m_CameraRight (glm::vec4 (1.0f, 0.0f, 0.0f, 0.0f))
{

}