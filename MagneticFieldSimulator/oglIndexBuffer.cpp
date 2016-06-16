#include "stdafx.h"
#include "oglIndexBuffer.h"

OGLIndexBuffer::OGLIndexBuffer (std::shared_ptr<const IndexBuffer> iBuffer)
	:	OGLBuffer (iBuffer, GL_ELEMENT_ARRAY_BUFFER)
{
	Initialize ();
}

std::shared_ptr<OGLDrawObject> OGLIndexBuffer::Create (std::shared_ptr<const DrawObject> iBuffer)
{
	return std::make_shared<OGLIndexBuffer> (std::static_pointer_cast<IndexBuffer const> (iBuffer));
}

std::shared_ptr<IndexBuffer> OGLIndexBuffer::GetIndexBuffer () const
{
	return std::static_pointer_cast<IndexBuffer> (m_DPObject);
}

void OGLIndexBuffer::Enable () const
{
	glBindBuffer (m_Type, m_OGLObject);
}

void OGLIndexBuffer::Disable () const
{
	glBindBuffer (m_Type, 0);
}