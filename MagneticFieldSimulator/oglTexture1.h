#ifndef OGL_TEXTURE_1
#define OGL_TEXTURE_1

#include "oglTextureSolo.h"
#include "texture1.h"

class OGLTexture1 : public OGLTextureSolo
{
public:
	OGLTexture1 (std::shared_ptr<const Texture1> texture);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> drawObject);

	std::shared_ptr<Texture1> GetTexture () const;

	virtual bool CanGenerateAutoMipMaps () const override;

	virtual void LoadTextureLevel (unsigned int level, void const* data) override;
};
#endif