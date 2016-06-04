#include "stdafx.h"
#include "oglTextureRT.h"

OGLTextureRT::OGLTextureRT (std::shared_ptr<const TextureRT> dObject)
	:	OGLTexture2 (dObject)
{
}

std::shared_ptr<OGLDrawObject> OGLTextureRT::Create (std::shared_ptr<const DrawObject> dObject)
{
	if (dObject->GetType () == DP_TEXTURE_RT)
	{
		return std::make_shared<OGLTextureRT> (std::static_pointer_cast<const TextureRT> (dObject));
	}

	fprintf (stderr, "The create method of OGLTextureRT failed, because the object type is not correct.\n");
	return nullptr;
}

std::shared_ptr<TextureRT> OGLTextureRT::GetTexture () const
{
	return std::static_pointer_cast<TextureRT> (m_DPObject);
}

bool OGLTextureRT::CanGenerateAutoMipMaps () const
{
	auto texture = GetTexture ();

	return texture && texture->HasMipMaps () && texture->WantAutoGenerateMipMap ();
}