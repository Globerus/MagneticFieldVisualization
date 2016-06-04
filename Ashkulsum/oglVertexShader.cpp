#include "stdafx.h"
#include "oglVertexShader.h"

OGLVertexShader::~OGLVertexShader ()
{

}

OGLVertexShader::OGLVertexShader (Shader const* vShader)
	:	OGLShader (vShader)
{
	GLuint* oglShader;

	std::string source = vShader->GetSource ();
	char const* sourcePointer = source.c_str ();
	*oglShader = glCreateShaderProgramv (GL_VERTEX_SHADER, 1, &sourcePointer);

	m_OGLObject = oglShader;
}

void OGLVertexShader::Enable (OGLProgramPipelineObject* ppo)
{
	glUseProgramStages(*ppo->GetContainerObject (), GL_VERTEX_SHADER_BIT, *m_OGLObject);
}

void OGLVertexShader::Disable (OGLProgramPipelineObject* ppo)
{
	glUseProgramStages(*ppo->GetContainerObject (), GL_VERTEX_SHADER_BIT, 0);
}

OGLDrawObject* OGLVertexShader::Create (DrawObject const* vShader)
{
	if (vShader->GetType () == ST_VERTEX)
	{
		return new OGLVertexShader (static_cast<Shader const*> (vShader));
	}

	return nullptr;
}

