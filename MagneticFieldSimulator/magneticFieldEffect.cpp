#include "stdafx.h"
#include "magneticFieldEffect.h"

MagneticFieldEffect::MagneticFieldEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2Array> const& magneticFieldTextureArray, std::shared_ptr<Texture2> const& colorScaleTexture, glm::vec3 index, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1)
	:	m_MagneticFieldTextureArray (magneticFieldTextureArray),
		m_ColorScaleTexture (colorScaleTexture)
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

		m_WMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
		m_Program->GetVertexShader ()->Set ("WMatrix", m_WMatrixUniformBuffer);

		m_ArrayIndexUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::vec3), true);
		m_Program->GetVertexShader ()->Set ("ArrayIndex", m_ArrayIndexUniformBuffer);

		m_ArrayIndexUniformBuffer->SetMember ("arrayIndex", index);
		
		m_Sampler = std::make_shared<SamplerState> ();

		m_Sampler->m_Filter = filter;
		m_Sampler->m_Mode[0] = mode0;
		m_Sampler->m_Mode[1] = mode1;

		m_Program->GetFragmentShader () ->Set ("magneticFieldTextureArray", m_MagneticFieldTextureArray);
		m_Program->GetFragmentShader () ->Set ("colorScaleTexture", m_ColorScaleTexture);
		
		m_Program->GetFragmentShader () ->Set ("magneticFieldTextureArray", m_Sampler);
		m_Program->GetFragmentShader () ->Set ("colorScaleTexture", m_Sampler);
		
	}
}

std::shared_ptr<Texture2Array> const& MagneticFieldEffect::GetMagneticFieldTextureArray () const
{
	return m_MagneticFieldTextureArray;
}

std::shared_ptr<Texture2> const& MagneticFieldEffect::GetColorScaleTexture () const
{
	return m_ColorScaleTexture;
}

std::shared_ptr<SamplerState> const& MagneticFieldEffect::GetSampler () const
{
	return m_Sampler;
}

std::shared_ptr<UniformBuffer> const& MagneticFieldEffect::GetPVWMatrixUniformBuffer () const
{
	return m_PVWMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& MagneticFieldEffect::GetWMatrixUniformBuffer () const
{
	return m_WMatrixUniformBuffer;
}
