#include "stdafx.h"
#include "directionalLightingTextureEffect.h"

DirectionalLightingTextureEffect::DirectionalLightingTextureEffect (std::shared_ptr<ProgramFactory> const& programFactory, BufferUpdater const& updater, std::shared_ptr<Material> const& material, std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraInfo> const& lightCameraInfo,
	 std::shared_ptr<Texture2> texture, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1)
	:	LightingEffect (programFactory, updater, "data\\shaders\\DirectLightingTexture.vert", "data\\shaders\\DirectLightingTexture.frag", material, lighting, lightCameraInfo),
		m_Texture (texture)
{
	m_MaterialUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectMaterial), true);
	UpdateEffectMaterial ();

	m_LightingUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectLighting), true);
	UpdateEffectLighting ();

	m_LightCameraInfoUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectLightCameraInfo), true);
	UpdateEffectLightCameraInfo ();
	

	m_NormalWorldMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);

	m_WorldMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);

	if(m_Program)
	{
		m_Sampler = std::make_shared<SamplerState> ();

		m_Sampler->m_Filter = filter;
		m_Sampler->m_Mode[0] = mode0;
		m_Sampler->m_Mode[1] = mode1;

		m_Program->GetVertexShader ()->Set ("NormalWorldMatrix", m_NormalWorldMatrixUniformBuffer);
		m_Program->GetVertexShader ()->Set ("WorldMatrix", m_WorldMatrixUniformBuffer);


		m_Program->GetFragmentShader () ->Set ("materialTexture", m_Texture);
		m_Program->GetFragmentShader () ->Set ("materialTexture", m_Sampler);

		m_Program->GetFragmentShader ()->Set ("Material", m_MaterialUniformBuffer);
		m_Program->GetFragmentShader ()->Set ("Lighting", m_LightingUniformBuffer);
		m_Program->GetFragmentShader ()->Set ("LightCameraInfo", m_LightCameraInfoUniformBuffer);
	}
}

void DirectionalLightingTextureEffect::UpdateEffectLighting ()
{
	EffectLighting* effectLighting = m_LightingUniformBuffer->Get<EffectLighting> ();
	effectLighting->m_Diffuse = m_Lighting->m_Diffuse;
	effectLighting->m_Ambient = m_Lighting->m_Ambient;	
	effectLighting->m_Specular = m_Lighting->m_Specular;
	effectLighting->m_Attenuation = m_Lighting->m_Attenuation;
}

void DirectionalLightingTextureEffect::UpdateEffectMaterial ()
{
	EffectMaterial* effectMaterial = m_MaterialUniformBuffer->Get<EffectMaterial> ();
	effectMaterial->m_Diffuse = m_Material->m_Diffuse;
	effectMaterial->m_Ambient = m_Material->m_Ambient;
	effectMaterial->m_Emissive = m_Material->m_Emissive;
	effectMaterial->m_Specular = m_Material->m_Specular;
}

void DirectionalLightingTextureEffect::UpdateEffectLightCameraInfo ()
{
	EffectLightCameraInfo* effectLightCameraInfo = m_LightCameraInfoUniformBuffer->Get<EffectLightCameraInfo> ();
	effectLightCameraInfo->m_CameraPosition = m_LightCameraInfo->m_CameraPosition;
	effectLightCameraInfo->m_LightDirection = m_LightCameraInfo->m_LightDirection;
}

std::shared_ptr<UniformBuffer> const& DirectionalLightingTextureEffect::GetWorldMatrixUniformBuffer () const
{
	return m_WorldMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& DirectionalLightingTextureEffect::GetNormalWorldMatrixUniformBuffer () const
{
	return m_NormalWorldMatrixUniformBuffer;
}