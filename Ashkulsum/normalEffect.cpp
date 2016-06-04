#include "stdafx.h"
#include "normalEffect.h"

NormalEffect::NormalEffect (std::shared_ptr<ProgramFactory> const& factory)
{
	PathEnvironment pathEnvironment;

	std::string pathDir = pathEnvironment.GetExeDir ();

	std::string pathVertShader = pathDir + "data\\shaders\\NoLighting.vert";
	std::string pathFragShader = pathDir + "data\\shaders\\NoLighting.frag";
	m_Program = factory->CreateFromFiles (pathVertShader, pathFragShader);

	if (m_Program)
	{
		m_PVWMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
		m_ColourUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::vec4), false);

		m_Program->GetVertexShader ()->Set ("PVWMatrix", m_PVWMatrixUniformBuffer);
		m_Program->GetFragmentShader ()->Set ("Color", m_ColourUniformBuffer);

		m_ColourUniformBuffer->SetMember<glm::vec4> ("color", glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f));
	}
}

std::shared_ptr<UniformBuffer> const& NormalEffect::GetPVWMatrixUniformBuffer () const
{
	return m_PVWMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& NormalEffect::GetColourUniformBuffer () const
{
	return m_ColourUniformBuffer;
}

void NormalEffect::SetColour (glm::vec4 const& colour)
{
	m_ColourUniformBuffer->SetMember<glm::vec4> ("color", colour);
}
