#ifndef OGL_BUFFER_H
#define OGL_BUFFER_H

#include "oglBuffer.h"
#include "vertexBuffer.h"
//#include "oglInputLayout.h"

class OGLVertexBuffer : public OGLBuffer
{
public:
	OGLVertexBuffer (std::shared_ptr<const VertexBuffer> vBuffer);
	
	static std::shared_ptr<OGLDrawObject> Create (std::shared_ptr<const DrawObject> vBuffer);
	std::shared_ptr<VertexBuffer> GetVertexBuffer () const;

	void Enable () const;
	void Disable () const;

public:
	static GLenum const m_ChannelType[];
};
#endif
