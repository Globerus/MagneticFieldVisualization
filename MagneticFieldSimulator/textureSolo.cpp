#include "stdafx.h"
#include "textureSolo.h"

TextureSolo::TextureSolo (ContainerType format, unsigned int numDimensions, unsigned int dim0, unsigned int dim1, unsigned int dim2, bool hasMipMap, bool createStorage)
	:	Texture (1, format, numDimensions, dim0, dim1, dim2, hasMipMap, createStorage)
{
	m_Type = DP_TEXTURE_SOLO;
}

char const* TextureSolo::GetDataFor (unsigned int level) const
{
	return Texture::GetDataFor (0, level);
}