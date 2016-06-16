#include "stdafx.h"
#include "oglProgramPipelineObject.h"

OGLProgramPipelineObject::~OGLProgramPipelineObject ()
{

}

OGLProgramPipelineObject::OGLProgramPipelineObject ()
{
	GLuint progPipeline;
	glGenProgramPipelines (1, &progPipeline);

	*m_ContainerObject = progPipeline;
}

void OGLProgramPipelineObject::Enable () const
{
	if (m_ContainerObject)
	{
		glBindProgramPipeline (*m_ContainerObject);
	}
}

void OGLProgramPipelineObject::Disable () const
{
	glBindProgramPipeline (0);
}

void OGLProgramPipelineObject::UseProgramStages (OGLVertexShader const* oglVShader, OGLFragmentShader const* oglFShader)
{
	GLuint* pipeline = GetContainerObject ();
	glUseProgramStages(*pipeline, GL_VERTEX_SHADER_BIT, oglVShader->GetOGLDrawObject ());
	glUseProgramStages(*pipeline, GL_FRAGMENT_SHADER_BIT, oglFShader->GetOGLDrawObject ());

}