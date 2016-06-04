#ifndef OGL_INDEX_BUFFER_H
#define OGL_INDEX_BUFFER_H

#include "oglBuffer.h"
#include "indexBuffer.h"

class OGLIndexBuffer : public OGLBuffer
{
public:

	OGLIndexBuffer (std::shared_ptr<const IndexBuffer> iBuffer);

	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> iBuffer);

	std::shared_ptr<IndexBuffer> GetIndexBuffer () const;
	void Enable () const;
	void Disable () const;
};
#endif