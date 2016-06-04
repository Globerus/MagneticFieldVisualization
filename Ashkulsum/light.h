#ifndef LIGHT_H
#define LIGHT_H

#include "resourceBase.h"
#include "utils.h"
#include <fstream>
#include <sstream>
#include "boost\shared_ptr.hpp"
#include <boost\filesystem.hpp>
#include "glm\glm.hpp"

class Light : public ResourceBase
{
public:
	Light (std::string fileName);
	~Light () {};

	typedef boost::shared_ptr <Light> SharedPtr;

	void SetSupportedExtensions ();

	void LoadLightParam (std::string fileName, glm::vec4 &lightIntensity, glm::vec3 &lightPosition, double &lightAttenuation);

	void SetLightIntensity (glm::vec4 lightIntensity);
	void SetLightPosition (glm::vec3 lightPosition);
	void SetLightAttenuation (double lightAttenuation);

	glm::vec4 GetLightIntensity ();
	glm::vec3 GetLightPosition ();
	double GetLightAttenuation ();

private:
	glm::vec4 m_LightIntensity;
	glm::vec3 m_LightPosition;
	double m_LightAttenuation;
};
#endif