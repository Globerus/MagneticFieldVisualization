#include "stdafx.h"
#include "oglShaderManager.h"

OGLShaderManager::~OGLShaderManager ()
{
	if (m_MapShader.HasElements ())
	{
		UnbindAll ();
	}
}

OGLShaderManager::OGLShaderManager ()
{

}

void OGLShaderManager::Bind (std::string const sName, GLuint* oglShader)
{	
	if (oglShader)
	{
		m_MapShader.Insert (sName, oglShader);
	}
}

bool OGLShaderManager::Unbind (std::string const sName)
{
	if (sName != "")
	{
		GLuint* oglShader = nullptr;

		if (m_MapShader.Remove (sName, oglShader))
		{
			delete oglShader;
		}

		return true;
	}
	else
	{
		return false;
	}
}

void OGLShaderManager::UnbindAll ()
{
	if (m_MapShader.HasElements ())
	{
		std::vector<GLuint*> vShader;
		m_MapShader.GatherAll (vShader);
		
		for (auto iter = vShader.begin (); iter!= vShader.end (); iter++)
		{
			delete *iter;
		}
		
		m_MapShader.RemoveAll ();
	}
}

GLuint* OGLShaderManager::Get (std::string const sName)
{
	GLuint* oglShader = nullptr;

	m_MapShader.Get (sName, oglShader); 

	return oglShader;
}

OGLShaderManager::ShaderMap::~ShaderMap ()
{

}

OGLShaderManager::ShaderMap::ShaderMap ()
{

}