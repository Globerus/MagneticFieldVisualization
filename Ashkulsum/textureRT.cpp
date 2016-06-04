#include "stdafx.h"
#include "textureRT.h"

TextureRT::TextureRT (ContainerType format, unsigned int dim0, unsigned int dim1, bool hasMipMaps, bool createStorage)
	:	Texture2 (format, dim0, dim1, hasMipMaps, createStorage)
{
	m_Type = DP_TEXTURE_RT;
}