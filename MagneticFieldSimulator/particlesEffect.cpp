#include "stdafx.h"
#include "particlesEffect.h"

ParticlesEffect::ParticlesEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2> const& colorTexture, std::shared_ptr<Texture2> const& alphaTexture, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1)
	:	m_AlphaTexture (alphaTexture),
		m_ColorTexture (colorTexture)
{
	PathEnvironment pathEnvironment;

	std::string pathDir = pathEnvironment.GetExeDir ();

	std::string pathVertShader = pathDir + "data\\shaders\\Particles.vert";
	std::string pathFragShader = pathDir + "data\\shaders\\Particles.frag";
	m_Program = programFactory->CreateFromFiles (pathVertShader, pathFragShader);

	if(m_Program)
	{
		m_ProjectionMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
		m_Program->GetVertexShader ()->Set ("ProjectionMatrix", m_ProjectionMatrixUniformBuffer);
		m_ViewMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
		m_Program->GetVertexShader ()->Set ("ViewMatrix", m_ViewMatrixUniformBuffer);
		m_WorldMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
		m_Program->GetVertexShader ()->Set ("WorldMatrix", m_WorldMatrixUniformBuffer);

		m_Sampler = std::make_shared<SamplerState> ();

		m_Sampler->m_Filter = filter;
		m_Sampler->m_Mode[0] = mode0;
		m_Sampler->m_Mode[1] = mode1;

		m_Program->GetFragmentShader () ->Set ("colorTexture", m_ColorTexture);
		m_Program->GetFragmentShader () ->Set ("colorTexture", m_Sampler);
		m_Program->GetFragmentShader () ->Set ("alphaTexture", m_AlphaTexture);
		m_Program->GetFragmentShader () ->Set ("alphaTexture", m_Sampler);
	}
}

std::shared_ptr<UniformBuffer> const& ParticlesEffect::GetProjectionMatrixUniformBuffer () const
{
	return m_ProjectionMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& ParticlesEffect::GetViewMatrixUniformBuffer () const
{
	return m_ViewMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& ParticlesEffect::GetWorldMatrixUniformBuffer () const
{
	return m_WorldMatrixUniformBuffer;
}

std::shared_ptr<Texture2> const& ParticlesEffect::GetAlphaTexture () const
{
	return m_AlphaTexture;
}

std::shared_ptr<Texture2> const& ParticlesEffect::GetColorTexture () const
{
	return m_ColorTexture;
}

std::shared_ptr<SamplerState> const& ParticlesEffect::GetSampler () const
{
	return m_Sampler;
}