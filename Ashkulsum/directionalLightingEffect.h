#ifndef DIRECTIONAL_LIGHTING_EFFECT_H
#define DIRECTIONAL_LIGHTING_EFFECT_H

#include "lightingEffect.h"

class DirectionalLightingEffect : public LightingEffect
{
public:
	DirectionalLightingEffect (std::shared_ptr<ProgramFactory> const& programFactory, BufferUpdater const& updater, std::shared_ptr<Material> const& material, std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraInfo> const& lightCameraInfo, glm::vec4 color);

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
	std::shared_ptr<UniformBuffer> const& GetColorUniformBuffer () const;

	virtual void UpdateEffectMaterial ();
	virtual void UpdateEffectLighting ();
	virtual void UpdateEffectLightCameraInfo ();

protected:
	std::shared_ptr<UniformBuffer> m_EffectLightingUniformBuffer;
	std::shared_ptr<UniformBuffer> m_EffectMaterialUniformBuffer;
	std::shared_ptr<UniformBuffer> m_EffectLightCameraInfoUniformBuffer;
	std::shared_ptr<UniformBuffer> m_NormalWorldMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_WorldMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_ColorUniformBuffer;
};
#endif