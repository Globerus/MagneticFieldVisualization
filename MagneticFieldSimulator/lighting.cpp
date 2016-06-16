#include "stdafx.h"
#include "lighting.h"

Lighting::Lighting ()
	:	m_Attenuation (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_Diffuse (glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f)),
		m_Ambient (glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f)),
		m_Specular (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f))
{

}