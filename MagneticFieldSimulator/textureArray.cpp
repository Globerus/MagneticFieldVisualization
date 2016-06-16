#include "stdafx.h"
#include "textureArray.h"

TextureArray::TextureArray (unsigned int numItems, ContainerType format, unsigned int numDimensions, int dim0, int dim1, int dim2, bool hasMipMap, bool createStorage)
	:	Texture (numItems, format, numDimensions, dim0, dim1, dim2, hasMipMap, createStorage)
{
	m_Type = DP_TEXTURE_ARRAY;

}