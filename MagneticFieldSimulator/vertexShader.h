#ifndef VERTEX_SHADER_H
#define VERTEX_SHADER_H

#include "shader.h"
#include "oglReflection.h"

class VertexShader : public Shader
{
public:
	VertexShader ();

	VertexShader (OGLReflection const& reflector);
};
#endif