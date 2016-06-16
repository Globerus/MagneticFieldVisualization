#ifndef OGL_RASTERIZER_STATE_H
#define OGL_RASTERIZER_STATE_H

#include "oglDrawingState.h"
#include "rasterizerState.h"

class OGLRasterizerState : public OGLDrawingState
{
public:
	OGLRasterizerState (std::shared_ptr<const RasterizerState> rasterizerState);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> dObject);

	std::shared_ptr<RasterizerState> GetRasterizerState ();

	void Enable ();
	
private:
	GLenum m_FillMode;
	GLenum m_CullFace;
	GLenum m_FrontFace;
	GLboolean m_EnableScissor;

	static GLenum const m_sFillMode [];
	static GLenum const m_sCullFace [];
};


inline std::shared_ptr<RasterizerState> OGLRasterizerState::GetRasterizerState()
{
    return std::static_pointer_cast<RasterizerState>(m_DPObject);
}
#endif