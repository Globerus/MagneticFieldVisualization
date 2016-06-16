#include "stdafx.h"
#include "material.h"

Material::Material ()
	:	m_Diffuse (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_Ambient (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_Emissive (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_Specular (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f))
{

}
