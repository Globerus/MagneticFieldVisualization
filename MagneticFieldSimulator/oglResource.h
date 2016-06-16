#ifndef OGL_RESOURCE_H
#define OGL_RESOURCE_H

#include "oglDrawObject.h"
#include "resourceO.h"

class OGLResource : public OGLDrawObject
{
protected:
	OGLResource (std::shared_ptr<const Resource> resource);

public:
	std::shared_ptr<Resource> GetResource () const;
	virtual bool Update () { return false;}
};

#endif