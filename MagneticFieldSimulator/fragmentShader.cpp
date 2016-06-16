#include "stdafx.h"
#include "fragmentShader.h"

FragmentShader::FragmentShader ()
	:	Shader ()
{
	m_Type = DP_FRAGMENT_SHADER;
}

FragmentShader::FragmentShader (OGLReflection const& reflector) 
	:	Shader (reflector, OGLReflection::ST_FRAGMENT)
{
	m_Type = DP_FRAGMENT_SHADER;
}