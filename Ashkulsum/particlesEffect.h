#ifndef PARTICLES_EFFECT_H
#define PARTICLES_EFFECT_H

#include "visualEffect.h"
#include "texture2.h"
#include "samplerState.h"
#include "programFactory.h"
#include "pathEnvironment.h"

class ParticlesEffect : public VisualEffect
{
public:
	ParticlesEffect (std::shared_ptr<ProgramFactory> const& programFactory,std::shared_ptr<Texture2> const& colorTexture, std::shared_ptr<Texture2> const& alphaTexture, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1);

	std::shared_ptr<UniformBuffer> const& GetProjectionMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetViewMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetWorldMatrixUniformBuffer () const;


	std::shared_ptr<Texture2> const& GetAlphaTexture () const;
	std::shared_ptr<Texture2> const& GetColorTexture () const;
	std::shared_ptr<SamplerState> const& GetSampler () const;

private:
	std::shared_ptr<UniformBuffer> m_ProjectionMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_ViewMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_WorldMatrixUniformBuffer;

	std::shared_ptr<Texture2> m_ColorTexture;
	std::shared_ptr<Texture2> m_AlphaTexture;
	std::shared_ptr<SamplerState> m_Sampler;
};
#endif