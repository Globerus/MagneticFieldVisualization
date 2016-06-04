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
/*class Material
{
public:
	Material () {};
	~Material () {};

	typedef boost::shared_ptr <Material> MaterialPtr;

	glm::vec4 GetColours ();
	glm::vec4 GetAmbientIntensity ();
	double GetShinninessFactor ();
	std::string GetShaderProgramID ();
	
	void SetColours (glm::vec4 colour);
	void SetAmbientIntensity (glm::vec4 ambientIntensity);
	void SetShinninessFactor (double shinninessFactor);
	void SetShaderProgramID (std::string shaderProgram);

private:
	glm::vec4 m_Colour;
	glm::vec4 m_AmbientIntensity;
	double m_ShinninessFactor;
	std::string m_ShaderProgramID;
};*/

#endif