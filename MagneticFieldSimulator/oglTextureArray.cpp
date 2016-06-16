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
        else
        {
            for (unsigned int item = 0; item < numItems; ++item)
            {
                for (unsigned int level = 0; level < m_NumLevels; ++level)
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
	auto texture = GetTexture();
    auto const numItems = texture->GetNumItems();

    if (CanGenerateAutoMipMaps())
    {
        for (unsigned int item = 0; item < numItems; ++item)
        {
            if (!Update(item, 0))
            {
                return false;
            }
        }
        GenerateMipMaps();
    }

    else
    {
        auto const numLevels = texture->GetNumLevels();
        for (unsigned int item = 0; item < numItems; ++item)
        {
            for (unsigned int level = 0; level < numLevels; ++level)
            {
                if (!Update(item, level))
                {
                    return false;
                }
            }
        }
    }
	return true;
}

bool OGLTextureArray::Update (int item, int level)
{
	auto texture = GetTexture();
    if (texture->GetUsage() != Resource::DYNAMIC_UPDATE)
    {
        fprintf(stderr, "The SendToGPU method in OGLTextureArray failed, because texture usage is not DYNAMIC_UPDATE.\n");
        return false;
    }

    return SendToGpu(item, level);
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

bool OGLTextureArray::SendToGpu(unsigned int item, unsigned int level)
{
    auto texture = GetTexture();

   if (CanGenerateAutoMipMaps() && (level > 0))
    {
        fprintf(stderr, "The SendToGPU method in OGLTextureArray failed, because cannot update automatically generated mipmaps in GPU.\n");
        return false;
    }

    auto const numItems = texture->GetNumItems();
    if (item >= numItems)
    {
        fprintf(stderr, "The SendToGPU method in OGLTextureArray failed, because item for TextureArray is out of range. \n");
        return false;
    }

    auto const numLevels = texture->GetNumLevels();
    if (level >= numLevels)
    {
        fprintf(stderr, "The SendToGPU method in OGLTextureArray failed, because level for TextureArray is out of range. \n");
        return false;
    }

    auto data = texture->GetDataFor(item, level);
    auto numBytes = texture->GetNumBytesFor(level);

    if ((data == nullptr) || (numBytes == 0))
    {
        fprintf(stderr, "The SendToGPU method in OGLTextureArray failed, because there is no source data for TextureArray. \n");
        return false;
    }

    auto const target = GetTarget();
    glBindTexture(target, m_OGLObject);

    LoadTextureLevel(item, level, data);

    glBindTexture(target, 0);

    return true;
}