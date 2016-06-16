#include "stdafx.h"
#include "oglProgram.h"

OGLProgram::~OGLProgram ()
{

}

OGLProgram::OGLProgram (GLuint programHandle)
		:	m_ProgHandle (programHandle),
			m_Reflector (programHandle)
{
	
}
GLuint OGLProgram::GetProgramHandle () const
{
	return m_ProgHandle;
}

GLuint OGLProgram::GetVertexShaderHandle () const
{
	return m_VSHandle;
}

GLuint OGLProgram::GetFragmentShaderHandle () const
{
	return m_FSHandle;
}

OGLReflection const& OGLProgram::GetReflector () const
{
	return m_Reflector;
}