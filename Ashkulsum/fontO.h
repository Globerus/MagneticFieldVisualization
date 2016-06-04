#ifndef FONT_O_H
#define FONT_O_H

#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "textEffect.h"

class Font
{
public:
	Font (std::shared_ptr<ProgramFactory> programFactory, unsigned int width, unsigned int height,
			char const* texels, float const* characterData, float const* characterWidth, unsigned int maxMessageLength);

	inline std::shared_ptr<VertexBuffer> const& GetVertexBuffer () const;
	inline std::shared_ptr<IndexBuffer> const& GetIndexBuffer () const;
	inline std::shared_ptr<TextEffect> const& GetTextEffect () const;

	void SetStringData (int viewPortWidth, int viewPortHeight, int x, int y, glm::vec4 const& color, std::string const& message);

protected:
	unsigned int m_MaxMessageLength;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Texture2> m_Texture;
	std::shared_ptr<TextEffect> m_TextEffect;
	float m_CharacterData[257];
	float m_CharacterWidth[257];

};

inline std::shared_ptr<VertexBuffer> const& Font::GetVertexBuffer () const
{
	return m_VertexBuffer;
}

inline std::shared_ptr<IndexBuffer> const& Font::GetIndexBuffer () const
{
	return m_IndexBuffer;
}

inline std::shared_ptr<TextEffect> const& Font::GetTextEffect () const
{
	return m_TextEffect;
}
#endif