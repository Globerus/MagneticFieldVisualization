#ifndef OGL_FRAGMENT_SHADER_H
#define OGL_FRAGMENT_SHADER_H

#include "oglShader.h"

class OGLFragmentShader : public OGLShader
{
public:
	virtual ~OGLFragmentShader ();

	OGLFragmentShader (Shader const* fShader);

	void Enable (OGLProgramPipelineObject* ppo);
	void Disable (OGLProgramPipelineObject* ppo);

	static OGLDrawObject* Create (DrawObject const* fShader);

};
#endif