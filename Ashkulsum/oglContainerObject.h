#ifndef OGL_CONTAINER_OBJECT_H
#define OGL_CONTAINER_OBJECT_H

#include "oglInclude.h"

class OGLContainerObject 
{
public:
	virtual ~OGLContainerObject ();

	GLuint GetContainerObject () const;

	virtual void Enable () const = 0;
	virtual void Disable () const = 0;

protected:
	OGLContainerObject ();

protected:
	GLuint m_ContainerObject;

};
#endif