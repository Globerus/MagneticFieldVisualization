#include "stdafx.h"
#include "glslShader.h"

GLSLShader::GLSLShader ()
{

}

std::string const& GLSLShader::GetSource () const
{
	return m_Source;
}

std::string const& GLSLShader::GetName () const
{
	return m_Name;
}

int GLSLShader::GetType () const 
{
	return m_Type;
}

void GLSLShader::SetSource (std::string const sSource)
{
	m_Source = sSource;
}

void GLSLShader::SetName (std::string const sName)
{
	m_Name = sName;
}

void GLSLShader::SetType (int const type)
{
	m_Type = type;
}

bool GLSLShader::IsValid () const
{
	if (m_Name == "" || m_Source == "")
	{
		return false;
	}

	return true;
}