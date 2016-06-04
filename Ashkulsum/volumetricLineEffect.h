#ifndef VOLUMETRIC_LINE_EFFECT_H
#define VOLUMETRIC_LINE_EFFECT_H

#include "visualEffect.h"
#include "texture2.h"
#include "programFactory.h"
#include "uniformBuffer.h"
#include "pathEnvironment.h"

class VolumetricLineEffect : public VisualEffect
{
public:
	VolumetricLineEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2> const& texture, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1);

	std::shared_ptr<UniformBuffer> const& GetPVWMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetVWMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetColourUniformBuffer () const;

	std::shared_ptr<Texture2> const& GetTexture () const;
	std::shared_ptr<SamplerState> const& GetSampler () const;

	void SetColour (glm::vec4 const& colour);
private:
	std::shared_ptr<UniformBuffer> m_PVWMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_VWMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_ColourUniformBuffer;

	std::shared_ptr<Texture2> m_Texture;
	std::shared_ptr<SamplerState> m_Sampler;
};
#endif