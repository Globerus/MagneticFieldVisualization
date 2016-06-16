#ifndef OGL_DRAW_OBJECT_H
#define OGL_DRAW_OBJECT_H

#include "oglInclude.h"
#include "drawObject.h"

class OGLDrawObject
{
public:
	virtual ~OGLDrawObject();

	std::shared_ptr<DrawObject> GetDrawObject () const;
	GLuint GetOGLDrawObject () const;

protected:
	OGLDrawObject (std::shared_ptr<const DrawObject> dPObject);

	std::shared_ptr<DrawObject> m_DPObject;
	GLuint m_OGLObject;
};
#endif