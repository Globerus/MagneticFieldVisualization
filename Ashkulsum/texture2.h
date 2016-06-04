#ifndef TEXTURE_2_H
#define TEXTURE_2_H
#include "textureSolo.h"

class Texture2 : public TextureSolo
{
public:
	Texture2 (ContainerType format, unsigned int dim0, unsigned int dim1, bool hasMipMap = false, bool createStorage = true);

	unsigned int GetWidth () const;
	unsigned int GetHeight () const;
};
#endif