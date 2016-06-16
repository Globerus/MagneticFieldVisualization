#ifndef NORMAL_EFFECT_H
#define NORMAL_EFFECT_H

#include "visualEffect.h"
#include "programFactory.h"
#include "uniformBuffer.h"
#include "pathEnvironment.h"

class NormalEffect : public VisualEffect
{
public:
	NormalEffect (std::shared_ptr<ProgramFactory> const& programFactory);

	std::shared_ptr<UniformBuffer> const& GetPVWMatrixUniformBuffer () const;
	std::shared_ptr<UniformBuffer> const& GetColourUniformBuffer () const;

	void SetColour (glm::vec4 const& colour);
private:
	std::shared_ptr<UniformBuffer> m_PVWMatrixUniformBuffer;
	std::shared_ptr<UniformBuffer> m_ColourUniformBuffer;
};
#endif