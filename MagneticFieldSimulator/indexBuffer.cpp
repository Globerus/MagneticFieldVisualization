#include "stdafx.h"
#include "indexBuffer.h"

IndexBuffer::IndexBuffer (PType pType, unsigned int numPrimitives, size_t indexSize, bool createStorage) 
	:	Buffer (numPrimitives, indexSize, createStorage),
		m_PrimitiveType (pType),
		m_NumPrimitives (numPrimitives),
		m_NumActivePrimitives (numPrimitives)
{	
	m_Type = DP_INDEX_BUFFER;
}

IndexBuffer::IndexBuffer (PType pType, unsigned int numPrimitives) 
	:	Buffer (numPrimitives, 0, false),
		m_PrimitiveType (pType),
		m_NumPrimitives (numPrimitives),
		m_NumActivePrimitives (numPrimitives)
{	
	m_Type = DP_INDEX_BUFFER;
}

int IndexBuffer::GetPrimitiveType () const
{
	return m_PrimitiveType;
}

unsigned int IndexBuffer::GetNumPrimitives () const
{
	return m_NumPrimitives;
}

unsigned int IndexBuffer::GetNumActivePrimitives () const
{
	return m_NumActivePrimitives;
}

void IndexBuffer::SetNumActivePrimitives (unsigned int numActivePrimitives)
{
	if (numActivePrimitives <= m_NumPrimitives)
	{
		m_NumActivePrimitives = numActivePrimitives;
	}
	else
	{
		m_NumActivePrimitives = m_NumPrimitives;
	}
}

bool IndexBuffer::IsIndexed () const
{
	return (m_Data != nullptr);
}