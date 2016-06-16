#ifndef OGL_SHADER_MANAGER_H
#define OGL_SHADER_MANAGER_H

#include "oglVertexShader.h"
#include "oglFragmentShader.h"
#include "customMap.h"
#include "shader.h"

class OGLShaderManager 
{
public:
	~OGLShaderManager ();
	OGLShaderManager ();

	static void Bind (std::string const sName, std::shared_ptr<OGLDrawObject> oglShader);

	bool Unbind (std::string const sName);
	void UnbindAll ();

	static GLuint* Get (std::string const sName);
	
private:
	class ShaderMap : public CustomMap<std::string const, std::shared_ptr<OGLDrawObject>>
	{
	public:
		~ShaderMap ();
		ShaderMap ();
	};

	static ShaderMap m_MapShader;
};
#endif