#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "shader.h"
#include "oglReflection.h"

class VertexShader : public Shader
{
public:
	//VertexShader (std::string const& sName, std::string const& sSource);
	VertexShader ();

	VertexShader (OGLReflection const& reflector);
};
#endif