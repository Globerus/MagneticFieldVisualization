#ifndef FRAGMENT_SHADER_H
#define FRAGMENT_SHADER_H

#include "shader.h"

class FragmentShader : public Shader
{
public:
	//FragmentShader (std::string const& sName, std::string const& sSource);
	FragmentShader ();

	FragmentShader (OGLReflection const& reflector);
};
#endif