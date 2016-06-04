#ifndef TEXTURE_DS_H
#define TEXTURE_DS_H

#include "texture2.h"

class TextureDS : public Texture2
{
public:
	TextureDS (ContainerType format, unsigned int dim0, unsigned int dim1, bool createStorage);
};
#endif