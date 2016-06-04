#include "stdafx.h"
#include "volumetricLineEffect.h"

VolumetricLineEffect::VolumetricLineEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2> const& texture, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1)
	: m_Texture (texture)
{
	PathEnvironment pathEnvironment;

	std::string pathDir = pathEnvironment.GetExeDir ();

	std::string pathVertShader = pathDir + "data\\shaders\\VolumetricLine.vert";
	std::string pathFragShader = pathDir + "data\\shaders\\VolumetricLine.frag";
	m_Program = programFactory->CreateFromFiles (pathVertShader, pathFragShader);

	m_PVWMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
	m_VWMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);

	m_Program->GetVertexShader ()->Set ("PVWMatrix", m_PVWMatrixUniformBuffer);
	m_Program->GetVertexShader ()->Set ("VWMatrix", m_VWMatrixUniformBuffer);

	if(m_Program)
	{
		m_Sampler = std::make_shared<SamplerState> ();

		m_Sampler->m_Filter = filter;
		m_Sampler->m_Mode[0] = mode0;
		m_Sampler->m_Mode[1] = mode1;

		m_Program->GetFragmentShader () ->Set ("glowTexture", m_Texture);
		m_Program->GetFragmentShader () ->Set ("glowTexture", m_Sampler);
	}
}

std::shared_ptr<UniformBuffer> const& VolumetricLineEffect::GetPVWMatrixUniformBuffer () const
{
	return m_PVWMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& VolumetricLineEffect::GetVWMatrixUniformBuffer () const
{
	return m_VWMatrixUniformBuffer;
}

std::shared_ptr<Texture2> const& VolumetricLineEffect::GetTexture () const
{
	return m_Texture;
}

std::shared_ptr<SamplerState> const& VolumetricLineEffect::GetSampler () const
{
	return m_Sampler;
}

void VolumetricLineEffect::SetColour (glm::vec4 const& colour)
{
	m_ColourUniformBuffer->SetMember<glm::vec4> ("color", colour);
}