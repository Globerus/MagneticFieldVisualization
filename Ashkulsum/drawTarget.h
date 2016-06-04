#ifndef DRAW_TARGET_H
#define DRAW_TARGET_H

#include "textureDS.h"
#include "textureRT.h"

class DrawTarget
{
public:
	//virtual ~DrawTarget ();
	DrawTarget (unsigned int numRenderTargets, ContainerType rtFormat, unsigned int width, unsigned int height, bool hasRTMipmaps,
		bool createRTStorage, ContainerType dsFormat, bool createDSStorage);

	bool HasRTMipMaps () const;
	void AutogenerateRTMipmaps ();
	bool WantAutogenerateRTMipmaps () const;

	std::shared_ptr<TextureRT> GetRTTexture (unsigned int i) const;
	std::shared_ptr<TextureDS> GetDSTexture () const;

	unsigned int GetNumTargets ();
	unsigned int GetWidth ();
	unsigned int GetHeight ();

protected:
	std::vector<std::shared_ptr<TextureRT>> m_RTTextures;
	std::shared_ptr<TextureDS> m_DSTexture;
};
#endif