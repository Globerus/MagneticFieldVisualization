#include "stdafx.h"
#include "shaderProgram.h"

GLuint ShaderProgram::GetVertexShader ()
{
	return this-> m_VertexShader;
}

GLuint ShaderProgram::GetFragmentShader ()
{
	return this-> m_FragmentShader;
}
GLuint ShaderProgram::GetShaderProgram ()
{
	return this->m_ShaderProgram;
}

void ShaderProgram::SetVertexShader (GLuint vShader)
{
	this->m_VertexShader = vShader;
}

void ShaderProgram::SetFragmentShader (GLuint fShader)
{
	this->m_FragmentShader = fShader;
}

void ShaderProgram::SetShaderProgram (GLuint sProgram)
{
	this->m_ShaderProgram = sProgram;
}

GLint ShaderProgram::GetUniformIndex (const char* unifName)
{
	GLint result = -1;
	if (m_ShaderProgram != 0)
	{
		UniformMap::iterator iter;
		if (iter == m_UniformMap.find (unifName))
		{
			result = glGetUniformLocation (m_ShaderProgram, unifName);
			if (result != -1)
			{
				m_UniformMap[unifName] = result;
			}
		}
		else
			result = iter->second;
	}
	return result;
}