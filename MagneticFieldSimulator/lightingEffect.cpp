#include "stdafx.h"
#include "lightingEffect.h"

LightingEffect::LightingEffect (std::shared_ptr<ProgramFactory> const& programFactory, BufferUpdater const& updater, std::string const& vShader, std::string const& fShader, std::shared_ptr<Material> const& material, std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraInfo> const& lightCameraInfo)
	:	m_Material (material),
		m_Lighting (lighting),
		m_LightCameraInfo (lightCameraInfo)
{
	PathEnvironment pathEnvironment;

	std::string pathDir = pathEnvironment.GetExeDir ();

	std::string pathVertShader = pathDir + vShader;
	std::string pathFragShader = pathDir + fShader;
	m_Program = programFactory->CreateFromFiles (pathVertShader, pathFragShader);

	if (m_Program)
	{
		m_BufferUpdater = updater;
		m_PVWMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);
		m_Program->GetVertexShader ()->Set ("PVWMatrix", m_PVWMatrixUniformBuffer);
	}
}

std::shared_ptr<UniformBuffer> const& LightingEffect::GetPVWMatrixUniformBuffer () const
{
	return m_PVWMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& LightingEffect::GetMaterialUniformBuffer () const
{
	return m_MaterialUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& LightingEffect::GetLightingUniformBuffer () const
{
	return m_LightingUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& LightingEffect::GetLightCameraInfoUniformBuffer () const
{
	return m_LightCameraInfoUniformBuffer;
}

std::shared_ptr<Material> const& LightingEffect::GetMaterial () const
{
	return m_Material;
}
std::shared_ptr<Lighting> const& LightingEffect::GetLighting () const
{
	return m_Lighting;
}

std::shared_ptr<LightCameraInfo> const& LightingEffect::GetLightInfo () const
{
	return m_LightCameraInfo;
}

void LightingEffect::UpdateEffectLighting ()
{
	m_BufferUpdater (m_LightingUniformBuffer);
}

void LightingEffect::UpdateEffectMaterial ()
{
	m_BufferUpdater (m_MaterialUniformBuffer);
}

void LightingEffect::UpdateEffectLightCameraInfo ()
{
	m_BufferUpdater (m_LightCameraInfoUniformBuffer);
}