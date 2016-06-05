#include "stdafx.h"
#include "texture2Array.h"

Texture2Array::Texture2Array (unsigned int numItems, ContainerType format, int dim0, int dim1, bool hasMipMap, bool createStorage)
	:	TextureArray (numItems, format, 2, dim0, dim1, 0, hasMipMap, createStorage)
{
	m_Type = DP_TEXTURE2_ARRAY;
}

int Texture2Array::GetWidth () const
{
	return GetDimension (0);
}

int Texture2Array::GetHeight () const
{
	return GetDimension (1);
}