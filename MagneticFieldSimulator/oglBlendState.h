#ifndef OGL_BLEND_STATE_H
#define OGL_BLEND_STATE_H

#include "oglDrawingState.h"
#include "blendState.h"

class OGLBlendState : public OGLDrawingState
{
public:
	OGLBlendState (std::shared_ptr<const BlendState> blendState);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> dObject);

	inline std::shared_ptr<BlendState> GetBlendState ();

	void Enable ();

private:
	struct Target
	{
		GLboolean enable;
		GLenum srcColor;
		GLenum dstColor;
		GLenum opColor;
		GLenum srcAlpha;
		GLenum dstAlpha;
		GLenum opAlpha;
		GLboolean rMask;
		GLboolean gMask;
		GLboolean bMask;
		GLboolean aMask;
	};

	bool m_EnableAlphaToCoverage;
	bool m_EnableIndependentBlend;
	Target m_Target[BlendState::NUM_TARGETS];
	glm::vec4 m_BlendColor;
	unsigned int m_SampleMask;

	static GLenum const m_sMode[];
	static GLenum const m_sOperation[];
};

inline std::shared_ptr<BlendState> OGLBlendState::GetBlendState ()
{
	return std::static_pointer_cast<BlendState> (m_DPObject);
}
#endif