#include "stdafx.h"
#include "oglTexture2Array.h"

OGLTexture2Array::OGLTexture2Array (std::shared_ptr<const Texture2Array> texture)
	:	OGLTextureArray (texture, GL_TEXTURE_2D_ARRAY)
{
	glGenTextures(1, &m_OGLObject);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_OGLObject);

    auto const width = texture->GetDimension(0);
    auto const height = texture->GetDimension(1);
    auto const numItems = texture->GetNumItems();
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, m_NumLevels, m_InternalFormat, width, height, numItems);

    Initialize();

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

std::shared_ptr<OGLDrawObject> OGLTexture2Array::Create( std::shared_ptr<const DrawObject> object)
{
    if (object->GetType() == DP_TEXTURE2_ARRAY)
    {
        return std::make_shared<OGLTexture2Array>(std::static_pointer_cast<const Texture2Array> (object));
    }

    fprintf (stderr, "The create method in OGLTexture2Array failed, because the object is not DP_TEXTURE2_ARRAY type.\n");
    return nullptr;
}

bool OGLTexture2Array::CanGenerateAutoMipMaps() const
{
    auto texture = GetTexture();

    return texture && texture->HasMipMaps() && texture->WantAutoGenerateMipMap();
}

void OGLTexture2Array::LoadTextureLevel(unsigned int item, unsigned int level, void const* data)
{
    auto texture = GetTexture();
    if (texture && level < texture->GetNumLevels())
    {
        auto const width = texture->GetDimensionFor(level, 0);
        auto const height = texture->GetDimensionFor(level, 1);

        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, level, 0, 0, item, width, height, 1,
            m_ExternalFormat, m_ExternalType, data);
    }
}