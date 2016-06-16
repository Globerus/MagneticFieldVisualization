#ifndef LIGHTING_H
#define LIGHTING_H

#include "include.h"

class Lighting 
{
public:
	Lighting ();

	glm::vec4 m_Diffuse;
	glm::vec4 m_Ambient;
	glm::vec4 m_Specular;
	glm::vec4 m_Attenuation;
};
#endif