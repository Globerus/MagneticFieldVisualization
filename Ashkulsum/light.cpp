#include "stdafx.h"
#include "light.h"

Light::Light (std::string fileName)
{
	glm::vec4 lightIntensity;
	glm::vec3 lightPosition;
	double lightAttenuation;

	this->SetSupportedExtensions ();
	LoadLightParam (fileName, lightIntensity, lightPosition, lightAttenuation);

	this->SetLightIntensity (lightIntensity);
	this->SetLightPosition (lightPosition);
	this->SetLightAttenuation (lightAttenuation);
}

void Light::SetSupportedExtensions ()
{
	std::string supportedExtensions[] = {".lp"};
	std::vector <std::string> supExt (begin(supportedExtensions), end (supportedExtensions));

	this->m_SupportedExtensions = supExt;
}

void Light::LoadLightParam (std::string fileName, glm::vec4 &lightIntensity, glm::vec3 &lightPosition, double &lightAttenuation)
{
	std::string extension = boost::filesystem::extension (fileName);
	
	if (this->IsFileSupported (extension))
	{
		std::string fullDirPath = Utils::GetFullDirPath (fileName);
		
		
		std::ifstream stream (fullDirPath, std::ios::in);

		if (stream.is_open ())
		{
			std::string line, id;
			stream.clear ();
			stream.seekg(0, stream.beg);

			while (std::getline (stream, line))
			{
				std::istringstream sstream (line);
				sstream >> id;
				if (id == "li")
				{
					double x, y, z, a;
					sstream >> x >> y >> z >> a;
					lightIntensity = glm::vec4 (x, y, z, a);
				}
				else if (id == "lp")
				{
					double x, y, z;
					sstream >> x >> y >> z;
					lightPosition = glm::vec3 (x, y, z);
				}
				else if (id == "la")
				{
					double x;
					sstream >> x;
					lightAttenuation = x;
				}
			}
		}
		else
			throw std::invalid_argument ("Error while opening the file! File not found");
		
		stream.close ();
	}
	else
		throw std::invalid_argument ("Error while opening the file! Unsupported format");
}

glm::vec4 Light::GetLightIntensity ()
{
	return this->m_LightIntensity;
}

glm::vec3 Light::GetLightPosition ()
{
	return this->m_LightPosition;
}

double Light::GetLightAttenuation ()
{
	return this->m_LightAttenuation;
}

void Light::SetLightIntensity (glm::vec4 lightIntensity)
{
	this->m_LightIntensity = lightIntensity;
}

void Light::SetLightPosition (glm::vec3 lightPosition)
{
	this->m_LightPosition = lightPosition;
}

void Light::SetLightAttenuation (double lightAttenuation)
{
	this->m_LightAttenuation = lightAttenuation;
}