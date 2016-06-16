#include "stdafx.h"
#include "oglContainerObject.h"

OGLContainerObject::~OGLContainerObject ()
{

}

OGLContainerObject::OGLContainerObject ()
	:	m_ContainerObject (0)
{

}

GLuint OGLContainerObject::GetContainerObject () const
{
	return m_ContainerObject;
}