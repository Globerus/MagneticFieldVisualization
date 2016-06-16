#include "stdafx.h"
#include "oglDrawObject.h"

OGLDrawObject::~OGLDrawObject ()
{
}

OGLDrawObject::OGLDrawObject (std::shared_ptr<const DrawObject> dPObject)
	:	m_DPObject (std::const_pointer_cast<DrawObject> (dPObject)),
		m_OGLObject (0)
{	
}
std::shared_ptr<DrawObject> OGLDrawObject::GetDrawObject () const
{
	return m_DPObject;
}

GLuint OGLDrawObject::GetOGLDrawObject () const
{
	return m_OGLObject;
}