#ifndef OPEN_GL_ENGINE
#define OPEN_GL_ENGINE

#include "OGLInclude.h"
#include "programBlockIndexMap.h"
#include "geometryNode.h"
#include "billBoardNode.h"
#include "oglContainerObjectManager.h"
#include "oglVertexBuffer.h"
#include "oglIndexBuffer.h"
#include "oglProgramManager.h"
#include "oglProgramFactory.h"
#include "oglUniformBuffer.h"
#include "texture2.h"
#include "texture1.h"
#include "drawTarget.h"
#include "oglDrawTarget.h"
#include "oglTexture1.h"
#include "oglTexture2.h"
#include "oglTextureRT.h"
#include "oglTextureDS.h"
#include "samplerState.h"
#include "oglBlendState.h"
#include "oglDepthStencilState.h"
#include "oglRasterizerState.h"
#include "oglSamplerState.h"
#include "fontO.h"

class OpenGLEngine 
{
public:
	OpenGLEngine ();
	~OpenGLEngine ();

	struct Viewport 
	{
		float m_BotLeftX;
		float m_BotLeftY;
		float m_Width;
		float m_Height;
	};

	void SetViewport (glm::vec4 viewPort);
	void GetViewport (int & x, int & y, int & width, int & height);

	struct DepthRange
	{
		float m_Near;
		float m_Far;
	};

	void SetCullBackFace ();
	void SetCullFrontFace ();
	void SetEnable (GLenum glEnum);
	void SetDisable (GLenum glEnum);
	void SetCullFace (GLenum glEnum);
	void SetFrontFace (GLenum glEnum);
	void SetDepthFunc (GLenum glEnum);
	void SetDepthMask (GLenum glEnum);
	void SetDepthRange (float nearVal, float farVal);
	void SetClearColour (glm::vec4 colour);
	void ClearColorBuffer ();
	void ClearDepthBuffer ();
	void ClearBuffers ();
	
	void SetFont (std::shared_ptr<Font> const& font);

	void SetBlendState (std::shared_ptr<BlendState> const& blendState);
	void SetDepthStencilState (std::shared_ptr<DepthStencilState> const& depthStencilState);
	void SetRasterizerState (std::shared_ptr<RasterizerState> const& rasterizerState);

	inline std::shared_ptr<BlendState> GetBlendState () const;
	inline std::shared_ptr<DepthStencilState> GetDepthStencilState () const;
	inline std::shared_ptr<RasterizerState> GetRasterizerState () const;

	inline void SetDefaultBlendState ();
	inline void SetDefaultDepthStencilState ();
	inline void SetDefaultRasterizerState ();

	std::shared_ptr<OGLDrawObject> Bind (std::shared_ptr<DrawObject> const& dObject);
	std::shared_ptr<OGLDrawTarget> Bind (std::shared_ptr<DrawTarget> const& dTarget);
	OGLVertexArrayObject* Bind (std::shared_ptr<OGLVertexBuffer> const& vBuffer, std::shared_ptr<OGLIndexBuffer> const& iBuffer);
	
	std::shared_ptr<OGLDrawObject> Get (std::shared_ptr<DrawObject> const& dObject);
	std::shared_ptr<OGLDrawTarget> Get (std::shared_ptr<DrawTarget> const& dTarget);

	bool Unbind (std::shared_ptr<DrawObject> const& dObject);
	bool Unbind (std::shared_ptr<DrawTarget> const& dTarget);
	bool Unbind (std::shared_ptr<VertexBuffer> const& vBuffer, std::shared_ptr<IndexBuffer> const& iBuffer);

	bool SubscribeAsDrawObject (std::shared_ptr<GeometryNode> node);
	bool UnsubscribeDrawObject (std::shared_ptr<GeometryNode> node);

	void Draw (std::shared_ptr<GeometryNode> const& geometryNode);
	void Draw (GeometryNode const* geometryNode);
	void Draw (std::shared_ptr<VertexBuffer> vBuffer, std::shared_ptr<IndexBuffer> iBuffer, std::shared_ptr<VisualEffect> vEffect);
	void Draw (std::shared_ptr<VertexBuffer> vBuffer, std::shared_ptr<VertexBuffer> instancedBuffer, std::shared_ptr<IndexBuffer> iBuffer, std::shared_ptr<VisualEffect> vEffect);
	void Draw (int x, int y, glm::vec4 const& color, std::string const& message);

	void DrawPrimitive (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer) const;
	void DrawPrimitive (VertexBuffer const* vBuffer, VertexBuffer const* instancedBuffer, IndexBuffer const* iBuffer) const;

	bool EnableShaders (std::shared_ptr<VisualEffect> vEffect, GLuint program);
	void DisableShaders (std::shared_ptr<VisualEffect> vEffect, GLuint program);

	void Enable (Shader const* shader, GLuint program);
	void Disable (Shader const* shader, GLuint program);

	void Enable (std::shared_ptr<DrawTarget>const& dTarget);
	void Disable (std::shared_ptr<DrawTarget>const& dTarget);

	void EnableUniformBuffers (Shader const* shader, GLuint program);
	void EnableTextures (Shader const* shader, GLuint program);

	void DisableUniformBuffers (Shader const* shader, GLuint program);
	void DisableTextures (Shader const* shader, GLuint program);

	void EnableSamplers (Shader const* shader, GLuint program);
	void DisableSamplers (Shader const* shader, GLuint program);
	
	bool Update (std::shared_ptr<Buffer> const& buffer);
	bool Update (std::shared_ptr<TextureSolo> const& texture);
	bool Update (std::shared_ptr<TextureSolo> const& texture, int level);

private:
	void Initialize ();
	
	std::shared_ptr<ProgramFactory> m_ProgramFactory;
	Viewport m_Viewport;
	DepthRange m_DepthRange;
	glm::vec4 m_ClearColor;
	float m_ClearDepth;


	std::shared_ptr<Font> m_ActiveFont;

	std::shared_ptr<BlendState> m_DefaultBlendState;
	std::shared_ptr<BlendState> m_ActiveBlendState;
	std::shared_ptr<DepthStencilState> m_DefaultDepthStencilState;
	std::shared_ptr<DepthStencilState> m_ActiveDepthStencilState;
	std::shared_ptr<RasterizerState> m_DefaultRasterizerState;
	std::shared_ptr<RasterizerState> m_ActiveRasterizerState;

	static GLenum const m_PTypeTable [P_NUM_TYPES];

	typedef std::pair<DrawObject const*, DrawObject const*> CCPair;
	CustomMap<CCPair, OGLVertexArrayObject*> m_MapCO;

	CustomMap<std::shared_ptr<DrawObject> const, std::shared_ptr<OGLDrawObject>> m_MapDO;
	CustomMap<std::shared_ptr<DrawTarget> const, std::shared_ptr<OGLDrawTarget>> m_MapDT;

	ProgramBlockIndexMap m_ProgramUnitMap;
	ProgramBlockIndexMap m_TextureUnitMap;

	typedef std::shared_ptr<OGLDrawObject> (*CreateOGLObject) (std::shared_ptr<const DrawObject>);
	typedef std::shared_ptr<OGLDrawTarget> (*CreateOGLDrawTarget) (std::shared_ptr<const DrawTarget>, std::vector<std::shared_ptr<OGLDrawObject>>&, std::shared_ptr<OGLDrawObject>);
	static CreateOGLDrawTarget const m_CreateOGLDrawTarget;
	static CreateOGLObject const m_CreateOGLObject[DP_NUM_TYPES];
};

inline std::shared_ptr<BlendState> OpenGLEngine::GetBlendState () const
{
	return m_ActiveBlendState;
}

inline std::shared_ptr<DepthStencilState> OpenGLEngine::GetDepthStencilState () const
{
	return m_ActiveDepthStencilState;
}

inline std::shared_ptr<RasterizerState> OpenGLEngine::GetRasterizerState () const
{
	return m_ActiveRasterizerState;
}

inline void OpenGLEngine::SetDefaultBlendState ()
{
	SetBlendState (m_DefaultBlendState);
}

inline void OpenGLEngine::SetDefaultDepthStencilState ()
{
	SetDepthStencilState (m_DefaultDepthStencilState);
}

inline void OpenGLEngine::SetDefaultRasterizerState ()
{
	SetRasterizerState (m_DefaultRasterizerState);
}
#endif