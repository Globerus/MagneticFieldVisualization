#include "stdafx.h"
#include "material.h"

Material::Material ()
	:	m_Diffuse (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_Ambient (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_Emissive (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f)),
		m_Specular (glm::vec4 (0.0f, 0.0f, 0.0f, 1.0f))
{

}
/*
Material::Material ()
{
	glm::vec4 ambientIntensity, colour;
	double shinninessFactor;
	std::string shader;

	this->SetSupportedExtensions ();
	LoadMaterialParam (fileName, ambientIntensity, shinninessFactor, colour, shader);

	this->SetAmbientIntensity (ambientIntensity);
	this->SetShinninessFactor (shinninessFactor);
	this->SetColours (colour);
	this->SetShaderProgramID (shader);
}

void Material::SetSupportedExtensions ()
{
	std::string supportedExtensions[] = {".mtrl"};
	std::vector <std::string> supExt (begin(supportedExtensions), end (supportedExtensions));

	this->m_SupportedExtensions = supExt;
}

void Material::LoadMaterialParam (std::string fileName, glm::vec4 &ambientIntensity, double &shinninessFactor, glm::vec4 &colour, std::string &shader)
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
					if (id == "ai")
					{
						double x, y, z, a;
						sstream >> x >> y >> z >> a;
						ambientIntensity = glm::vec4 (x, y, z, a);
					}
					else if (id == "sf")
					{
						double x;
						sstream >>x;
						shinninessFactor = x;
					}
					else if (id == "c")
					{
						double x, y, z, a;
						sstream >> x >> y >> z >> a;
						colour = glm::vec4 (x, y, z, a);
					}
					else if (id == "s")
					{
						std::string s;
						sstream >> s;
						shader = s;
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

glm::vec4 Material::GetAmbientIntensity ()
{
	return this->m_AmbientIntensity;
}

double Material::GetShinninessFactor ()
{
	return this->m_ShinninessFactor;
}

glm::vec4 Material::GetColours ()
{
	return this->m_Colour;
}

std::string Material::GetShaderProgramID ()
{
	return this->m_ShaderProgramID;
}



void Material::SetAmbientIntensity (glm::vec4 ambientIntensity)
{
	this->m_AmbientIntensity = ambientIntensity;
}

void Material::SetShinninessFactor (double shinninessFactor)
{
	this->m_ShinninessFactor = shinninessFactor;
}

void Material::SetColours (glm::vec4 colour)
{
	this->m_Colour = colour;
}

void Material::SetShaderProgramID (std::string shaderProgram)
{
	this->m_ShaderProgramID = shaderProgram;
}*/