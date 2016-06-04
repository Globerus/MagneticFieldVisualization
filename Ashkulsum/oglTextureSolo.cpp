#include "stdafx.h"
#include "oglTextureSolo.h"

OGLTextureSolo::OGLTextureSolo (std::shared_ptr<const TextureSolo> texture, GLenum target)
	:	OGLTexture (texture, target)
{

}

void OGLTextureSolo::Initialize ()
{
	glBindTexture (m_Target, m_OGLObject);

	glTexParameteri (m_Target, GL_TEXTURE_BASE_LEVEL, 0);
	glTexParameteri (m_Target, GL_TEXTURE_MAX_LEVEL, m_NumLevels);

	auto texture = GetTexture ();

	if (texture->GetData())
	{
		if (CanGenerateAutoMipMaps ())
		{
			auto data = texture->GetDataFor (0);
			if (data)
			{
				LoadTextureLevel (0, data);
				GenerateMipMaps ();
			}
		}
		else
		{
			for (unsigned int level = 0; level <m_NumLevels; ++level)
			{
				auto data = texture->GetDataFor (level);
				if (data)
				{
					LoadTextureLevel (level, data);
				}
			}
		}
	
	}
}

bool OGLTextureSolo::Update ()
{
	return true;
}

bool OGLTextureSolo::Update (int level)
{
	return true;
}

std::shared_ptr<TextureSolo> OGLTextureSolo::GetTexture () const
{
	return std::static_pointer_cast<TextureSolo> (m_DPObject);
}

bool OGLTextureSolo::GenerateMipMaps ()
{
	if (CanGenerateAutoMipMaps ())
	{
		glBindTexture (m_Target, m_OGLObject);

		glGenerateMipmap (m_Target);

		glBindTexture (m_Target, 0);

		return true;
	}

	fprintf (stderr, "Cannot generate mipmaps for the texture.\n");
	return false;
}