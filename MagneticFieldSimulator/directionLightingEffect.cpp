#include "stdafx.h"
#include "directionalLightingEffect.h"

DirectionalLightingEffect::DirectionalLightingEffect (std::shared_ptr<ProgramFactory> const& programFactory, BufferUpdater const& updater, std::shared_ptr<Material> const& material, std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraInfo> const& lightCameraInfo, glm::vec4 color)
	:	LightingEffect (programFactory, updater, "data\\shaders\\DirectLighting.vert", "data\\shaders\\DirectLighting.frag", material, lighting, lightCameraInfo)
{
	m_EffectMaterialUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectMaterial), true);
	UpdateEffectMaterial ();

	m_EffectLightingUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectLighting), true);
	UpdateEffectLighting ();

	m_EffectLightCameraInfoUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectLightCameraInfo), true);
	UpdateEffectLightCameraInfo ();

	m_NormalWorldMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);

	m_WorldMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);

	m_ColorUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::vec4), false);

	if (m_Program)
	{
		m_Program->GetVertexShader ()->Set ("NormalWorldMatrix", m_NormalWorldMatrixUniformBuffer);
		m_Program->GetVertexShader ()->Set ("WorldMatrix", m_WorldMatrixUniformBuffer);
		m_Program->GetFragmentShader ()->Set ("Color", m_ColorUniformBuffer);
		m_ColorUniformBuffer->SetMember ("color", color);

		m_Program->GetFragmentShader ()->Set ("Material", m_EffectMaterialUniformBuffer);
		m_Program->GetFragmentShader ()->Set ("Lighting", m_EffectLightingUniformBuffer);
		m_Program->GetFragmentShader ()->Set ("LightCameraInfo", m_EffectLightCameraInfoUniformBuffer);
	}
}

void DirectionalLightingEffect::UpdateEffectLighting ()
{
	EffectLighting* effectLighting = m_EffectLightingUniformBuffer->Get<EffectLighting> ();
	effectLighting->m_Diffuse = m_Lighting->m_Diffuse;
	effectLighting->m_Ambient = m_Lighting->m_Ambient;	
	effectLighting->m_Specular = m_Lighting->m_Specular;
	effectLighting->m_Attenuation = m_Lighting->m_Attenuation;
	LightingEffect::UpdateEffectLighting ();
}

void DirectionalLightingEffect::UpdateEffectMaterial ()
{
	EffectMaterial* effectMaterial = m_EffectMaterialUniformBuffer->Get<EffectMaterial> ();
	effectMaterial->m_Diffuse = m_Material->m_Diffuse;
	effectMaterial->m_Ambient = m_Material->m_Ambient;
	effectMaterial->m_Emissive = m_Material->m_Emissive;
	effectMaterial->m_Specular = m_Material->m_Specular;
	LightingEffect::UpdateEffectMaterial ();
}

void DirectionalLightingEffect::UpdateEffectLightCameraInfo ()
{
	EffectLightCameraInfo* effectLightCameraInfo = m_EffectLightCameraInfoUniformBuffer->Get<EffectLightCameraInfo> ();
	effectLightCameraInfo->m_CameraPosition = m_LightCameraInfo->m_CameraPosition;
	effectLightCameraInfo->m_LightDirection = m_LightCameraInfo->m_LightDirection;
	LightingEffect::UpdateEffectLightCameraInfo ();
}

std::shared_ptr<UniformBuffer> const& DirectionalLightingEffect::GetWorldMatrixUniformBuffer () const
{
	return m_WorldMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& DirectionalLightingEffect::GetNormalWorldMatrixUniformBuffer () const
{
	return m_NormalWorldMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& DirectionalLightingEffect::GetColorUniformBuffer () const
{
	return m_ColorUniformBuffer;
}
