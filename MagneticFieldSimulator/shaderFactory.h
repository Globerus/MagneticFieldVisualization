#ifndef SHADER_FACTORY_H
#define SHADER_FACTORY_H

#include "shader.h"

class ShaderFactory 
{
public:
	static Shader* CreateFromString (std::string const& sName, std::string const& sSource, int sType);
	static Shader* CreateFromFile (std::string const& sFilename, int sType);

};
#endif