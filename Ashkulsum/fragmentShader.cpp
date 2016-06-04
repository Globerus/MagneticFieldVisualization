#include "stdafx.h"
#include "fragmentShader.h"

//FragmentShader::FragmentShader (std::string const& sName, std::string const& sSource)
FragmentShader::FragmentShader ()
	//:	Shader (sName, sSource)
	:	Shader ()
{
	m_Type = DP_FRAGMENT_SHADER;
}

FragmentShader::FragmentShader (OGLReflection const& reflector) 
	:	Shader (reflector, OGLReflection::ST_FRAGMENT)
{
	m_Type = DP_FRAGMENT_SHADER;
}