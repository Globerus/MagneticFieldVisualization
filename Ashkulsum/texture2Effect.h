#ifndef TEXTURE_2_EFFECT_H
#define TEXTURE_2_EFFECT_H

#include "visualEffect.h"
#include "texture2.h"
#include "samplerState.h"
#include "programFactory.h"
#include "pathEnvironment.h"
//#include "wicImageLoader.h"

class Texture2Effect : public VisualEffect
{
public:
	Texture2Effect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2> const& texture, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1);

	std::shared_ptr<Texture2> const& GetTexture () const;
	std::shared_ptr<SamplerState> const& GetSampler () const;
private:
	std::shared_ptr<Texture2> m_Texture;
	std::shared_ptr<SamplerState> m_Sampler;
};
#endif