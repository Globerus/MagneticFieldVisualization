#ifndef MATERIAL_H
#define MATERIAL_H

#include "include.h"

class Material
{
public:
	Material ();

	glm::vec4 m_Diffuse;
	glm::vec4 m_Ambient;
	glm::vec4 m_Emissive;
	glm::vec4 m_Specular;
};

#endif