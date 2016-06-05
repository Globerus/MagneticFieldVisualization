#ifndef OGL_TEXTURE_ARRAY_H
#define OGL_TEXTURE_ARRAY_H

#include "oglTexture.h"
#include "textureArray.h"

class OGLTextureArray : public OGLTexture
{
public:

	//virtual ~OGLTextureArray();

	inline std::shared_ptr<TextureArray> GetTexture () const;

	virtual bool Update ();

	bool Update(int item, int level);

	virtual bool CanGenerateAutoMipMaps() const = 0;

	virtual bool GenerateMipMaps();


protected:

	OGLTextureArray (std::shared_ptr<const TextureArray> texture, GLenum target);

	void Initialize();

	virtual void LoadTextureLevel(unsigned int item, unsigned int level, void const* data) = 0;

};

inline std::shared_ptr<TextureArray> OGLTextureArray::GetTexture() const
{
	return std::static_pointer_cast<TextureArray>(m_DPObject);
}

#endif