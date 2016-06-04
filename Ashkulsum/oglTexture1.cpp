#include "stdafx.h"
#include "oglTexture1.h"

OGLTexture1::OGLTexture1 (std::shared_ptr<const Texture1> texture)
	:	OGLTextureSolo (texture, GL_TEXTURE_1D)
{
	glGenTextures (1, &m_OGLObject);
	glBindTexture (GL_TEXTURE_1D, m_OGLObject);

	auto const dim0 = texture->GetDimension (0);
	glTexStorage1D (GL_TEXTURE_1D, m_NumLevels, m_InternalFormat, dim0);

	Initialize ();

	glBindTexture (GL_TEXTURE_1D, 0);
}

std::shared_ptr<OGLDrawObject> OGLTexture1::Create (std::shared_ptr<const DrawObject> drawObject)
{
	if (drawObject->GetType () == DP_TEXTURE_1)
	{
		return std::make_shared<OGLTexture1> (std::static_pointer_cast<Texture1 const> (drawObject));
	}

	fprintf (stderr, "The OGL Texture1 cannot be created, because the input argument is not correct.\n");
	return nullptr;
}

std::shared_ptr<Texture1> OGLTexture1::GetTexture () const
{
	return std::static_pointer_cast<Texture1> (m_DPObject);
}

bool OGLTexture1::CanGenerateAutoMipMaps ()  const
{
	auto texture = GetTexture ();

	return texture && texture->HasMipMaps () && texture->WantAutoGenerateMipMap ();
}

void OGLTexture1::LoadTextureLevel (unsigned int level, void const* data)
{
	auto texture = GetTexture ();

	if (texture && level < texture->GetNumLevels ())
	{
		auto dim0 = texture->GetDimension (0);

		glTexSubImage1D(GL_TEXTURE_1D, level, 0, dim0,
            m_ExternalFormat, m_ExternalType, data);
	}
}