#ifndef OGL_TEXTURE_SOLO_H
#define OGL_TEXTURE_SOLO_H

#include "oglTexture.h"
#include "textureSolo.h"
class OGLTextureSolo : public OGLTexture
{
public:
	std::shared_ptr<TextureSolo> GetTexture () const;
	bool Update ();
	bool Update (int level);
	virtual bool GenerateMipMaps ();
	virtual bool CanGenerateAutoMipMaps () const = 0;

protected:
	OGLTextureSolo (std::shared_ptr<const TextureSolo> texture, GLenum target);

	void Initialize ();

	virtual void LoadTextureLevel (unsigned int level, void const* data) = 0;
};
#endif

