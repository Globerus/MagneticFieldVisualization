#include "stdafx.h"
#include "field.h"

FieldEffect::FieldEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2> const& texture, std::shared_ptr<Texture2> const& texture2, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1)
	:	m_Texture (texture),
		m_Texture2 (texture2)
{
	PathEnvironment pathEnvironment;

	std::string pathDir = pathEnvironment.GetExeDir ();

	std::string pathVertShader = pathDir + "data\\shaders\\Field.vert";
	std::string pathFragShader = pathDir + "data\\shaders\\Field.frag";
	m_Program = programFactory->CreateFromFiles (pathVertShader, pathFragShader);

	if(m_Program)
	{
		m_PVWMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
		m_Program->GetVertexShader ()->Set ("PVWMatrix", m_PVWMatrixUniformBuffer);

		m_Sampler = std::make_shared<SamplerState> ();

		m_Sampler->m_Filter = filter;
		m_Sampler->m_Mode[0] = mode0;
		m_Sampler->m_Mode[1] = mode1;

		m_Program->GetFragmentShader () ->Set ("fieldTexture", m_Texture);
		m_Program->GetFragmentShader () ->Set ("colorTexture", m_Texture2);
		m_Program->GetFragmentShader () ->Set ("fieldTexture", m_Sampler);
		m_Program->GetFragmentShader () ->Set ("colorTexture", m_Sampler);
	}
}

std::shared_ptr<Texture2> const& FieldEffect::GetTexture () const
{
	return m_Texture;
}

std::shared_ptr<Texture2> const& FieldEffect::GetTexture2 () const
{
	return m_Texture2;
}


std::shared_ptr<SamplerState> const& FieldEffect::GetSampler () const
{
	return m_Sampler;
}

std::shared_ptr<UniformBuffer> const& FieldEffect::GetPVWMatrixUniformBuffer () const
{
	return m_PVWMatrixUniformBuffer;
}