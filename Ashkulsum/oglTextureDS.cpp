#include "stdafx.h"
#include "oglTextureDS.h"

OGLTextureDS::OGLTextureDS (std::shared_ptr<const TextureDS> dObject)
	:	OGLTexture2 (dObject)
{
}

std::shared_ptr<OGLDrawObject> OGLTextureDS::Create (std::shared_ptr<const DrawObject> dObject)
{
	if (dObject->GetType () == DP_TEXTURE_DS)
	{
		return std::make_shared<OGLTextureDS> (std::static_pointer_cast<const TextureDS> (dObject));
	}

	fprintf (stderr, "The create method of OGLTextureDS failed, because the object type is not correct.\n");
	return nullptr;
}

std::shared_ptr<TextureDS> OGLTextureDS::GetTexture () const
{
	return std::static_pointer_cast<TextureDS> (m_DPObject);
}

bool OGLTextureDS::CanGenerateAutoMipMaps () const
{
	return false;
}