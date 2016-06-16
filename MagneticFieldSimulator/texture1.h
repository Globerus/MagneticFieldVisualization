#ifndef TEXTURE_1_H
#define TEXTURE_1_H
#include "textureSolo.h"

class Texture1 : public TextureSolo
{
public:
	Texture1 (ContainerType format, unsigned int dim0, bool hasMipMap = false, bool createStorage = true);
};
#endif