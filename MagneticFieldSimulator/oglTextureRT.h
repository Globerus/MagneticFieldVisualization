#ifndef OGL_TEXTURE_RT_H
#define OGL_TEXTURE_RT_H

#include "oglTexture2.h"
#include "textureRT.h"

class OGLTextureRT : public OGLTexture2
{
public:
	OGLTextureRT (std::shared_ptr<const TextureRT> texture);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> dObject);

	std::shared_ptr<TextureRT> GetTexture () const;

	virtual bool CanGenerateAutoMipMaps () const override;
};
#endif