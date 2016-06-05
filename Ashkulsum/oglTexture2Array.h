#ifndef OGL_TEXTURE_2_ARRAY_H
#define OGL_TEXTURE_2_ARRAY_H

#include "oglTextureArray.h"
#include "texture2Array.h"

class OGLTexture2Array : public OGLTextureArray 
{
public:
	OGLTexture2Array (std::shared_ptr<const Texture2Array> texture);
	
	static std::shared_ptr<OGLDrawObject> Create(std::shared_ptr<const DrawObject> object);

	inline std::shared_ptr<Texture2Array> GetTexture() const;

	virtual bool CanGenerateAutoMipMaps() const;

protected:
	virtual void LoadTextureLevel(unsigned int item, unsigned int level, void const* data);

};

inline std::shared_ptr<Texture2Array> OGLTexture2Array::GetTexture() const
{
    return std::static_pointer_cast<Texture2Array>(m_DPObject);
}
#endif