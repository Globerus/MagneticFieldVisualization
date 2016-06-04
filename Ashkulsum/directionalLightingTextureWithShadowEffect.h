#ifndef DIRECTIONAL_LIGHTING_TEXTURE_WITH_SHADOW_EFFECT_H
#define DIRECTIONAL_LIGHTING_TEXTURE_WITH_SHADOW_EFFECT_H

#include "lightingEffect.h"
#include "samplerState.h"
#include "textureDS.h"

class DirectionalLightingTextureWithShadowEffect : public LightingEffect
{
public:
	DirectionalLightingTextureWithShadowEffect (std::shared_ptr<ProgramFactory> const& programFactory, BufferUpdater const& updater, std::shared_ptr<Material> const& material, std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraInfo> const& lightCameraInfo,
		std::shared_ptr<Texture2> texture, std::shared_ptr<TextureDS> shadowTexture, SamplerState::Filter filter, SamplerState::BoundaryMode mode);

	struct EffectLighting
	{
		glm::vec4 m_Diffuse;
		glm::vec4 m_Ambient;
		glm::vec4 m_Specular;
		glm::vec4 m_Attenuation;
	};

	struct EffectMaterial
	{
		glm::vec4 m_Diffuse;
		glm::vec4 m_Ambient;
		glm::vec4 m_Emissive;
		glm::vec4 m_Specular;
	};

	struct EffectLightCameraInfo
	{
		glm::vec4 m_CameraPosition;
		glm::vec4 m_LightDirection;
	};

	std::shared_ptr<UniformBuffer> const& GetNormalWorldMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetWorldMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetLightPVWMatrixUniformBuffer () const;

	void UpdateEffectMaterial ();
	void UpdateEffectLighting ();
	void UpdateEffectLightCameraInfo ();

protected:
	std::shared_ptr<Texture2> m_Texture;
	std::shared_ptr<TextureDS> m_ShadowTexture;
	std::shared_ptr<SamplerState> m_TexSampler;
	std::shared_ptr<SamplerState> m_ShadowSampler;	

	std::shared_ptr<UniformBuffer> m_NormalWorldMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_WorldMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_LightPVWMatrixUniformBuffer;
};
#endif