#include "stdafx.h"
#include "fontO.h"
#include <iostream>
Font::Font (std::shared_ptr<ProgramFactory> programFactory, unsigned int width, unsigned int height,
			char const* texels, float const* characterData, float const* characterWidth, unsigned int maxMessageLength)
			:	m_MaxMessageLength (maxMessageLength)
{
	struct Vertex
	{
		glm::vec2 m_Position, m_TexCoord;
	};

	VertexAttributes vAttribute;
	vAttribute.Bind (VA_POSITION, DP_R32G32_FLOAT, 0);
	vAttribute.Bind (VA_TEXCOORD, DP_R32G32_FLOAT, 0);

	unsigned int numVertices = 4*m_MaxMessageLength;

	m_VertexBuffer = std::make_shared<VertexBuffer> (vAttribute, numVertices);
	m_VertexBuffer->SetUsage (Resource::DYNAMIC_UPDATE);

	Vertex* vertices = m_VertexBuffer->Get<Vertex> ();
	memset (vertices, 0, sizeof(Vertex)*numVertices);

	for (unsigned int i = 0; i < m_MaxMessageLength; i++)
	{
		Vertex& v0 = vertices[4*i +0];
		Vertex& v1 = vertices[4*i +1];
		Vertex& v2 = vertices[4*i +2];
		Vertex& v3 = vertices[4*i +3];

		v0.m_Position[1] = 0.0f;
        v0.m_TexCoord[1] = 1.0f;
        v1.m_TexCoord[1] = 0.0f;
        v2.m_Position[1] = 0.0f;
        v2.m_TexCoord[1] = 1.0f;
        v3.m_TexCoord[1] = 0.0f;
	}

	vertices[0].m_Position[0] = 0.0f;
	vertices[1].m_Position[0] = 0.0f;
	
	unsigned int numIndices = 6*m_MaxMessageLength;
	m_IndexBuffer = std::make_shared<IndexBuffer> (P_TRIANGLES, numIndices, sizeof(unsigned int));
	unsigned int* indices = m_IndexBuffer->Get<unsigned int> ();

	for (unsigned int i = 0; i < m_MaxMessageLength; i++)
	{
		indices[6*i +0] = 4*i;
		indices[6*i +1] = 4*i + 3;
		indices[6*i +2] = 4*i + 1;

		indices[6*i +3] = 4*i;
		indices[6*i +4] = 4*i + 2;
		indices[6*i +5] = 4*i + 3;

	}

	m_Texture = std::make_shared<Texture2> (DP_R8_UNSIGNED_NORM, width, height);
	memcpy (m_Texture->GetData(), texels, m_Texture->GetNumBytes ());
	memcpy (m_CharacterData, characterData, 257*sizeof(float));
	memcpy (m_CharacterWidth, characterWidth, 257*sizeof(float));

	m_TextEffect = std::make_shared<TextEffect> (programFactory, m_Texture);
}

void Font::SetStringData (int viewPortWidth, int viewPortHeight, int x, int y, glm::vec4 const& color, std::string const& message)
{
	float const vdx = 1.0f/static_cast<float>(viewPortWidth);
    float const vdy = 1.0f/static_cast<float>(viewPortHeight);

    float tw = static_cast<float>(m_Texture->GetWidth());
    float th = static_cast<float>(m_Texture->GetHeight());

    unsigned int vertexSize = m_VertexBuffer->GetVertexAttrib().GetVertexSize();
	char* data = m_VertexBuffer->GetData ();

    float x0 = 0.0f;
    unsigned int const length = std::min(
        static_cast<unsigned int>(message.length()), m_MaxMessageLength);
    for (unsigned int i = 0; i < length; ++i)
    {
        char c = message[i];
        float const tx0 = m_CharacterData[c];
		float const tx1 = tx0 + m_CharacterWidth[c];
       
        float charWidthM1 = (tx1 - tx0)*tw;

        float* v0 = reinterpret_cast<float*>(data + (4*i+0)*vertexSize);
        float* v1 = reinterpret_cast<float*>(data + (4 * i + 1)*vertexSize);
        float* v2 = reinterpret_cast<float*>(data + (4 * i + 2)*vertexSize);
        float* v3 = reinterpret_cast<float*>(data + (4 * i + 3)*vertexSize);

        v1[1] = vdy*th;
            
        float x1 = x0 + charWidthM1*vdx;
        v0[0] = x0;
        v1[0] = x0;
        v2[0] = x1;
        v3[0] = x1;

        v3[1] = vdy*th;

        v0[2] = tx0;
        v1[2] = tx0;
        v2[2] = tx1;
        v3[2] = tx1;

        x0 = x1;
    }

	m_VertexBuffer->SetNumActiveElements(4*length);
	m_IndexBuffer->SetNumActivePrimitives(6*length);

	float trnX = vdx*static_cast<float>(x);
	float trnY = vdy*static_cast<float>(y);
	m_TextEffect->SetTranslate(trnX, trnY);
	m_TextEffect->SetColor(color);
}