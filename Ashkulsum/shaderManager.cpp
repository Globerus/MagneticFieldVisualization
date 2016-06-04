#include "stdafx.h"
#include "shaderManager.h"

ShaderManager::SharedPtr ShaderManager::s_Instance = NULL;

ShaderManager::~ShaderManager ()
{
	ShaderMap::iterator iter;

	for (iter = m_ShaderMap.begin (); iter != m_ShaderMap.end (); ++iter)
	{
		DeleteProgram (iter->second);
	}

	m_ShaderMap.clear ();
}

ShaderManager::SharedPtr ShaderManager::GetInstance ()
{
	if (s_Instance == nullptr)
	{
		s_Instance = boost::make_shared<ShaderManager> ();
	}
	return s_Instance;
}

std::string ShaderManager::LoadSource ( GLenum eShaderType, std::string inShaderName)
{
	int id;

	if (inShaderName == "LOADING")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_LOADING_VERT;
		else
			id = IDR_LOADING_FRAG;
	}
	else if (inShaderName == "LIGHTING")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_LIGHTING_VERT;
		else
			id = IDR_LIGHTING_FRAG;
	}
	else if (inShaderName == "NO_LIGHTING")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_NO_LIGHTING_VERT;
		else
			id = IDR_NO_LIGHTING_FRAG;
	}
	else if (inShaderName == "POINT")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_POINT_VERT;
		else
			id = IDR_POINT_FRAG;
	}
	else if (inShaderName == "SCALE")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_SCALE_VERT;
		else
			id = IDR_SCALE_FRAG;
	}
	else if (inShaderName == "SHADOW")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_SHADOW_VERT;
		else
			id = IDR_SHADOW_FRAG;
	}
	else if (inShaderName == "TEXT")
	{
		if (eShaderType == GL_VERTEX_SHADER)
			id = IDR_TEXT_VERT;
		else
			id = IDR_TEXT_FRAG;
	}
	else
	{
		id = NULL;
	}

	if (id != NULL)
	{
		HRSRC hRes = FindResource(NULL, MAKEINTRESOURCE(id), Utils::s2ws(inShaderName).c_str()); 
	
		if (!hRes)
			throw std::runtime_error("Could not find the resource ");
	
		HGLOBAL res_handle = LoadResource(NULL, hRes);
	
		if (!res_handle)
			throw std::runtime_error("Could not load the resource ");
	
		DWORD dataSize = SizeofResource(0, hRes);
		char*  res_data = (char*)LockResource(res_handle);
	
		std::string result;
		result.assign(res_data, dataSize);
	
		return result;
	}
	else
		return NULL;
}

GLuint ShaderManager::LoadShader (GLenum eShaderType, std::string inShaderName)
{
	std::string shaderStr = LoadSource (eShaderType, inShaderName);
	try
	{
		return glutil::CompileShader (eShaderType, shaderStr);
	}
	catch(std::exception &e)
	{
		fprintf(stderr, "%s\n", e.what());
		throw;
	}
}

ShaderProgram::SharedPtr ShaderManager::CreateProgram (const char* inShaderName)
{
	ShaderProgram::SharedPtr sProgram;

	GLuint vertShader, fragShader, shaderProgram;
	std::vector <GLuint> shaderArray;

	vertShader = LoadShader (GL_VERTEX_SHADER, inShaderName);
	fragShader = LoadShader (GL_FRAGMENT_SHADER, inShaderName);
	if ((vertShader != NULL) && (fragShader != NULL))
	{
		shaderArray.push_back (vertShader);
		shaderArray.push_back (fragShader);

		try
		{
			shaderProgram = glutil::LinkProgram (shaderArray); 
			std::for_each(shaderArray.begin(), shaderArray.end(), glDeleteShader);
		
			sProgram = boost::make_shared<ShaderProgram> ();
			sProgram->SetVertexShader (vertShader);
			sProgram->SetFragmentShader (fragShader);
			sProgram->SetShaderProgram (shaderProgram);

		} 
		catch(std::exception &e)
		{
			std::for_each(shaderArray.begin(), shaderArray.end(), glDeleteShader);
			fprintf(stderr, "%s\n", e.what());
			throw;
		}
	}
	return sProgram;
}

void ShaderManager::DeleteProgram (ShaderProgram::SharedPtr sProgram)
{
	if (sProgram->GetShaderProgram () != 0)
		glDeleteProgram(sProgram->GetShaderProgram ());

	if (sProgram->GetVertexShader () != 0)
		glDeleteShader (sProgram->GetVertexShader ());

	if (sProgram->GetFragmentShader () != 0)
		glDeleteShader (sProgram->GetFragmentShader ());
}

ShaderProgram::SharedPtr ShaderManager::GetShaderProgram (const char* inShaderName)
{
	ShaderProgram::SharedPtr sProgram;
	ShaderMap::iterator iter = m_ShaderMap.find (inShaderName);
	if (iter != m_ShaderMap.end ())
	{
		sProgram = iter->second;
	}
	else
	{
		sProgram = CreateProgram (inShaderName);
		if (sProgram != NULL)
		{
			m_ShaderMap[inShaderName] = sProgram;
		}
	}
	return sProgram;
}