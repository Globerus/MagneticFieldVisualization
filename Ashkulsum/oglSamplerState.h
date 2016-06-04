#ifndef OGL_SAMPLERSTATE_H
#define OGL_SAMPLERSTATE_H

#include "oglDrawingState.h"
#include "samplerState.h"

class OGLSamplerState : public OGLDrawingState
{
public:
	OGLSamplerState (std::shared_ptr<const SamplerState> samplerState);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> drawObject);

protected:
	static GLint const m_TableMode[];
	static GLint const m_TableCompare[];
};
#endif