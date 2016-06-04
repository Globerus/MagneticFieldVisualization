#include "stdafx.h"
#include "drawTarget.h"

DrawTarget::DrawTarget (unsigned int numRenderTargets, ContainerType rtFormat, unsigned int width, unsigned int height, bool hasRTMipmaps,
		bool createRTStorage, ContainerType dsFormat, bool createDSStorage)
{
	if (numRenderTargets > 0)
	{
		m_RTTextures.resize (numRenderTargets);
		
		for (unsigned int i = 0; i < m_RTTextures.size(); i++)
		{
			auto & texture = m_RTTextures[i];
			texture = std::make_shared<TextureRT> (rtFormat, width, height, hasRTMipmaps, createRTStorage);
		}

		if (dsFormat != DP_UNKNOWN)
		{
			if (DataAttributes::IsDepthFormat (dsFormat))
			{
				m_DSTexture = std::make_shared<TextureDS> (dsFormat, width, height, createDSStorage);

				m_DSTexture->SetUsage (Resource::STATIC);
			}
			else
			{
				fprintf (stderr, "The drawTarget method in DrawTarget failed, because the depth stencil format is not correct.\n");
			}
		}
	}
	else
	{
		fprintf (stderr, "The drawTarget method in DrawTarget failed, because the number of targets is 0.\n");
	}
}

bool DrawTarget::HasRTMipMaps () const
{
	if (m_RTTextures.size() > 0)
	{
		return m_RTTextures[0]->HasMipMaps ();
	}

	fprintf (stderr, "The hasRTMipmaps method in DrawTarget failed, because the number of render target textures is 0.\n");
	return false;
}

void DrawTarget::AutogenerateRTMipmaps ()
{
	if (HasRTMipMaps ())
	{
		for (unsigned int i = 0; i < m_RTTextures.size (); i++)
		{
			m_RTTextures[i]->AutoGenerateMipMap ();
		}
	}
}

bool DrawTarget::WantAutogenerateRTMipmaps () const
{
	if (m_RTTextures.size () > 0)
	{
		return m_RTTextures[0]->WantAutoGenerateMipMap ();
	}

	fprintf (stderr, "The wantAutogenerateRTMipmaps method in DrawTarget failed, because the number of render target textures is 0.\n");
	return false;
}

std::shared_ptr<TextureRT> DrawTarget::GetRTTexture (unsigned int i) const
{
	return m_RTTextures[i];
}

std::shared_ptr<TextureDS> DrawTarget::GetDSTexture () const
{
	return m_DSTexture;
}

unsigned int DrawTarget::GetWidth ()
{
	if (m_RTTextures.size() > 0)
	{
		return m_RTTextures[0]->GetWidth ();
	}

	fprintf (stderr, "The getWidth method in DrawTarget failed, because the number of render target textures is 0.\n");
	return 0;
}

unsigned int DrawTarget::GetHeight ()
{
	if (m_RTTextures.size() > 0)
	{
		return m_RTTextures[0]->GetHeight ();
	}

	fprintf (stderr, "The getHeight method in DrawTarget failed, because the number of render target textures is 0.\n");
	return 0;
}

unsigned int DrawTarget::GetNumTargets ()
{
	return static_cast<unsigned int> (m_RTTextures.size ());
}