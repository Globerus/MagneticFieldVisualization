#include "stdafx.h"
#include "textureDS.h"

TextureDS::TextureDS (ContainerType format, unsigned int dim0, unsigned int dim1, bool createStorage)
	:	Texture2 (format, dim0, dim1, false, createStorage)
{
	m_Type = DP_TEXTURE_DS;
}