#ifndef OGL_SHADER_H
#define OGL_SHADER_H

#include "oglDrawObject.h"
#include "oglProgramPipelineObject.h"
#include "shader.h"

class OGLShader : public OGLDrawObject
{
public:
	virtual ~OGLShader ();

	virtual void Enable (OGLProgramPipelineObject* ppo) = 0;
	virtual void Disable (OGLProgramPipelineObject* ppo) = 0;

protected:
	OGLShader (Shader const* shader);

};
#endif