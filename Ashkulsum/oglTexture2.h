#ifndef OGL_TEXTURE_2_H
#define OGL_TEXTURE_2_H

#include "oglTextureSolo.h"
#include "texture2.h"

class OGLTexture2 : public OGLTextureSolo
{
public:
	OGLTexture2 (std::shared_ptr<const Texture2> texture);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> drawObject);

	std::shared_ptr<Texture2> GetTexture () const;

	virtual bool CanGenerateAutoMipMaps () const override;

	virtual void LoadTextureLevel (unsigned int level, void const* data) override;
};
#endif