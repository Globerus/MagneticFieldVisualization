#include "stdafx.h"
#include "oglTexture2.h"

OGLTexture2::OGLTexture2 (std::shared_ptr<const Texture2> texture)
	:	OGLTextureSolo (texture, GL_TEXTURE_2D)
{
	glGenTextures (1, &m_OGLObject);

	glBindTexture (GL_TEXTURE_2D, m_OGLObject);

	auto const dim0 = texture->GetDimension (0);
	auto const dim1 = texture->GetDimension (1);
	glTexStorage2D (GL_TEXTURE_2D, m_NumLevels, m_InternalFormat, dim0, dim1);

	Initialize ();

	glBindTexture (GL_TEXTURE_2D, 0);
}

std::shared_ptr<OGLDrawObject> OGLTexture2::Create (std::shared_ptr<const DrawObject> drawObject)
{
	if (drawObject->GetType () == DP_TEXTURE_2)
	{
		return std::make_shared<OGLTexture2> (std::static_pointer_cast<Texture2 const> (drawObject));
	}

	fprintf (stderr, "The OGL Texture2 cannot be created, because the input argument is not correct.\n");
	return nullptr;
}

std::shared_ptr<Texture2> OGLTexture2::GetTexture () const
{
	return std::static_pointer_cast<Texture2> (m_DPObject);
}

bool OGLTexture2::CanGenerateAutoMipMaps ()  const
{
	auto texture = GetTexture ();

	return texture && texture->HasMipMaps () && texture->WantAutoGenerateMipMap ();
}

void OGLTexture2::LoadTextureLevel (unsigned int level, void const* data)
{
	auto texture = GetTexture ();

	if (texture && level < texture->GetNumLevels ())
	{
		auto dim0 = texture->GetDimension (0);
		auto dim1 = texture->GetDimension (1);
		glTexSubImage2D(m_Target, level, 0, 0, dim0, dim1, m_ExternalFormat, m_ExternalType, data);
	}
}