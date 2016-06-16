#include "stdafx.h"
#include "oglBuffer.h"

OGLBuffer::~OGLBuffer ()
{
	glDeleteBuffers (1, &m_OGLObject);
}

OGLBuffer::OGLBuffer (std::shared_ptr<const Buffer> buffer, GLenum type)
	:	OGLResource (buffer),
		m_Type (type)
{
	glGenBuffers (1, &m_OGLObject);

	Resource::Usage usage = buffer->GetUsage ();
	if (usage == Resource::STATIC)
	{
		m_Usage = GL_STATIC_DRAW;
	}
	else if (usage == Resource::DYNAMIC_UPDATE)
	{
		m_Usage = GL_DYNAMIC_DRAW;
	}
}

std::shared_ptr<Buffer> OGLBuffer::GetBuffer () const
{
	return std::static_pointer_cast<Buffer> (m_DPObject);
}

void OGLBuffer::Initialize ()
{
	glBindBuffer (m_Type, m_OGLObject);

	const auto buffer = GetBuffer ();
	glBufferData (m_Type, buffer->GetNumBytes (), buffer->GetData (), m_Usage);
	glBindBuffer (m_Type, 0);
}

bool OGLBuffer::Update ()
{
	auto buffer = GetBuffer ();

	if (buffer->GetUsage () != Resource::DYNAMIC_UPDATE)
	{
		fprintf (stderr, "The update method in OGLBuffer failed, because the usage is not DYNAMIC_UPDATE.\n");
		return false;
	}

	glBindBuffer (m_Type, m_OGLObject);
	glBufferSubData (m_Type, 0, buffer->GetNumBytes (), buffer->GetData ());
	glBindBuffer (m_Type, 0);

	return true;
}