#ifndef TEXTURE_ARRAY_H
#define TEXTURE_ARRAY_H

#include "textureO.h"

class TextureArray : public Texture
{
public:
	TextureArray (unsigned int numItems, ContainerType format, unsigned int numDimensions, int dim0, int dim1, int dim2, bool hasMipMap, bool createStorage);

	static int const shaderLookUp = 3;

	inline char const* GetDataFor(unsigned int item, unsigned int level) const;
	inline char* GetDataFor(unsigned int item, unsigned int level);
};

inline char const* TextureArray::GetDataFor(unsigned int item, unsigned int level) const
{
    return Texture::GetDataFor(item, level);
}

inline char* TextureArray::GetDataFor(unsigned int item, unsigned int level)
{
    return Texture::GetDataFor(item, level);
}


#endif