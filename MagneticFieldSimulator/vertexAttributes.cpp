#include "stdafx.h"
#include "vertexAttributes.h"

VertexAttributes::VertexAttributes ()
	:	m_NumAttributes (0),
		m_VertexSize (0)
{
}

bool VertexAttributes::Bind (VAType vaType, ContainerType containerType, int counter)
{
	if (m_NumAttributes < VA_MAX_NUMBER)
	{
		if (vaType == VA_TEXCOORD && counter > VA_MAX_TEXCOORDS)
		{
			fprintf (stderr, "The bind method in VertexAttributes class failed, because the counter is more than the allowed texCoords.\n");
		}

		Attributes& attributes = m_Attributes[m_NumAttributes];
		attributes.m_VAType = vaType;
		attributes.m_Counter = counter;
		attributes.m_ContainerType = containerType;
		attributes.m_Offset = m_VertexSize;
		
		++m_NumAttributes;
		
		m_VertexSize = m_VertexSize + DataAttributes::GetNumBytes (containerType);
		
		return true;
	}

	fprintf (stderr, "The bind method in VertexAttributes failed, because the max number of attributes has been reached.\n");
	return false;
}

unsigned int VertexAttributes::GetNumAttrib () const
{
	return m_NumAttributes;
}

int VertexAttributes::GetIndex (VAType vaType, int counter)
{
	for (int i = 0; i < (int)m_NumAttributes; i++)
		{
			if (m_Attributes[i].m_VAType == vaType && m_Attributes[i].m_Counter == counter)
			{
				return i;
			}
		}

	return -1;
}

ContainerType VertexAttributes::GetContainerType (int index) const
{
	return m_Attributes[index].m_ContainerType;
}

size_t VertexAttributes::GetOffset (int index) const
{
	return m_Attributes[index].m_Offset;
}

size_t VertexAttributes::GetVertexSize () const
{
	return m_VertexSize;
}

VertexAttributes::Attributes::Attributes ()
	:	m_Offset (0),
		m_ContainerType (DP_UNKNOWN),
		m_VAType (VA_NO_TYPE)
{
}