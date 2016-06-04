#include "stdafx.h"
#include "texture2.h"

Texture2::Texture2 (ContainerType format, unsigned int dim0, unsigned int dim1, bool hasMipMap, bool createStorage)
	:	TextureSolo (format, 2, dim0, dim1, 1, hasMipMap, createStorage)
{
	m_Type = DP_TEXTURE_2;
}

unsigned int Texture2::GetWidth () const
{
	return GetDimension (0);
}

unsigned int Texture2::GetHeight () const
{
	return GetDimension (1);
}