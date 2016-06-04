#include "stdafx.h"
#include "texture1.h"

Texture1::Texture1 (ContainerType format, unsigned int dim0, bool hasMipMap, bool createStorage)
	:	TextureSolo (format, 1, dim0, 1, 1, hasMipMap, createStorage)
{
	m_Type = DP_TEXTURE_1;
}