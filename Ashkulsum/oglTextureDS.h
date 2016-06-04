#ifndef OGL_TEXTURE_DS_H
#define OGL_TEXTURE_DS_H

#include "oglTexture2.h"
#include "textureDS.h"

class OGLTextureDS : public OGLTexture2
{
public:
	OGLTextureDS (std::shared_ptr<const TextureDS> texture);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> dObject);

	std::shared_ptr<TextureDS> GetTexture () const;

	virtual bool CanGenerateAutoMipMaps () const override;
};
#endif