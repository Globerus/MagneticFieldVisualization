#ifndef TEXTURE_2_ARRAY_H
#define TEXTURE_2_ARRAY_H

#include "textureArray.h"

class Texture2Array : public TextureArray
{
public:
	Texture2Array (unsigned int numItems, ContainerType format, int dim0, int dim1, bool hasMipMap = false, bool createStorage = true);
	
	int GetWidth () const;
	int GetHeight () const;
};
#endif