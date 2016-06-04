#ifndef SHADER_MANAGER_H
#define SHADER_MANAGER_H

#include "embeddedShaders.h"
#include "shaderProgram.h"
#include "utils.h"
#include <boost\shared_ptr.hpp>
#include <boost\make_shared.hpp>

class ShaderManager 
{
private:
	typedef std::map <std::string, ShaderProgram::SharedPtr> ShaderMap;

public:
	typedef boost::shared_ptr<ShaderManager> SharedPtr;

	static ShaderManager::SharedPtr GetInstance ();
	~ShaderManager ();

	ShaderProgram::SharedPtr CreateProgram (const char* inShaderName);
	void DeleteProgram (ShaderProgram::SharedPtr sProgram);

	std::string LoadSource (GLenum eShaderType, std::string inShaderName);
	GLuint LoadShader (GLenum eShaderType, std::string inShaderName);

	ShaderProgram::SharedPtr GetShaderProgram (const char* inShaderName);	

private:
	ShaderMap m_ShaderMap;
	static ShaderManager::SharedPtr s_Instance;
};
#endif