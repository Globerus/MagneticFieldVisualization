#ifndef TEXTURE_RT_H
#define TEXTURE_RT_H

#include "texture2.h"

class TextureRT : public Texture2
{
public:
	TextureRT (ContainerType format, unsigned int dim0, unsigned int dim1, bool hasMipMaps, bool createStorage);
};
#endif