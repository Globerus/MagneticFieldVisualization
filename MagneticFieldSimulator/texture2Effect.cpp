#include "stdafx.h"
#include "texture2Effect.h"

Texture2Effect::Texture2Effect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2> const& texture, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1)
	: m_Texture (texture)
{
	PathEnvironment pathEnvironment;

	std::string pathDir = pathEnvironment.GetExeDir ();

	std::string pathVertShader = pathDir + "data\\shaders\\Scale.vert";
	std::string pathFragShader = pathDir + "data\\shaders\\Scale.frag";
	m_Program = programFactory->CreateFromFiles (pathVertShader, pathFragShader);

	if(m_Program)
	{
		m_Sampler = std::make_shared<SamplerState> ();

		m_Sampler->m_Filter = filter;
		m_Sampler->m_Mode[0] = mode0;
		m_Sampler->m_Mode[1] = mode1;

		m_Program->GetFragmentShader () ->Set ("scaleTexture", m_Texture);
		m_Program->GetFragmentShader () ->Set ("scaleTexture", m_Sampler);
	}
}

std::shared_ptr<Texture2> const& Texture2Effect::GetTexture () const
{
	return m_Texture;
}

std::shared_ptr<SamplerState> const& Texture2Effect::GetSampler () const
{
	return m_Sampler;
}