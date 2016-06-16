#include "stdafx.h"
#include "vertexBuffer.h"

VertexBuffer::VertexBuffer (VertexAttributes const& vAttrib, unsigned int numVertices, bool createStorage)
	:	Buffer (numVertices, vAttrib.GetVertexSize (), createStorage),
		m_VertexAttributes (vAttrib)
{	
	m_Type = DP_VERTEX_BUFFER;
	SetNumActiveElements (numVertices);
}

VertexAttributes const& VertexBuffer::GetVertexAttrib () const
{
	return m_VertexAttributes;
}

char* VertexBuffer::GetAttribData (VAType vaType, int counter, std::set<ContainerType> setTypes)
{
	if (!m_Data)
	{
		fprintf (stderr, "The getAttribData method in VertexBuffer failed, because the storage data is empty.\n");
		return nullptr;
	}
	int index = m_VertexAttributes.GetIndex (vaType, counter);

	ContainerType type = m_VertexAttributes.GetContainerType (index);

	if (setTypes.find (type) == setTypes.end ())
	{
		fprintf (stderr, "The getAttribData method in VertexBuffer failed, because the type was not found.\n");
		return nullptr;
	}

	return m_Data + m_VertexAttributes.GetOffset (index);
}