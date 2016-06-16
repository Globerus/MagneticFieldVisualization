#include "stdafx.h"
#include "vertexShader.h"

VertexShader::VertexShader ()
	:	Shader ()
{
	m_Type = DP_VERTEX_SHADER;
}

VertexShader::VertexShader (OGLReflection const& reflector)
	:	Shader (reflector, OGLReflection::ST_VERTEX)
{
	m_Type = DP_VERTEX_SHADER;
};