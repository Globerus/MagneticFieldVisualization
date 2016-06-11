#ifndef TEXTURE_O_H
#define TEXTURE_O_H

#include "resourceO.h"
#include "dataAttributes.h"
#include "bitWiseHack.h"
#include <array>

class Texture : public Resource
{
protected:
	Texture (unsigned int numItems, ContainerType format, unsigned int numDimensions, int dim0, int dim1, int dim2, bool hasMipMap, bool createStorage);

public:
	enum {MAX_MIPMAP_LEVEL = 32};
	unsigned int GetAllElements (unsigned int numItems, int dim0, int dim1, int dim2, bool hasMipMap);

	ContainerType GetFormat () const;
	unsigned int GetNumDimensions () const;
	unsigned int GetDimension (unsigned int i) const;
	unsigned int GetDimensionFor(unsigned int level, int i) const;
	unsigned int GetNumBytesFor (unsigned int level) const;
	unsigned int GetNumItems () const;
	unsigned int GetNumLevels () const;

	char const* GetDataFor (unsigned int item, unsigned int level) const;
	char* GetDataFor (unsigned int item, unsigned int level);
	
	bool HasMipMaps () const;

	void AutoGenerateMipMap ();

	bool WantAutoGenerateMipMap () const;

protected:
	unsigned int m_NumItems;
	unsigned int m_NumLevels;
	unsigned int m_NumDimensions;
	ContainerType m_Format;
	bool m_HasMipMap;
	bool m_AutoGenerateMipMap;
	std::array<std::array<unsigned int, 3>, MAX_MIPMAP_LEVEL> m_LevelDimensions;
	std::array<unsigned int, MAX_MIPMAP_LEVEL> m_LevelNumBytes;
	std::vector <std::array<unsigned int, MAX_MIPMAP_LEVEL>> m_LevelOffset;
};
#endif