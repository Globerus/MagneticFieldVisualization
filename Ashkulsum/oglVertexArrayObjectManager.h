#ifndef OGL_VERTEX_ARRAY_OBJECT_MANAGER_H
#define OGL_VERTEX_ARRAY_OBJECT_MANAGER_H

#include "oglVertexArrayObject.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "customMap.h"

class OGLVertexArrayObjectManager
{
public:
	~OGLVertexArrayObjectManager ();
	OGLVertexArrayObjectManager ();

	OGLVertexArrayObject* Bind (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer);
	bool Unbind (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer);
	void UnbindAll ();

	OGLVertexArrayObject* Get (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer) const;

private:

	typedef std::pair<VertexBuffer const*, IndexBuffer const*> VIPair;
	class VaoMap : public CustomMap<VIPair, OGLVertexArrayObject*> 
	{
	public:
		~VaoMap ();
		VaoMap ();

	};

	VaoMap m_Map;

};
#endif