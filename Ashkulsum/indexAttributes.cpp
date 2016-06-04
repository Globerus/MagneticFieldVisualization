#include "stdafx.h"
#include "indexAttributes.h"

IndexAttributes::IndexAttributes ()
{
}

void IndexAttributes::Bind (ContainerType containerType, ElementType elType)
{
	m_Attributes.m_ContainerType = containerType;
	m_Attributes.m_ElementType = elType;
	m_Attributes.m_NumIndexElements = DataAttributes::GetNumElement (containerType);
	m_IndexSize = sizeof (unsigned int);
}

void IndexAttributes::GetAttribute (unsigned int& numElements, ElementType& elType) const
{
	numElements = m_Attributes.m_NumIndexElements;
	elType = m_Attributes.m_ElementType;
}

size_t IndexAttributes::GetIndexSize () const
{
	return m_IndexSize;
}

IndexAttributes::Attributes::Attributes ()
{

}