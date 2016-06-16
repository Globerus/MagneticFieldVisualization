#include "stdafx.h"
#include "oglVertexBuffer.h"

OGLVertexBuffer::OGLVertexBuffer (std::shared_ptr<const VertexBuffer> vBuffer)
	:	OGLBuffer (vBuffer, GL_ARRAY_BUFFER)
{
	Initialize ();
}

std::shared_ptr<OGLDrawObject> OGLVertexBuffer::Create (std::shared_ptr<const DrawObject> vBuffer)
{
	return std::make_shared<OGLVertexBuffer> (std::static_pointer_cast<VertexBuffer const> (vBuffer));
}


std::shared_ptr<VertexBuffer> OGLVertexBuffer::GetVertexBuffer () const
{
	return std::static_pointer_cast<VertexBuffer> (m_DPObject);
}

void OGLVertexBuffer::Enable () const
{
	if (m_OGLObject)
	{
		glBindBuffer (GL_ARRAY_BUFFER, m_OGLObject);
	}
}

void OGLVertexBuffer::Disable () const
{
	if (m_OGLObject)
	{
		glBindBuffer (GL_ARRAY_BUFFER, 0);
	}
}

GLenum const OGLVertexBuffer::m_ChannelType[] =
{
	GL_ZERO, //DP_NO_TYPE,
	GL_HALF_FLOAT, //DP_HALF,
	GL_FLOAT, //DP_FLOAT,
	GL_INT, //DP_INT,
	GL_UNSIGNED_INT, //DP_U_INT,
	GL_BYTE, //DP_BYTE,
	GL_UNSIGNED_BYTE, //DP_U_BYTE,
	GL_SHORT, //DP_SHORT,
	GL_UNSIGNED_SHORT, //DP_U_SHORT,
};