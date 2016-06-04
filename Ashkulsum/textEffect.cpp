#include "stdafx.h"
#include "textEffect.h"

TextEffect::TextEffect (std::shared_ptr<ProgramFactory> const& programFactory, std::shared_ptr<Texture2> const& texture)
{
	PathEnvironment pathEnvironment;

	std::string pathDir = pathEnvironment.GetExeDir ();

	std::string pathVertShader = pathDir + "data\\shaders\\Text.vert";
	std::string pathFragShader = pathDir + "data\\shaders\\Text.frag";
	m_Program = programFactory->CreateFromFiles (pathVertShader, pathFragShader);

	if (m_Program)
	{
		m_Translate = std::make_shared<UniformBuffer> (sizeof(glm::vec2), true);
		m_Color = std::make_shared<UniformBuffer> (sizeof(glm::vec4), true);

		m_Sampler = std::make_shared<SamplerState> ();
		
		SetTranslate (0.0f, 0.0f);
		m_Program->GetVertexShader () ->Set ("Translate", m_Translate);

		SetColor (glm::vec4 (0.0f));
		m_Program->GetFragmentShader () ->Set ("TextColor", m_Color);

		m_Program->GetFragmentShader () ->Set ("sampler", texture);
		m_Program->GetFragmentShader () ->Set ("sampler", m_Sampler);
	}
}

std::shared_ptr<UniformBuffer> const& TextEffect::GetTranslate () const
{
	return m_Translate;
}

std::shared_ptr<UniformBuffer> const& TextEffect::GetColor () const
{
	return m_Color;
}

void TextEffect::SetTranslate (float x, float y)
{
	float* data = m_Translate->Get<float> ();
	data[0] = x;
	data[1] = y;
}

void TextEffect::SetColor (glm::vec4 color)
{
	glm::vec4* data = m_Color->Get<glm::vec4> ();
	*data = color;
}