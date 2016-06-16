#ifndef TEXT_EFFECT_H
#define TEXT_EFFECT_H

#include "visualEffect.h"
#include "programFactory.h"
#include "pathEnvironment.h"

class TextEffect : public VisualEffect
{
public:
	TextEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2> const& texture);


	std::shared_ptr<UniformBuffer> const& GetTranslate () const;
	std::shared_ptr<UniformBuffer> const& GetColor () const;

	void SetTranslate (float x, float y);
	void SetColor (glm::vec4 color);

private:

	std::shared_ptr<UniformBuffer> m_Translate;
	std::shared_ptr<UniformBuffer> m_Color;
	std::shared_ptr<SamplerState> m_Sampler;

};
#endif