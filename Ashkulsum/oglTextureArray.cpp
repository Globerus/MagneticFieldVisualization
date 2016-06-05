#include "stdafx.h"
#include "oglTextureArray.h"

OGLTextureArray::OGLTextureArray (std::shared_ptr<const TextureArray> texture, GLenum target)
	:	OGLTexture (texture, target)
{
	
}

void OGLTextureArray::Initialize ()
{
	glBindTexture(m_Target, m_OGLObject);

	glTexParameteri(m_Target, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(m_Target, GL_TEXTURE_MAX_LEVEL, m_NumLevels-1);

	auto texture = GetTexture();
    auto const numItems = texture->GetNumItems();
    if (texture->GetData())
    {
        // Initialize with first mipmap level and then generate mipmaps.
        if (CanGenerateAutoMipMaps())
        {
            for (unsigned int item = 0; item < numItems; ++item)
            {
                auto data = texture->GetDataFor(item, 0);
                if (data)
                {
                    LoadTextureLevel(item, 0, data);
                }
            }
            GenerateMipMaps();
        }
        // Initialize with each mipmap level.
        else
        {
            for (unsigned int item = 0; item < numItems; ++item)
            {
                for (int level = 0; level < m_NumLevels; ++level)
                {
                    auto data = texture->GetDataFor(item, level);
                    if (data)
                    {
                        LoadTextureLevel(item, level, data);
                    }
                }
            }
        }
    }
}

bool OGLTextureArray::Update ()
{
	return true;
}

bool OGLTextureArray::Update (int item, int level)
{
	return true;
}

bool OGLTextureArray::GenerateMipMaps ()
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