#include "stdafx.h"
#include "shaderFactory.h"

Shader* ShaderFactory::CreateFromString (std::string const& sName, std::string const& sSource, int sType)
{
	Shader* shader = new Shader ();
	shader->SetName (sName);
	shader->SetSource (sSource);
	shader->SetType (sType);

	return shader;
}