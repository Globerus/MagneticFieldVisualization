#ifndef OGL_UNIFORM_BUFFER_H
#define OGL_UNIFORM_BUFFER_H

#include "oglBuffer.h"
#include "uniformBuffer.h"

class OGLUniformBuffer : public OGLBuffer
{
public:
	//virtual ~OGLUniformBuffer ();
	OGLUniformBuffer (std::shared_ptr<const UniformBuffer> uBuffer);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> uBuffer);

	//void CopyToGPU (UniformBuffer const* uBuffer);
	void BindData (GLuint bindingPoint, GLuint bindIndex);
};
#endif