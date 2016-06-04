#ifndef OGL_DEPTH_STENCIL_STATE_H
#define OGL_DEPTH_STENCIL_STATE_H

#include "oglDrawingState.h"
#include "depthStencilState.h"

class OGLDepthStencilState : public OGLDrawingState
{
public:
	OGLDepthStencilState (std::shared_ptr<const DepthStencilState> depthStencilState);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> dObject);

	inline std::shared_ptr<DepthStencilState> GetDepthStencilState ();

	void Enable ();

private:
	struct Face 
	{
		GLenum onFail;
		GLenum onDepthFail;
		GLenum onDepthPass;
		GLenum comparison;
	};

	GLboolean m_DepthEnable;
	GLboolean m_WriteMask;
	GLenum m_Comparison;
	GLboolean m_StencilEnable;
	GLuint m_StencilReadMask;
	GLuint m_StencilWriteMask;
	Face m_FrontFace;
	Face m_BackFace;
	GLuint m_Reference;

	static GLboolean const m_sWriteMask [];
	static GLenum const m_sComparison [];
	static GLenum const m_sOperation [];

};

inline std::shared_ptr<DepthStencilState> OGLDepthStencilState::GetDepthStencilState ()
{
	return std::static_pointer_cast <DepthStencilState> (m_DPObject);
}
#endif