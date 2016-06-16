#ifndef DIRECTIONAL_LIGHTING_TEXTURE_EFFECT_H
#define DIRECTIONAL_LIGHTING_TEXTURE_EFFECT_H

#include "lightingEffect.h"
#include "samplerState.h"
#include "texture2.h"

class DirectionalLightingTextureEffect : public LightingEffect
{
public:
	DirectionalLightingTextureEffect (std::shared_ptr<ProgramFactory> const& programFactory, BufferUpdater const& updater, std::shared_ptr<Material> const& material, std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraInfo> const& lightCameraInfo,
		std::shared_ptr<Texture2> texture, SamplerState::Filter filter, SamplerState::BoundaryMode mode0, SamplerState::BoundaryMode mode1);

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

	void UpdateEffectMaterial ();
	void UpdateEffectLighting ();
	void UpdateEffectLightCameraInfo ();

protected:

	std::shared_ptr<UniformBuffer> m_NormalWorldMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_WorldMatrixUniformBuffer;
	std::shared_ptr<Texture2> m_Texture;
	std::shared_ptr<SamplerState> m_Sampler;


};
#endif