#include "stdafx.h"
#include "resourceO.h"

Resource::~Resource ()
{
}

Resource::Resource (unsigned int numElements, size_t elementSize, bool createStorage)
	:	m_NumElements (numElements),
		m_ElementSize (static_cast<unsigned int> (elementSize)),
		m_Usage (STATIC),
		m_Data (nullptr)
{
	m_Type = DP_RESOURCE;

	if (elementSize > 0 && numElements > 0)
	{
		m_NumBytes = elementSize*numElements;
		m_NumActiveElements = numElements;
	}
	else
	{
		m_NumBytes = 0;
		m_NumActiveElements = 0;
	}

	if (createStorage)
		CreateStorage ();
}

unsigned int const & Resource::GetNumBytes () const
{
	return m_NumBytes;
}

unsigned int const & Resource::GetElementSize () const
{
	return m_ElementSize;
}

unsigned int const & Resource::GetNumElements () const
{
	return m_NumElements;
}

unsigned int const & Resource::GetNumActiveElements () const
{
	return m_NumActiveElements;
}

void Resource::SetNumActiveElements (unsigned int numActiveElements)
{
	if (numActiveElements <= m_NumElements)
	{
		m_NumActiveElements = numActiveElements;
	}
	else
	{
		m_NumActiveElements = m_NumElements;
	}
}

char const* Resource::GetData () const
{
	return m_Data;
}

char* Resource::GetData ()
{
	return m_Data;
}

void Resource::CreateStorage ()
{
	if (m_Storage.size () == 0)
	{
		m_Storage.resize (m_NumBytes);
		if (!m_Data)
		{
			m_Data = &m_Storage[0];
		}
	}
}

void Resource::SetUsage (Usage usage)
{
	m_Usage = usage;
}

Resource::Usage Resource::GetUsage () const
{
	return m_Usage;
}