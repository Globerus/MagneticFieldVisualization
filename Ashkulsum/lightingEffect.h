#ifndef LIGHTING_EFFECT_H
#define LIGHTING_EFFECT_H

#include "visualEffect.h"
#include "programFactory.h"
#include "pathEnvironment.h"
#include "uniformBuffer.h"
#include "material.h"
#include "lighting.h"
#include "lightCameraInfo.h"

class LightingEffect : public VisualEffect
{
public:
	LightingEffect (std::shared_ptr<ProgramFactory> const& programFactory, BufferUpdater const& updater, std::string const& vShader, std::string const& fShader, std::shared_ptr<Material> const& material, std::shared_ptr<Lighting> const& lighting, std::shared_ptr<LightCameraInfo> const& lightCameraInfo);

	void SetMaterial (std::shared_ptr<Material> material);
	void SetLighting (std::shared_ptr<Lighting> lighting);
	void SetLightPosition (std::shared_ptr<LightCameraInfo> lightPosition);

	std::shared_ptr<Material> const& GetMaterial () const;
	std::shared_ptr<Lighting> const& GetLighting () const;
	std::shared_ptr<LightCameraInfo> const& GetLightInfo () const;

	std::shared_ptr<UniformBuffer> const& GetPVWMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetMaterialUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetLightingUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetLightCameraInfoUniformBuffer () const;
	
	virtual void UpdateEffectMaterial ();
	virtual void UpdateEffectLighting ();
	virtual void UpdateEffectLightCameraInfo ();

protected:
	std::shared_ptr<Material> m_Material;
	std::shared_ptr<Lighting> m_Lighting;
	std::shared_ptr<LightCameraInfo> m_LightCameraInfo;

	std::shared_ptr<UniformBuffer> m_MaterialUniformBuffer;
	std::shared_ptr<UniformBuffer> m_LightingUniformBuffer;
	std::shared_ptr<UniformBuffer> m_LightCameraInfoUniformBuffer;
	std::shared_ptr<UniformBuffer> m_PVWMatrixUniformBuffer;
	//std::shared_ptr<UniformBuffer> m_WorldMatricesUniformBuffer;
	//std::shared_ptr<UniformBuffer> m_LightPVWMatrixUniformBuffer;
};

#endif