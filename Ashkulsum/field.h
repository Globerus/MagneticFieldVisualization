#ifndef FIELD_H
#define FIELD_H

#include "visualEffect.h"
#include "texture2.h"
#include "texture2Array.h"
#include "samplerState.h"
#include "programFactory.h"
#include "pathEnvironment.h"
//#include "wicImageLoader.h"

class FieldEffect : public VisualEffect
{
public:
	FieldEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2Array> const& texture,  std::shared_ptr<Texture2> const& texture2, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1);

	std::shared_ptr<UniformBuffer> const& GetPVWMatrixUniformBuffer () const;

	std::shared_ptr<Texture2Array> const& GetTexture () const;
	std::shared_ptr<Texture2> const& GetTexture2 () const;
	std::shared_ptr<SamplerState> const& GetSampler () const;
private:
	std::shared_ptr<UniformBuffer> m_PVWMatrixUniformBuffer;

	std::shared_ptr<Texture2Array> m_Texture;
	std::shared_ptr<Texture2> m_Texture2;
	std::shared_ptr<SamplerState> m_Sampler;
};
#endif