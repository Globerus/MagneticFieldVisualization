#ifndef OGL_CONTAINER_OBJECT_MANAGER_H
#define OGL_CONTAINER_OBJECT_MANAGER_H

#include "customMap.h"
#include "vertexShader.h"
#include "fragmentShader.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include "oglVertexArrayObject.h"
//#include "oglProgramPipelineObject.h"

class OGLContainerObjectManager 
{
public:
	~OGLContainerObjectManager ();
	OGLContainerObjectManager ();

	//OGLContainerObject* Bind (VertexShader const* vShader, FragmentShader const* fShader);
	OGLContainerObject* Bind (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer);

	bool Unbind (DrawObject const* drawObjOne, DrawObject const* drawObjTwo);
	void UnbindAll ();

	//OGLContainerObject* Get (VertexShader const* vShader, FragmentShader const* fShader) const;
	OGLContainerObject* Get (VertexBuffer const* vBuffer, IndexBuffer const* iBuffer) const;

private:
	typedef std::pair<DrawObject const*, DrawObject const*> CCPair;
	class COMap : public CustomMap<CCPair, OGLContainerObject*> 
	{
	public:
		~COMap ();
		COMap ();
	};

private:
	COMap m_COMap;

};
#endif;