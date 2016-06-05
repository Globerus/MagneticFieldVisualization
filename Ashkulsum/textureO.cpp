#include "stdafx.h"
#include "textureO.h"

Texture::Texture (unsigned int numItems, ContainerType format, unsigned int numDimensions, int dim0, int dim1, int dim2, bool hasMipMap, bool createStorage)
	:	Resource (GetAllElements (numItems, dim0, dim1, dim2, hasMipMap), DataAttributes::GetNumBytes (format), createStorage),
		m_NumItems (numItems),
		m_HasMipMap (hasMipMap),
		m_Format (format),
		m_NumLevels (1),
		m_NumDimensions (numDimensions),
		m_LevelOffset (numItems)
{
	m_Type = DP_TEXTURE;

	for (unsigned int level = 0; level < MAX_MIPMAP_LEVEL; ++level)
	{
		m_LevelDimensions[level][0] = 0;
		m_LevelDimensions[level][1] = 0;
		m_LevelDimensions[level][2] = 0;
		m_LevelNumBytes[level] = 0;
	}

	m_LevelDimensions[0][0] = dim0;
	m_LevelDimensions[0][1] = dim1;
	m_LevelDimensions[0][2] = dim2;
	m_LevelNumBytes[0] = dim0*dim1*dim2*m_ElementSize;

	for (unsigned int item = 0; item < m_NumItems; ++item)
	{
		for ( unsigned int level = 0; level < MAX_MIPMAP_LEVEL; ++level)
		{
			m_LevelOffset[item][level] = 0;
		}
	}

	if (hasMipMap)
	{
		unsigned int log0 = Log2OfPowerOfTwo (RoundDownToPowerOfTwo (dim0));
		unsigned int log1 = Log2OfPowerOfTwo (RoundDownToPowerOfTwo (dim1));
		unsigned int log2 = Log2OfPowerOfTwo (RoundDownToPowerOfTwo (dim2));

		m_NumLevels =1 + std::max (log0, std::max (log1, log2));

		for (unsigned int level = 1; level < m_NumLevels; ++level)
		{
			if (dim0 > 1)
				dim0 >>= 1;
			if (dim1 > 1)
				dim1 >>= 1;
			if (dim2 > 1)
				dim2 >>= 2;

			m_LevelNumBytes[level] = dim0*dim1*dim2*m_ElementSize;
			m_LevelDimensions[level][0] = dim0;
			m_LevelDimensions[level][1] = dim1;
			m_LevelDimensions[level][2] = dim2;
		}

		unsigned int numBytes = 0;

		for (unsigned int item = 0; item < m_NumItems; ++item)
		{
			for (unsigned int level = 0; level < MAX_MIPMAP_LEVEL; ++level)
			{
				m_LevelOffset[item][level] = numBytes;
				numBytes += m_LevelNumBytes[level];
			}
		}
	}
}

unsigned int Texture::GetAllElements (unsigned int numItems, int dim0, int dim1, int dim2, bool hasMipMap)
{
	unsigned int numElements = dim0*dim1*dim2;

	if (hasMipMap)
	{
		unsigned int log0 = Log2OfPowerOfTwo (RoundDownToPowerOfTwo (dim0));
		unsigned int log1 = Log2OfPowerOfTwo (RoundDownToPowerOfTwo (dim1));
		unsigned int log2 = Log2OfPowerOfTwo (RoundDownToPowerOfTwo (dim2));

		unsigned int numLevels = 1 + std::max (log0, std::max (log1, log2));

		for (unsigned int i = 1; i < numLevels; ++i)
		{
			if (dim0 > 1)
				dim0 >>= 1;
			if (dim1 > 1)
				dim1 >>= 1;
			if (dim2 > 1)
				dim2 >>= 2;

			numElements += dim0*dim1*dim2;
		}
	}
	return numItems * numElements;
}

ContainerType Texture::GetFormat () const
{
	return m_Format;
}

unsigned int Texture::GetNumDimensions () const
{
	return m_NumDimensions;
}

unsigned int Texture::GetDimension (unsigned int i) const
{
	return m_LevelDimensions[0][i];
}

unsigned int Texture::GetDimensionFor(unsigned int level, int i) const
{
	return m_LevelDimensions[level][i];
}

unsigned int Texture::GetNumItems () const
{
	return m_NumItems;
}
unsigned int Texture::GetNumLevels () const
{
	return m_NumLevels;
}

char* Texture::GetDataFor (unsigned int item, unsigned int level)
{
	if (m_Data)
	{
		return m_Data + m_LevelOffset[item][level];
	}

	fprintf (stderr, "The getDataFor method in TextureO failed, because the storage data is empty.\n");
	return nullptr;
}

char const* Texture::GetDataFor (unsigned int item, unsigned int level) const
{
	if (m_Data)
	{
		return m_Data + m_LevelOffset[item][level];
	}

	fprintf (stderr, "The getDataFor method in TextureO failed, because the storage data is empty.\n");
	return nullptr;
}

bool Texture::HasMipMaps () const
{
	return m_HasMipMap;
}

void Texture::AutoGenerateMipMap ()
{
	if (m_HasMipMap)
	{
		m_AutoGenerateMipMap = true;
	}
}

bool Texture::WantAutoGenerateMipMap () const
{
	return m_AutoGenerateMipMap;
}