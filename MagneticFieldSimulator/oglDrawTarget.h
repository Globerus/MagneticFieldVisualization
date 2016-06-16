#ifndef OGL_DRAW_TARGET_H
#define OGL_DRAW_TARGET_H

#include "oglTextureDS.h"
#include "oglTextureRT.h"
#include "drawTarget.h"
#include "oglInclude.h"

class OGLDrawTarget 
{
public:
	OGLDrawTarget (std::shared_ptr<const DrawTarget> drawTarget, std::vector<std::shared_ptr<OGLTextureRT>> rtTextures, std::shared_ptr<OGLTextureDS> dsTexture);

	static std::shared_ptr<OGLDrawTarget> Create (std::shared_ptr<const DrawTarget> drawTarget, std::vector<std::shared_ptr<OGLDrawObject>>& rtTextures, std::shared_ptr<OGLDrawObject> dsTexture);

	std::shared_ptr<DrawTarget> GetDrawTarget () const;

	void Enable ();
	void Disable ();

protected:
	std::vector<std::shared_ptr<OGLTextureRT>> m_RTTextures;
	std::shared_ptr<OGLTextureDS> m_DSTexture;
	std::shared_ptr<DrawTarget> m_Target;
	GLuint m_Framebuffer;

	GLint m_SaveViewportX;
	GLint m_SaveViewportY;
	GLsizei m_SaveViewportWidth;
	GLsizei m_SaveViewportHeight;
	GLdouble m_SaveViewportNear;
	GLdouble m_SaveViewportFar;
};
#endif