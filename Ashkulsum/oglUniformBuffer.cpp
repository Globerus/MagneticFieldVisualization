#include "stdafx.h"
#include "oglUniformBuffer.h"

OGLUniformBuffer::OGLUniformBuffer (std::shared_ptr<const UniformBuffer> uBuffer)
	:	OGLBuffer (uBuffer, GL_UNIFORM_BUFFER)
{
	Initialize ();
}


std::shared_ptr<OGLDrawObject> OGLUniformBuffer::Create (std::shared_ptr<const DrawObject> uBuffer)
{
	if (uBuffer)
	{
		return std::make_shared<OGLUniformBuffer> (std::static_pointer_cast<UniformBuffer const> (uBuffer));
	}

	fprintf (stderr, "The OGL Uniform buffer cannot be created, because the input argument is not correct.\n");
	return nullptr;
}

void OGLUniformBuffer::BindData (GLuint bindingPoint, GLuint bindIndex)
{
	glBindBufferBase (m_Type, bindIndex, m_OGLObject);
}
