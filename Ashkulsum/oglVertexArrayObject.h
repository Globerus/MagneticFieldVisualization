#ifndef OGL_VERTEX_ARRAY_OBJECT_H
#define OGL_VERTEX_ARRAY_OBJECT_H

#include "OGLInclude.h"
#include "oglContainerObject.h"
#include "oglVertexBuffer.h"
#include "oglIndexBuffer.h"

class OGLVertexArrayObject : public OGLContainerObject
{
public:
	~OGLVertexArrayObject ();
	OGLVertexArrayObject (std::shared_ptr<OGLVertexBuffer> oglVBuffer, std::shared_ptr<OGLIndexBuffer> oglIBuffer);

	void Enable () const;
	void Disable () const;
};

#endif