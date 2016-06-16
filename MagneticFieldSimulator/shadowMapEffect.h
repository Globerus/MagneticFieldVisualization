#ifndef SHADOW_MAP_EFFECT_H
#define SHADOW_MAP_EFFECT_H

#include "visualEffect.h"
#include "programFactory.h"
#include "pathEnvironment.h"

class ShadowMapEffect : public VisualEffect
{
public:
	ShadowMapEffect (std::shared_ptr<ProgramFactory> const& programFactory);

	std::shared_ptr<UniformBuffer> const& GetPVWMatrixUniformBuffer () const;
private:
	std::shared_ptr<UniformBuffer> m_PVWMatrixUniformBuffer;
};
#endif