#ifndef OGL_VERTEX_SHADER_H
#define OGL_VERTEX_SHADER_H

#include "oglShaderManager.h"
#include "oglShader.h"

class OGLVertexShader : public OGLShader
{
public:
	virtual ~OGLVertexShader ();

	OGLVertexShader (Shader const* vShader);

	void Enable (OGLProgramPipelineObject* ppo);
	void Disable (OGLProgramPipelineObject* ppo);

	static OGLDrawObject* Create (DrawObject const* vShader);

};
#endif