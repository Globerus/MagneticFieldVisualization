#include "stdafx.h"
#include "oglVertexArrayObject.h"

OGLVertexArrayObject::~OGLVertexArrayObject ()
{
}

OGLVertexArrayObject::OGLVertexArrayObject (std::shared_ptr<OGLVertexBuffer> oglVBuffer, std::shared_ptr<OGLIndexBuffer> oglIBuffer)		//m_NumAttrib (0)
{
	GLuint vertexArrayObject;
	glGenVertexArrays (1, &vertexArrayObject);
	

	glBindVertexArray (vertexArrayObject);
	
	auto type = oglVBuffer->GetType();
	oglVBuffer->Enable ();
	std::shared_ptr<VertexBuffer> vBuffer = std::static_pointer_cast<VertexBuffer> (oglVBuffer->GetDrawObject ());
	
	VertexAttributes vAttrib = vBuffer->GetVertexAttrib ();

	unsigned int numAttrib = vAttrib.GetNumAttrib ();
	
	for (int i = 0; i< (int)numAttrib; i++)
	{
		ContainerType type = vAttrib.GetContainerType (i);
		int offset = vAttrib.GetOffset(i);
		
		int numElements = DataAttributes::GetNumElement (type);	
		GLenum channelType = oglVBuffer->m_ChannelType[DataAttributes::GetElementType (type)];
		size_t vertSize = vAttrib.GetVertexSize ();

		glEnableVertexAttribArray (i);
		
		glVertexAttribPointer (i, numElements, channelType, GL_FALSE, vertSize, (void*)offset);
			
	}

	oglIBuffer->Enable ();

	m_ContainerObject = vertexArrayObject;
}

void OGLVertexArrayObject::Enable () const
{
	if (m_ContainerObject)
	{
		glBindVertexArray (m_ContainerObject);
	}
}

void OGLVertexArrayObject::Disable () const
{
		glBindVertexArray (0);
}