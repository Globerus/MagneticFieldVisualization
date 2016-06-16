#include "stdafx.h"
#include "shadowMapEffect.h"

ShadowMapEffect::ShadowMapEffect (std::shared_ptr<ProgramFactory> const& programFactory)
{
	PathEnvironment pathEnvironment;

	std::string pathDir = pathEnvironment.GetExeDir ();

	std::string pathVertShader = pathDir + "data\\shaders\\ShadowMap.vert";
	std::string pathFragShader = pathDir + "data\\shaders\\ShadowMap.frag";
	m_Program = programFactory->CreateFromFiles (pathVertShader, pathFragShader);

	if(m_Program)
	{
		m_PVWMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
		m_Program->GetVertexShader () ->Set ("PVWMatrix", m_PVWMatrixUniformBuffer);
	}
}

std::shared_ptr<UniformBuffer> const& ShadowMapEffect::GetPVWMatrixUniformBuffer () const
{
	return m_PVWMatrixUniformBuffer;
}