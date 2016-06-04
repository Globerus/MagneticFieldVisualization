#include "stdafx.h"
#include "oglResource.h"

OGLResource::OGLResource (std::shared_ptr<const Resource> resource)
	:	OGLDrawObject (resource)
{

}

std::shared_ptr<Resource> OGLResource::GetResource () const
{
	return std::static_pointer_cast<Resource> (m_DPObject);
}