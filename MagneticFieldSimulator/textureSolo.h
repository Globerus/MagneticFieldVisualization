#ifndef TEXTURE_SOLO_H
#define TEXTURE_SOLO_H
#include "textureO.h"

class TextureSolo : public Texture
{
public:
	char const* GetDataFor (unsigned int level) const;

protected:
	TextureSolo (ContainerType format,unsigned int numDimensions, unsigned int dim0, unsigned int dim1, unsigned int dim2, bool hasMipMap, bool createStorage);

public:
	static int const shaderLookUp = 1;
};
#endif