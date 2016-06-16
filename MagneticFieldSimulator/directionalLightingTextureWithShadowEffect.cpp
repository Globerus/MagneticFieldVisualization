#include "stdafx.h"
#include "directionalLightingTextureWithShadowEffect.h"

DirectionalLightingTextureWithShadowEffect::DirectionalLightingTextureWithShadowEffect (std::shared_ptr<ProgramFactory> const& programFactory, BufferUpdater const& updater, std::shared_ptr<Material> const& material, std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraInfo> const& lightCameraInfo,
	std::shared_ptr<Texture2> texture, std::shared_ptr<TextureDS> shadowTexture, SamplerState::Filter filter, SamplerState::BoundaryMode mode)
	:	LightingEffect (programFactory, updater, "data\\shaders\\DirectLightingTextureWithShadow.vert", "data\\shaders\\DirectLightingTextureWithShadow.frag", material, lighting, lightCameraInfo),
		m_Texture (texture),
		m_ShadowTexture (shadowTexture)
{
	m_MaterialUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectMaterial), true);
	UpdateEffectMaterial ();

	m_LightingUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectLighting), true);
	UpdateEffectLighting ();

	m_LightCameraInfoUniformBuffer = std::make_shared<UniformBuffer> (sizeof(EffectLightCameraInfo), true);
	UpdateEffectLightCameraInfo ();
	

	m_NormalWorldMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);

	m_WorldMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);

	m_LightPVWMatrixUniformBuffer = std::make_shared<UniformBuffer> (sizeof(glm::mat4), true);

	if(m_Program)
	{
		m_Program->GetVertexShader ()->Set ("LightPVWMatrix", m_LightPVWMatrixUniformBuffer);
		m_Program->GetVertexShader ()->Set ("NormalWorldMatrix", m_NormalWorldMatrixUniformBuffer);
		m_Program->GetVertexShader ()->Set ("WorldMatrix", m_WorldMatrixUniformBuffer);

		m_TexSampler = std::make_shared<SamplerState> ();
		m_ShadowSampler = std::make_shared<SamplerState> ();

		m_TexSampler->m_Filter = filter;
		m_TexSampler->m_Mode[0] = mode;
		m_TexSampler->m_Mode[1] = mode;
		
		m_ShadowSampler->m_Filter = filter;
		m_ShadowSampler->m_Mode[0] = SamplerState::BORDER;
		m_ShadowSampler->m_Mode[1] = SamplerState::BORDER;
		m_ShadowSampler->m_BorderColor = glm::vec4 (1.0f, 1.0f, 1.0f, 1.0f);

		m_ShadowSampler->m_Comparison = SamplerState::LESS_EQUAL;

		m_Program->GetFragmentShader () ->Set ("materialTexture", m_Texture);
		m_Program->GetFragmentShader () ->Set ("materialTexture", m_TexSampler);
		m_Program->GetFragmentShader () ->Set ("shadowTexture", m_ShadowTexture);
		m_Program->GetFragmentShader () ->Set ("shadowTexture", m_ShadowSampler);

		m_Program->GetFragmentShader ()->Set ("Material", m_MaterialUniformBuffer);
		m_Program->GetFragmentShader ()->Set ("Lighting", m_LightingUniformBuffer);
		m_Program->GetFragmentShader ()->Set ("LightCameraInfo", m_LightCameraInfoUniformBuffer);
	}
}

void DirectionalLightingTextureWithShadowEffect::UpdateEffectLighting ()
{
	EffectLighting* effectLighting = m_LightingUniformBuffer->Get<EffectLighting> ();
	effectLighting->m_Diffuse = m_Lighting->m_Diffuse;
	effectLighting->m_Ambient = m_Lighting->m_Ambient;	
	effectLighting->m_Specular = m_Lighting->m_Specular;
	effectLighting->m_Attenuation = m_Lighting->m_Attenuation;
}

void DirectionalLightingTextureWithShadowEffect::UpdateEffectMaterial ()
{
	EffectMaterial* effectMaterial = m_MaterialUniformBuffer->Get<EffectMaterial> ();
	effectMaterial->m_Diffuse = m_Material->m_Diffuse;
	effectMaterial->m_Ambient = m_Material->m_Ambient;
	effectMaterial->m_Emissive = m_Material->m_Emissive;
	effectMaterial->m_Specular = m_Material->m_Specular;
}

void DirectionalLightingTextureWithShadowEffect::UpdateEffectLightCameraInfo ()
{
	EffectLightCameraInfo* effectLightCameraInfo = m_LightCameraInfoUniformBuffer->Get<EffectLightCameraInfo> ();
	effectLightCameraInfo->m_CameraPosition = m_LightCameraInfo->m_CameraPosition;
	effectLightCameraInfo->m_LightDirection = m_LightCameraInfo->m_LightDirection;
}

std::shared_ptr<UniformBuffer> const& DirectionalLightingTextureWithShadowEffect::GetWorldMatrixUniformBuffer () const
{
	return m_WorldMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& DirectionalLightingTextureWithShadowEffect::GetNormalWorldMatrixUniformBuffer () const
{
	return m_NormalWorldMatrixUniformBuffer;
}

std::shared_ptr<UniformBuffer> const& DirectionalLightingTextureWithShadowEffect::GetLightPVWMatrixUniformBuffer () const
{
	return m_LightPVWMatrixUniformBuffer;
}