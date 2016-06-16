#ifndef MAGNETIC_FIELD_H
#define MAGNETIC_FIELD_H

#include "visualEffect.h"
#include "texture2.h"
#include "texture2Array.h"
#include "samplerState.h"
#include "programFactory.h"
#include "pathEnvironment.h"

class MagneticFieldEffect : public VisualEffect
{
public:
	MagneticFieldEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2Array> const& magneticFieldTextureArray,  std::shared_ptr<Texture2> const& colorScaleTexture, glm::vec3 index, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1);

	std::shared_ptr<UniformBuffer> const& GetPVWMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetWMatrixUniformBuffer () const;

	std::shared_ptr<Texture2Array> const& GetMagneticFieldTextureArray () const;
	std::shared_ptr<Texture2> const& GetColorScaleTexture () const;
	std::shared_ptr<SamplerState> const& GetSampler () const;
private:
	std::shared_ptr<UniformBuffer> m_PVWMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_WMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_ArrayIndexUniformBuffer;

	std::shared_ptr<Texture2Array> m_MagneticFieldTextureArray;
	std::shared_ptr<Texture2> m_ColorScaleTexture;
	std::shared_ptr<SamplerState> m_Sampler;
};
#endif