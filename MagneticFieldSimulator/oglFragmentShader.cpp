#include "stdafx.h"
#include "oglFragmentShader.h"

OGLFragmentShader::~OGLFragmentShader ()
{

}

OGLFragmentShader::OGLFragmentShader (Shader const* fShader)
	:	OGLShader (fShader)
{
	GLuint* oglShader;

	std::string source = fShader->GetSource ();
	char const* sourcePointer = source.c_str ();
	*oglShader = glCreateShaderProgramv (GL_FRAGMENT_SHADER, 1, &sourcePointer);
		
	m_OGLObject = oglShader;
}

void OGLFragmentShader::Enable (OGLProgramPipelineObject* ppo)
{
	glUseProgramStages(*ppo->GetContainerObject (), GL_FRAGMENT_SHADER_BIT, *m_OGLObject);
}

void OGLFragmentShader::Disable (OGLProgramPipelineObject* ppo)
{
	glUseProgramStages(*ppo->GetContainerObject (), GL_FRAGMENT_SHADER_BIT, 0);
}

OGLDrawObject* OGLFragmentShader::Create (DrawObject const* fShader)
{
	if (fShader->GetType () == ST_VERTEX)
	{
		return new OGLFragmentShader (static_cast<Shader const*> (fShader));
	}

	return nullptr;
}